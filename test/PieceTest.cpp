#include <Piece.hpp>

#include <util/matrix/Matrix.hpp>

#include <turtle/mock.hpp>

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

    MOCK_FUNCTOR(action, void(const mx::Matrix<bool>&));
    MOCK_EXPECT(action).once().with(piece[0]);
    MOCK_EXPECT(action).once().with(piece[1]);
    MOCK_EXPECT(action).once().with(piece[2]);
    MOCK_EXPECT(action).once().with(piece[3]);
    forEachRotation(piece, action);
}

BOOST_AUTO_TEST_CASE(ForEachRotation_FewerDirections) {
    Piece piece{{
        mx::Matrix<bool>{2, 1, {1, 1}},
        mx::Matrix<bool>{1, 2, {1, 1}},
    }};

    MOCK_FUNCTOR(action, void(const mx::Matrix<bool>&));
    MOCK_EXPECT(action).once().with(piece[0]);
    MOCK_EXPECT(action).once().with(piece[1]);
    forEachRotation(piece, action);
}

BOOST_AUTO_TEST_CASE(GetFitOffset) {
    BOOST_TEST(getFitOffset({2, 2, {
                1, 1,
                0, 1}}) == 0);
    BOOST_TEST(getFitOffset({2, 2, {
                0, 1,
                1, 1}}) == 1);
}

BOOST_AUTO_TEST_SUITE_END()
