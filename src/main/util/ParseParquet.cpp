//
// Created by chaithanya on 06/08/20.
//
#include <arrow/api.h>
#include <arrow/io/api.h>
#include <parquet/arrow/reader.h>
#include "ParseParquet.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sys/ioctl.h>
#include <unistd.h>
#include <arrow/csv/api.h>

using std::cout;
using std::endl;

// string ParseParquet::getCsv(string path) {

//     // Load Table
//     std::shared_ptr<arrow::Table> table = loadTable(path);

//     auto combinedTable = table->CombineChunks().ValueOrDie();
//     // writing header

//     auto headerFile = table->schema();
//     auto headerList = headerFile->field_names();

//     string csvoutput ;
//     for (int i = 0; i < headerList.size(); ++i) {
//         csvoutput.append(headerList[i]);
//         if (i!=headerList.size()-1) {
//             csvoutput.append(",");
//         };
//     }
//     csvoutput.append("\n");

//     for (int k = 0; k < combinedTable->num_rows(); ++k) {
//         for (int j = 0; j < combinedTable->num_columns(); ++j) {
//             auto chunkedColumns = combinedTable->column(j)->chunk(0);
//             auto idCast = std::static_pointer_cast<arrow::StringArray>(chunkedColumns);
//             csvoutput.append(idCast->GetScalar(k).ValueOrDie()->ToString());
//             csvoutput.append(",");
//         }
//         csvoutput.append("\n");
//     }
//     csvoutput.append("\n");
//     return csvoutput;
// }

arrow::Status ParseParquet::writeCSV(string path_to_file) {

   
    arrow::MemoryPool* pool = arrow::default_memory_pool();

    // Configure general Parquet reader settings
    auto reader_properties = parquet::ReaderProperties(pool);
    reader_properties.set_buffer_size(4096 * 4);
    reader_properties.enable_buffered_stream();

    // Configure Arrow-specific Parquet reader settings
    auto arrow_reader_props = parquet::ArrowReaderProperties();
    arrow_reader_props.set_batch_size(128 * 1024);  // default 64 * 1024

    parquet::arrow::FileReaderBuilder reader_builder;
    ARROW_RETURN_NOT_OK(
        reader_builder.OpenFile(path_to_file, /*memory_map=*/false, reader_properties));
    reader_builder.memory_pool(pool);
    reader_builder.properties(arrow_reader_props);

    std::unique_ptr<parquet::arrow::FileReader> arrow_reader;
    ARROW_ASSIGN_OR_RAISE(arrow_reader, reader_builder.Build());
    

    std::shared_ptr<arrow::RecordBatchReader> rb_reader;
    ARROW_RETURN_NOT_OK(arrow_reader->GetRecordBatchReader(&rb_reader));

    std::shared_ptr<arrow::io::FileOutputStream> outfile;
    ARROW_ASSIGN_OR_RAISE(outfile, arrow::io::FileOutputStream::Open(path_to_file));

    arrow::csv::WriteOptions write_options = arrow::csv::WriteOptions::Defaults();
    // std::shared_ptr<arrow::Schema> parquetFileSchema ;
    // ARROW_RETURN_NOT_OK(arrow_reader->GetSchema(&parquetFileSchema));
    // auto maybe_writer = arrow::csv::MakeCSVWriter(outfile, parquetFileSchema, write_options);
    // std::shared_ptr<arrow::ipc::RecordBatchWriter> writer = *maybe_writer;
    arrow::csv::WriteCSV(rb_reader,write_options,outfile.get());
    // for (arrow::Result<std::shared_ptr<arrow::RecordBatch>> maybe_batch : *rb_reader) {

    //     // Status WriteCSV(const std::shared_ptr<RecordBatchReader>& reader,
    //     //     const WriteOptions& options, arrow::io::OutputStream* output) {
    // }

    
    return arrow::Status::OK();

}

void ParseParquet::getTail(const string& path,int counH) {
    int formatWidth = 10;


    // Load Table
    std::shared_ptr<arrow::Table> table = loadTable(path);

    auto combinedTable = table->CombineChunks().ValueOrDie();
    // Boundary Chek

    if(combinedTable->num_rows() < counH){
        counH = combinedTable->num_rows();
    }


    auto formatRow = getTableFormatters(table,counH);
    int formatRowCount  = std::accumulate(formatRow.begin(), formatRow.end(), 0);

    cout << endl;

    int terminalWidth = getTerminalwidth();
    if (terminalWidth >  formatRowCount + formatRow.size()){
        terminalWidth = formatRowCount + formatRow.size();
    }

    for (int i = 0; i < terminalWidth; ++i) {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < table->schema()->field_names().size(); ++i) {
        cout << std::setw(formatRow[i]) << std::right << table->schema()->field_names()[i]  << "|" ;
    }
    cout << endl;

    for (int i = 0; i < terminalWidth; ++i) {
        cout << "-";
    }
    cout << endl;

    for (int k = combinedTable->num_rows() - counH; k < combinedTable->num_rows(); ++k) {
        for (int j = 0; j < combinedTable->num_columns(); ++j) {
            auto chunkedColumns = combinedTable->column(j)->chunk(0);
            auto idCast = std::static_pointer_cast<arrow::StringArray>(chunkedColumns);

            cout << std::setw(formatRow[j]) << std::right << idCast->GetScalar(k).ValueOrDie()->ToString() << "|";

        }
        cout << endl;
    }
    cout << endl;
}

