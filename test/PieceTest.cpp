#include <Piece.hpp>

#include <util/matrix/Matrix.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(PieceTest)

BOOST_AUTO_TEST_CASE(ForEachRotation_AllDirections) {
    Piece piece{{
        mx::Matrix<bool>{2, 2, {
                1, 1,
                0, 1}},
        mx::Matrix<bool>{2, 2, {
                0, 1,
                1, 1}},
        mx::Matrix<bool>{2, 2, {
                1, 0,
                1, 1}},
        mx::Matrix<bool>{2, 2, {
                1, 1,
                1, 0}},
    }};
}

BOOST_AUTO_TEST_CASE(ForEachRotation_AllDirections) {
    Piece piece{{
        mx::Matrix<bool>{2, 2, {
                1, 1,
                0, 1}},
        mx::Matrix<bool>{2, 2, {
                0, 1,
                1, 1}},
        mx::Matrix<bool>{2, 2, {
                1, 0,
                1, 1}},
        mx::Matrix<bool>{2, 2, {
                1, 1,
                1, 0}},
    }};
}

BOOST_AUTO_TEST_SUITE_END()
