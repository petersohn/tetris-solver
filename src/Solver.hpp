#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Piece.hpp"

#include <util/matrix/Matrix.hpp>

#include <array>
#include <functional>
#include <stack>

namespace mx = util::matrix;

class Solver {
public:
    Solver(const std::function<void(const mx::Matrix<int>&)>& callback)
            : callback(callback) {}

    void solve(std::size_t width, std::size_t height,
            const std::array<int, numPieces>& pieces);

    std::size_t getExpandedNodes() const { return expandedNodes; }

private:
    struct Node {
        mx::Matrix<int> field;
        std::array<int, numPieces> pieces;
        int depth;
    };

    enum class FitChoices {
        noChoices, singleChoice, multipleChoices
    };

    struct FitData {
        FitChoices choices;
        const mx::Matrix<bool>* piece;
        mx::Point offset;
        std::size_t pieceId;
    };

    void addToQueue(Node node);
    void processNode(Node&& node);
    bool checkNode(Node& node);
    void tryFitPiece(const Node& node, mx::Point offset,
            const mx::Matrix<bool>& piece, mx::Matrix<FitData>& fitData,
            std::size_t pieceId);
    bool fitPiece(Node& node, mx::Point offset,
            const mx::Matrix<bool>& piece, std::size_t pieceId);

    std::function<void(const mx::Matrix<int>)> callback;
    std::stack<Node> queue;
    std::size_t runningJobs = 0;
    std::size_t expandedNodes = 0;
};

#endif // SOLVER_HPP
