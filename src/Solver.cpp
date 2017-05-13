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
    // mx::dumpMatrix(std::cerr, node.field, "Add to queue");
    queue.push(std::move(node));
    ++expandedNodes;
}

void Solver::processNode(Node&& node) {
    // mx::dumpMatrix(std::cerr, node.field, "Processing node");
    // std::cerr << "Pieces: ";
    // for (int piece : node.pieces) {
    //     std::cerr << piece << " ";
    // }
    // std::cerr << "\n";
    if (checkNode(node)) {
        return;
    }

    // std::cerr << "Making search\n";
    for (mx::Point p : matrixRange(node.field)) {
        if (node.field[p] == -1) {
            for (std::size_t i = 0; i < pieces.size(); ++i) {
                if (node.pieces[i] == 0) {
                    continue;
                }
                forEachRotation(pieces[i],
                        [this, &node, &p, i](const mx::Matrix<bool>& piece) {
                            Node newNode = node;
                            if (fitPiece(newNode, p, piece, i)) {
                                addToQueue(std::move(newNode));
                            }
                        });
            }
            return;
        }
    }
    callback(node.field);
}

bool Solver::checkNode(Node& node) {
    mx::Matrix<FitData> fitData{node.field.width(), node.field.height(),
        {FitChoices::noChoices, nullptr, {0, 0}, 0}};
    for (mx::Point p : matrixRange(node.field)) {
        if (node.field[p] == -1) {
            for (std::size_t i = 0; i < pieces.size(); ++i) {
                if (node.pieces[i] == 0) {
                    continue;
                }
                forEachRotation(pieces[i],
                        [this, &node, &p, i, &fitData](
                                const mx::Matrix<bool>& piece) {
                            tryFitPiece(node, p, piece, fitData, i);
                        });
            }
        }
    }

    bool result = false;
    for (mx::Point p : matrixRange(node.field)) {
        if (node.field[p] != -1) {
            continue;
        }

        FitData& data = fitData[p];
        if (data.choices == FitChoices::noChoices) {
            // std::cerr << "No choices at " << p << "\n";
            return true;
        }
        if (data.choices == FitChoices::singleChoice) {
            // std::cerr << "Single choice at " << p << " offset="
            //         << data.offset << "\n";
            assert(data.piece);
            // mx::dumpMatrix(std::cerr, *data.piece);
            if (node.pieces[data.pieceId] == 0 ||
                    !fitPiece(node, data.offset, *data.piece, data.pieceId)) {
                return true;
            }
            result = true;
        }
    }
    if (result) {
        for (int piece : node.pieces) {
            if (piece > 0) {
                addToQueue(std::move(node));
                return true;
            }
        }
        callback(node.field);
        return true;
    }
    return false;
}

void Solver::tryFitPiece(const Node& node, mx::Point offset,
        const mx::Matrix<bool>& piece, mx::Matrix<FitData>& fitData,
        std::size_t pieceId) {
    auto originOffset = offset;
    originOffset.x -= getFitOffset(piece);
    for (mx::Point p : mx::matrixRange(piece)) {
        if (piece[p] && mx::matrixAt(node.field, p + originOffset, 0) >= 0) {
            return;
        }
    }

    for (mx::Point p : mx::matrixRange(piece)) {
        if (piece[p]) {
            FitData& data = fitData[p + originOffset];
            if (data.choices == FitChoices::noChoices) {
                data.choices = FitChoices::singleChoice;
                data.piece = &piece;
                data.offset = offset;
                data.pieceId = pieceId;
            } else if (data.choices == FitChoices::singleChoice) {
                data.choices = FitChoices::multipleChoices;
            }
        }
    }
}

bool Solver::fitPiece(Node& node, mx::Point offset,
        const mx::Matrix<bool>& piece, std::size_t pieceId) {
    // floodFill(node.field, mx::Point{0, 0}, [](mx::Point){});
    // mx::dumpMatrix(std::cerr, piece, "Fitting piece");
    // std::cerr << "Offset: " << offset << "\n";
    offset.x -= getFitOffset(piece);
    for (mx::Point p : mx::matrixRange(piece)) {
        if (piece[p] && mx::matrixAt(node.field, p + offset, 0) >= 0) {
            return false;
        }
    }

    for (mx::Point p : mx::matrixRange(piece)) {
        if (piece[p]) {
            node.field[p + offset] = node.depth;
        }
    }
    ++node.depth;
    --node.pieces[pieceId];
    return true;
}