void ParseParquet::getHead(const string& path,int counH) {

    // Load Table
    std::shared_ptr<arrow::Table> table = loadTable(path);

    auto combinedTable = table->CombineChunks().ValueOrDie();
    // Boundary Chek

    if(combinedTable->num_rows() < counH){
        counH = combinedTable->num_rows();
    }


    auto formatRow = getTableFormatters(table,counH);
    int formatRowCount  = std::accumulate(formatRow.begin(), formatRow.end(), 0);


    // writing Header

    int terminalWidth = getTerminalwidth();
    if (terminalWidth >  formatRowCount + formatRow.size()){
        terminalWidth = formatRowCount + formatRow.size();
    }
    cout << endl;
    for (int i = 0; i < terminalWidth; ++i) {
        cout << "-";
    }

    cout << endl;

    for (int i = 0; i < formatRow.size(); ++i) {
        cout << std::setw(formatRow[i]) << std::right << table->schema()->field_names()[i]  << "|" ;
    }
    cout << endl;

    for (int i = 0; i < terminalWidth; ++i) {
        cout << "-";
    }
    cout << endl;


    for (int k = 0; k < counH; ++k) {
        for (int j = 0; j < combinedTable->num_columns(); ++j) {
            auto chunkedColumns = combinedTable->column(j)->chunk(0);
            auto idCast = std::static_pointer_cast<arrow::StringArray>(chunkedColumns);
            cout << std::setw(formatRow[j]) << std::right << idCast->GetScalar(k).ValueOrDie()->ToString() << "|";
        }
        cout << endl;
    }
    cout << endl;
}


std::vector<int> ParseParquet::getTableFormatters(const std::shared_ptr<Table>& table, int counH) {


    auto combinedTable = table->CombineChunks().ValueOrDie();
    // Boundary Chek

    if(combinedTable->num_rows() < counH){
        counH = combinedTable->num_rows();
    }

    auto headerList = table->schema()->field_names();

    // formatter for loop

    std::vector<int> rowLenList(headerList.size()) ;

    for (int j = 0; j < combinedTable->num_columns(); ++j) {
        for (int k = 0; k < counH; ++k) {
            auto chunkedColumns = combinedTable->column(j)->chunk(0);
            auto idCast = std::static_pointer_cast<arrow::StringArray>(chunkedColumns);

            if(rowLenList[j] < idCast->GetScalar(k).ValueOrDie()->ToString().length()){
                rowLenList[j] = idCast->GetScalar(k).ValueOrDie()->ToString().length();
            };

        }
    }



    int formatRowCount = 0;
    for (int i = 0; i < headerList.size(); ++i) {
        if(rowLenList[i] < headerList[i].length()){
            rowLenList[i] = headerList[i].length();
        };
        rowLenList[i] += 3;
        formatRowCount += rowLenList[i];
    }

    return rowLenList;
}

std::shared_ptr<Table> ParseParquet::loadTable(const string &path) {

    arrow::Status st;
    auto memMappedFile = arrow::io::MemoryMappedFile::Open(path,arrow::io::FileMode::type::READ);

    // Creating Memory pool to hold the Table chunks
    arrow::MemoryPool* pool = arrow::default_memory_pool();
    std::shared_ptr<arrow::io::RandomAccessFile> input = memMappedFile.ValueOrDie();

    // Open Parquet file reader
    std::unique_ptr<parquet::arrow::FileReader> arrow_reader;
    st = parquet::arrow::OpenFile(input, pool, &arrow_reader);

    if (!st.ok()) {
        throw std::domain_error("Cannot Open File");
    }

    // Read entire file as a single Arrow table
    std::shared_ptr<arrow::Table> table;
    st = arrow_reader->ReadTable(&table);
    if (!st.ok()) {
        throw std::domain_error("Cannot Read Table");
    }
    return table;
}

int ParseParquet::getTerminalwidth() {
    struct winsize w{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}


