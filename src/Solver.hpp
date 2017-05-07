#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Piece.hpp"

#include <util/matrix/Matrix.hpp>

#include <array>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>

namespace mx = util::matrix;

class Solver {
public:
    Solver(const std::function<void(const mx::Matrix<int>&)>& callback)
            : callback(callback) {}

    void solve(std::size_t width, std::size_t height,
            const std::array<int, numPieces>& pieces);
    void run(std::size_t numThreads);

    std::size_t getExpandedNodes() const { return expandedNodes; }

private:
    struct Node {
        mx::Matrix<int> field;
        std::array<int, numPieces> pieces;
        int depth;

        bool operator<(const Node& other) const {
            return depth < other.depth;
        }
    };

    void addToQueue(Node node);
    void runThread();
    void processNode(Node node);
    void fitPiece(Node node, mx::Point offset, const mx::Matrix<bool>& piece,
            std::size_t pieceId);

    std::function<void(const mx::Matrix<int>)> callback;
    std::priority_queue<Node> queue;
    std::condition_variable jobNotifier;
    std::size_t runningJobs = 0;
    std::size_t expandedNodes = 0;
    std::mutex mutex;
};

#endif // SOLVER_HPP
