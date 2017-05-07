#include <Options.hpp>
#include <Solver.hpp>

#include <util/matrix/MatrixIO.hpp>

#include <iostream>

int main(int argc, const char* argv[]) {
    Options options = parseOptions(argc, argv);

    std::size_t numSolutions = 0;
    Solver solver{
            [&](const mx::Matrix<int>& solution) {
                ++numSolutions;
                std::cout << solution;
            }};
    solver.solve(options.width, options.height,
            parsePieces(options.pieces));
    solver.run(options.jobs);
    std::cerr << "Total expanded nodes: " << solver.getExpandedNodes() << "\n"
            << "Number of solutions: " << numSolutions << "\n";
}
