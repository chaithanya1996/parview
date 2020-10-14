#include <iostream>

#include <boost/program_options.hpp>
#include "util/ParseParquet.h"
#include <fstream>
#include <filesystem>

namespace po = boost::program_options;
namespace fs = std::filesystem;

using std::cout;
using std::endl;


int main(int argc, char *argv[] ) {
    // Declare the supported options.

    // Declare the Class
    po::options_description manOptions("Manual for parview utility");

    int headC=50;
    int tailC=50;
    // Add Supported options
    manOptions.add_options()
            ("help", "See available Commands and the usage")
            ("head,h", po::value<int>(&headC)->implicit_value(50), "No of lines to be displayed from the start of the parquet file \n Default Value is 50")
            ("tail,t", po::value<int>(&tailC)->implicit_value(50), "No of lines to be displayed till the bottom of the parquet file \n Default Value is 50")
            ("csv,c",po::value<bool>(),"Convert the parquet file to csv file with delimiter ,")
            ("filename,f",po::value<string>(),"specify the parquet file name")
            ("output,o",po::value<string>(),"specify the output file name");


    po::positional_options_description positionalGuide;
    positionalGuide.add("filename", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(manOptions).positional(positionalGuide).run(), vm);


    po::notify(vm);

    if (vm.count("help") || vm.count("filename") == 0) {
        cout << manOptions << "\n";
        return 1;
    }

    if (vm.count("head")){
        ParseParquet::getHead(vm.at("filename").as<string>(),headC);
        return 0;
    }

    if (vm.count("tail")){
        ParseParquet::getTail(vm.at("filename").as<string>(),tailC);
        return 0;
    }

    // Convert to String in CSV
    auto filePath =  vm.at("filename");
    string outPutString =  ParseParquet::getCsv(filePath.as<string>()) ;

    // write to output
    std::ofstream outputCSV;
    string oFileName;

    try{
       string oFileName = vm.at("output").as<string>();
    }
    catch(const std::exception& e){
        oFileName = fs::path(filePath.as<string>()).stem();
    }
    
    
    outputCSV.open ( oFileName + ".csv");
    outputCSV << outPutString;
    outputCSV.close();

    return 0;
}
