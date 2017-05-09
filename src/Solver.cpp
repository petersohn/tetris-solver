#include "FloodFill.hpp"
#include "Solver.hpp"

#include <util/matrix/DumperFunctions.hpp>
#include <util/matrix/PointRange.hpp>

#include <memory>

void Solver::solve(std::size_t width, std::size_t height,
        const std::array<int, numPieces>& pieces) {
    addToQueue({{width, height, -1}, pieces, 0});
    while (!queue.empty()) {
        auto node = queue.top();
        queue.pop();
        processNode(std::move(node));
    }
}

void Solver::addToQueue(Node node) {
    queue.push(std::move(node));
    ++expandedNodes;
}

void Solver::processNode(Node&& node) {
    // mx::dumpMatrix(std::cerr, node.field, "Processing node");
    for (mx::Point p : matrixRange(node.field)) {
        if (node.field[p] == -1) {
            for (std::size_t i = 0; i < pieces.size(); ++i) {
                if (node.pieces[i] == 0) {
                    continue;
                }
                forEachRotation(pieces[i],
                        [this, &node, &p, i](const mx::Matrix<bool>& piece) {
                            fitPiece(node, p, piece, i);
                        });
            }
            return;
        }
    }
    callback(node.field);
}

void Solver::fitPiece(Node node, mx::Point offset,
        const mx::Matrix<bool>& piece, std::size_t pieceId) {
    // floodFill(node.field, mx::Point{0, 0}, [](mx::Point){});
    // mx::dumpMatrix(std::cerr, piece, "Fitting piece");
    // std::cerr << "Offset: " << offset;
    offset.x -= getFitOffset(piece);
    // std::cerr << " real offset: " << offset << "\n";
    for (mx::Point p : mx::matrixRange(piece)) {
        if (piece[p] && mx::matrixAt(node.field, p + offset, 0) >= 0) {
            return;
        }
    }

    for (mx::Point p : mx::matrixRange(piece)) {
        if (piece[p]) {
            node.field[p + offset] = node.depth;
        }
    }
    ++node.depth;
    --node.pieces[pieceId];
    addToQueue(std::move(node));
}
