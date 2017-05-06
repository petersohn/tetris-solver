#include "FloodFill.hpp"
#include "Solver.hpp"

#include <util/matrix/PointRange.hpp>

#include <memory>
#include <thread>

void Solver::solve(std::size_t width, std::size_t height,
        const std::array<int, numPieces>& pieces) {
    addToQueue({{width, height, -1}, pieces, 0});
}

void Solver::addToQueue(Node node) {
    std::unique_lock<std::mutex> lock{mutex};
    queue.push(std::move(node));
    jobNotifier.notify_one();
}

void Solver::run(std::size_t numThreads) {
    assert(runningJobs == 0);
    runningJobs = numThreads;

    std::vector<std::unique_ptr<std::thread>> threads;
    for (std::size_t i = 0; i < numThreads; ++i) {
        threads.push_back(std::make_unique<std::thread>(
                [this]() { runThread(); }));
    }
    for (const auto& thread : threads) {
        thread->join();
    }
    assert(runningJobs == 0);
}

void Solver::runThread() {
    Node currentNode;
    while (true) {
        {
            std::unique_lock<std::mutex> lock{mutex};
            while (queue.empty()) {
                assert(runningJobs > 0);
                --runningJobs;
                if (runningJobs == 0) {
                    return;
                }
                jobNotifier.wait(lock);
                ++runningJobs;
            }
            currentNode = queue.top();
            queue.pop();
        }
        processNode(std::move(currentNode));
    }
}

void Solver::processNode(Node node) {
    for (mx::Point p : matrixRange(node.field)) {
        if (node.field[p] == -1) {
            for (const Piece& piece : pieces) {
                forEachRotation(piece,
                        [this, &node, &p](const mx::Matrix<bool>& piece) {
                            fitPiece(node, p, piece);
                        });
            }
            return;
        }
    }
    callback(node.field);
}

void Solver::fitPiece(Node node, mx::Point offset,
        const mx::Matrix<bool>& piece) {
    floodFill(node.field, mx::Point{0, 0}, [](mx::Point){});
}
