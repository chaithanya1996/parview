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

    // Add Supported options
    manOptions.add_options()
            ("help,h", "See availabale Commands and the usage")
            ("head,H", po::value<int>()->default_value(50), "No of lines to be displayed from the start of the parquet file \n Default Value is 50")
            ("tail,T", po::value<int>()->default_value(50), "No of lines to be displayed till the bottom of the parquet file \n Default Value is 50")
            ("csv",po::value<bool>()->default_value(false),"Convert the parquet file to csv file with delimiter ,")
            ("filename,f",po::value<string>(),"specify the parquet file name")
            ("output,o",po::value<string>(),"specify the output file name");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, manOptions), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << manOptions << "\n";
        return 1;
    }
    auto filePath =  vm.at("filename");
    string outPutString =  ParseParquet::getCsv(filePath.as<string>()) ;

    std::ofstream outputCSV;
    outputCSV.open (  vm.at("output").as<string>() + ".csv");
    outputCSV << outPutString;
    outputCSV.close();

    return 0;
}
