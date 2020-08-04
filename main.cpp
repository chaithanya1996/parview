#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
using std::cout;
using std::endl;

int main(int argc, char *argv[] ) {
    std::cout << "Hello, World!" << std::endl;
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("compression", po::value<int>(), "set compression level")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }

    if (vm.count("compression")) {
        cout << "Compression level was set to "
             << vm["compression"].as<int>() << ".\n";
    } else {
        cout << "Compression level was not set.\n";
    }
    return 0;
}
