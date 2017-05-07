#ifndef PIECE_HPP
#define PIECE_HPP

#include <util/matrix/Matrix.hpp>

#include <array>
#include <string>

namespace mx = util::matrix;

static constexpr int numRotations = 4;
static constexpr int numPieces = 7;

using Piece = std::array<mx::Matrix<bool>, numRotations>;

extern const std::array<Piece, numPieces> pieces;

std::array<int, numPieces> parsePieces(const std::string& input);

template<typename Action>
void forEachRotation(const Piece& piece, const Action& action) {
    for (const auto& rotation : piece) {
        if (rotation.width() == 0) {
            return;
        }
        action(rotation);
    }
}

inline
int getFitOffset(const mx::Matrix<bool>& piece) {
    for (mx::Point p{0, 0}; p.x < static_cast<int>(piece.width()); ++p.x) {
        if (piece[p]) {
            return p.x;
        }
    }
    assert(false && "Impossible piece");
}

#endif // PIECE_HPP
