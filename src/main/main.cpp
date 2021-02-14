#include <iostream>

#include <boost/program_options.hpp>
#include "util/ParseParquet.h"
#include <fstream>
#include <filesystem>
#include <cxxopts.hpp>

namespace po = cxxopts;
namespace fs = std::filesystem;

using std::cout;
using std::endl;


int main(int argc, char *argv[] ) {
    // Declare the supported options.

    // Declare the Class
    cxxopts::Options manOptions("Manual for parview utility");

    // Add Supported options
    manOptions.add_options()
            ("help", "See available Commands and the usage")
            ("head,h", "No of lines to be displayed from the start of the parquet file \n Default Value is 50", po::value<int>()->default_value("50"))
            ("tail,t",  "No of lines to be displayed till the bottom of the parquet file \n Default Value is 50",po::value<int>()->default_value("50"))
            ("csv,c","Convert the parquet file to csv file with delimiter ,",po::value<bool>()->default_value("false"))
            ("filename,f","specify the parquet file name",po::value<string>())
            ("output,o","specify the output file name",po::value<string>());


    manOptions.parse_positional("filename");

    po::ParseResult parsedManOptions = manOptions.parse(argc, argv);

    if (parsedManOptions.count("help") || parsedManOptions.count("filename") == 0) {
        cout << manOptions.help() << "\n";
        return 1;
    }

    if (parsedManOptions.count("head")){
        ParseParquet::getHead(parsedManOptions["filename"].as<string>(),parsedManOptions["head"].as<int>());
        return 0;
    }

    if (parsedManOptions.count("tail")){
        ParseParquet::getTail(parsedManOptions["filename"].as<string>(),parsedManOptions["tail"].as<int>());
        return 0;
    }

    // Convert to String in CSV
    string outPutString =  ParseParquet::getCsv(parsedManOptions["filename"].as<string>()) ;

    // write to output
    std::ofstream outputCSV;
    string oFileName;

    try{
       string oFileName = parsedManOptions["output"].as<string>();
    }
    catch(const std::exception& e){
        oFileName = fs::path(parsedManOptions["output"].as<string>()).stem();
    }
    
    
    outputCSV.open ( oFileName + ".csv");
    outputCSV << outPutString;
    outputCSV.close();

    return 0;
}
