#include <Options.hpp>
#include <Solver.hpp>

#include <util/matrix/DumperFunctions.hpp>

#include <iostream>
#include <unordered_set>

int main(int argc, const char* argv[]) {
    Options options = parseOptions(argc, argv);

    std::size_t numSolutions = 0;
    std::unordered_set<mx::Matrix<int>> solutions;
    Solver solver{
            [&](const mx::Matrix<int>& solution) {
                ++numSolutions;
                dumpMatrix(std::cout, solution, "", 0,
                        [](int i) { return std::to_string(i % 10); });
                if (solutions.count(solution) == 0) {
                    solutions.insert(solution);
                } else {
                    std::cout << "Duplicate solution\n";
                }
            }};
    solver.solve(options.width, options.height,
            parsePieces(options.pieces));
    std::cerr << "Total expanded nodes: " << solver.getExpandedNodes() << "\n"
            << "Number of solutions: " << numSolutions << "\n"
            << "Number of unique solutions: " << solutions.size() << "\n";
}
