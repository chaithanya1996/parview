//
// Created by chaithanya on 06/08/20.
//
#include <arrow/api.h>
#include <arrow/io/api.h>
#include <parquet/arrow/reader.h>
#include "ParseParquet.h"
#include <stdexcept>
#include <iostream>


string ParseParquet::getCsv(string path) {
    arrow::Status st;
    auto memMappedFile = arrow::io::MemoryMappedFile::Open(path,arrow::io::FileMode::type::READ);
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
    auto combinedTable = table->CombineChunks().ValueOrDie();
    // writing header

    auto headerFile = table->schema();
    auto headerList = headerFile->field_names();

    string csvoutput ;
    for (int i = 0; i < headerList.size(); ++i) {
        csvoutput.append(headerList[i]);
        if (i!=headerList.size()-1) {
            csvoutput.append(",");
        };
    }
    csvoutput.append("\n");

    for (int k = 0; k < combinedTable->num_rows(); ++k) {
        for (int j = 0; j < combinedTable->num_columns(); ++j) {
            auto chunkedColumns = combinedTable->column(j)->chunk(0);
            auto idCast = std::static_pointer_cast<arrow::StringArray>(chunkedColumns);
            csvoutput.append(idCast->GetScalar(k).ValueOrDie()->ToString());
            csvoutput.append(",");
        }
        csvoutput.append("\n");
    }
    csvoutput.append("\n");
    return csvoutput;
}

string ParseParquet::getTail(const string& path,int coun) {

    arrow::Status st;
    auto memMappedFile = arrow::io::MemoryMappedFile::Open(path,arrow::io::FileMode::type::READ);
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
    auto combinedTable = table->CombineChunks().ValueOrDie();
    // writing header

    if(combinedTable->num_rows() < coun){
        coun = combinedTable->num_rows();
    }

    auto headerFile = table->schema();
    auto headerList = headerFile->field_names();

    string csvoutput ;
    for (int i = 0; i < headerList.size(); ++i) {
        csvoutput.append(headerList[i]);
        if (i!=headerList.size()-1) {
            csvoutput.append(",");
        };
    }
    csvoutput.append("\n");

    for (int k = combinedTable->num_rows() - coun; k < combinedTable->num_rows(); ++k) {
        for (int j = 0; j < combinedTable->num_columns(); ++j) {
            auto chunkedColumns = combinedTable->column(j)->chunk(0);
            auto idCast = std::static_pointer_cast<arrow::StringArray>(chunkedColumns);
            csvoutput.append(idCast->GetScalar(k).ValueOrDie()->ToString());
            csvoutput.append(",");
        }
        csvoutput.append("\n");
    }
    csvoutput.append("\n");

    return csvoutput;
}

string ParseParquet::getHead(const string& path,int counH) {
    arrow::Status st;
    auto memMappedFile = arrow::io::MemoryMappedFile::Open(path,arrow::io::FileMode::type::READ);
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
    auto combinedTable = table->CombineChunks().ValueOrDie();
    // Boundary Chek

    if(combinedTable->num_rows() < counH){
        counH = combinedTable->num_rows();
    }
    // writing header
    auto headerFile = table->schema();
    auto headerList = headerFile->field_names();

    string csvoutput ;
    for (int i = 0; i < headerList.size(); ++i) {
        csvoutput.append(headerList[i]);
        if (i!=headerList.size()-1) {
            csvoutput.append(",");
        };
    }
    csvoutput.append("\n");

    for (int k = 0; k < counH; ++k) {
        for (int j = 0; j < combinedTable->num_columns(); ++j) {
            auto chunkedColumns = combinedTable->column(j)->chunk(0);
            auto idCast = std::static_pointer_cast<arrow::StringArray>(chunkedColumns);
            csvoutput.append(idCast->GetScalar(k).ValueOrDie()->ToString());
            csvoutput.append(",");
        }
        csvoutput.append("\n");
    }
    csvoutput.append("\n");

    return csvoutput;
}
