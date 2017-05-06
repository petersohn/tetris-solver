#include "Piece.hpp"

#include <algorithm>
#include <cctype>
#include <string>

namespace {

using M = mx::Matrix<bool>;

} // unnamed namespace

const std::array<Piece, 7> pieces{{
    {{ // Z
        M{3, 2, {
            1, 1, 0,
            0, 1, 1}},
        M{2, 3, {
            0, 1,
            1, 1,
            1, 0}},
        M{}, M{}
    }}, {{ // S
        M{3, 2, {
            0, 1, 1,
            1, 1, 0}},
        M{2, 3, {
            1, 0,
            1, 1,
            0, 1}},
        M{}, M{}
    }}, {{ // T
        M{3, 2, {
            1, 1, 1,
            0, 1, 0}},
        M{2, 3, {
            0, 1,
            1, 1,
            0, 1}},
        M{3, 2, {
            0, 1, 0,
            1, 1, 1}},
        M{2, 3, {
            1, 0,
            1, 1,
            1, 0}},
    }}, {{ // L
        M{3, 2, {
            0, 0, 1,
            1, 1, 1}},
        M{2, 3, {
            1, 0,
            1, 0,
            1, 1}},
        M{3, 2, {
            1, 1, 1,
            1, 0, 0}},
        M{2, 3, {
            1, 1,
            0, 1,
            0, 1}},
    }}, {{ // J
        M{3, 2, {
            1, 1, 1,
            0, 0, 1}},
        M{2, 3, {
            0, 1,
            0, 1,
            1, 1}},
        M{3, 2, {
            1, 0, 0,
            1, 1, 1}},
        M{2, 3, {
            1, 1,
            1, 0,
            1, 0}},
    }}, {{ // I
        M{4, 1, {1, 1, 1, 1}},
        M{1, 4, {1, 1, 1, 1}},
        M{}, M{}
    }}, {{ // O
        M{2, 2, {
            1, 1,
            1, 1}},
        M{}, M{}, M{}
    }}
}};

const Piece* getPiece(char id) {
    static const std::string ids = "ZSTLJIO";
    auto iterator = std::find(ids.begin(), ids.end(), std::toupper(id));
    if (iterator == ids.end()) {
        return nullptr;
    }
    return &pieces[iterator - ids.begin()];
}
