#include <iostream>

#include <boost/program_options.hpp>
#include "util/ParseParquet.h"
#include <fstream>

namespace po = boost::program_options;
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
            ("help", "See availabale Commands and the usage")
            ("head", po::value<int>(), "No of lines to be displayed from the start of the parquet file \n Default Value is 50")
            ("tail", po::value<int>(), "No of lines to be displayed till the bottom of the parquet file \n Default Value is 50")
            ("csv",po::value<bool>(),"Convert the parquet file to csv file with delimiter ,")
            ("filename",po::value<string>()->required(),"specify the parquet file name")
            ("output,o",po::value<string>(),"specify the output file name");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, manOptions), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << manOptions << "\n";
        return 1;
    }

    if (vm.count("head")){
        cout << ParseParquet::getHead(vm.at("filename").as<string>(),vm.at("head").as<int>());
        return 0;
    }

    if (vm.count("tail")){
        cout << ParseParquet::getTail(vm.at("filename").as<string>(),vm.at("tail").as<int>());
        return 0;
    }

    // Convert to String in CSV
    auto filePath =  vm.at("filename");
    string outPutString =  ParseParquet::getCsv(filePath.as<string>()) ;

    // write to output
    std::ofstream outputCSV;
    outputCSV.open (  vm.at("output").as<string>() + ".csv");
    outputCSV << outPutString;
    outputCSV.close();

    return 0;
}
