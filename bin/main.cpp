#include <Options.hpp>
#include <Solver.hpp>

#include <util/matrix/DumperFunctions.hpp>

#include <iostream>
#include <unordered_set>

int main(int argc, const char* argv[]) {
    Options options = parseOptions(argc, argv);

    std::size_t numSolutions = 0;
    Solver solver{
            [&](const mx::Matrix<int>& solution) {
                ++numSolutions;
                dumpMatrix(std::cout, solution, "", 0,
                        [](int i) { return std::to_string(i % 10); });
            }};
    solver.solve(options.width, options.height,
            parsePieces(options.pieces));
    std::cerr << "Total expanded nodes: " << solver.getExpandedNodes() << "\n"
            << "Number of solutions: " << numSolutions << "\n";
}
