#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <string>

struct Options {
    std::size_t width = 0;
    std::size_t height = 0;
    std::string pieces;
    std::size_t jobs = 1;
};

Options parseOptions(int argc, const char* argv[]);

#endif // OPTIONS_HPP
