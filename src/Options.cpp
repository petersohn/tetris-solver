#include "Options.hpp"

#include <util/DefaultValue.hpp>

#include <boost/program_options.hpp>

#include <iostream>

namespace po = boost::program_options;

Options parseOptions(int argc, const char* argv[]) {
    po::options_description optionsDescription;
    Options options;
    bool help = false;
    optionsDescription.add_options()
        ("help,h", po::bool_switch(&help))
        ("width,w", po::value(&options.width)->required())
        ("height,h", po::value(&options.height)->required())
        ("pieces,p", po::value(&options.pieces)->required())
        ;

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
            options(optionsDescription).
            run(), vm);
    po::notify(vm);

    if (help) {
        std::cerr << optionsDescription << "\n";
        exit(0);
    }
    return options;
}
