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

BOOST_AUTO_TEST_CASE(ParsePieces_empty) {
    auto result = parsePieces("");
    BOOST_TEST(result[0] == 0);
    BOOST_TEST(result[1] == 0);
    BOOST_TEST(result[2] == 0);
    BOOST_TEST(result[3] == 0);
    BOOST_TEST(result[4] == 0);
    BOOST_TEST(result[5] == 0);
    BOOST_TEST(result[6] == 0);
}

BOOST_AUTO_TEST_CASE(ParsePieces_oneOfEach) {
    auto result = parsePieces("ZTLOSIJ");
    BOOST_TEST(result[0] == 1);
    BOOST_TEST(result[1] == 1);
    BOOST_TEST(result[2] == 1);
    BOOST_TEST(result[3] == 1);
    BOOST_TEST(result[4] == 1);
    BOOST_TEST(result[5] == 1);
    BOOST_TEST(result[6] == 1);
}

BOOST_AUTO_TEST_CASE(ParsePieces_lowercase) {
    auto result = parsePieces("ztlosij");
    BOOST_TEST(result[0] == 1);
    BOOST_TEST(result[1] == 1);
    BOOST_TEST(result[2] == 1);
    BOOST_TEST(result[3] == 1);
    BOOST_TEST(result[4] == 1);
    BOOST_TEST(result[5] == 1);
    BOOST_TEST(result[6] == 1);
}

BOOST_AUTO_TEST_CASE(ParsePieces_moreOfSome) {
    auto result = parsePieces("ssooollll");
    BOOST_TEST(result[0] == 0);
    BOOST_TEST(result[1] == 2);
    BOOST_TEST(result[2] == 0);
    BOOST_TEST(result[3] == 4);
    BOOST_TEST(result[4] == 0);
    BOOST_TEST(result[5] == 0);
    BOOST_TEST(result[6] == 3);
}

BOOST_AUTO_TEST_CASE(ParsePieces_mixedOrder) {
    auto result = parsePieces("ssolsli");
    BOOST_TEST(result[0] == 0);
    BOOST_TEST(result[1] == 3);
    BOOST_TEST(result[2] == 0);
    BOOST_TEST(result[3] == 2);
    BOOST_TEST(result[4] == 0);
    BOOST_TEST(result[5] == 1);
    BOOST_TEST(result[6] == 1);
}

BOOST_AUTO_TEST_CASE(ParsePieces_invalidCharacter) {
    BOOST_CHECK_THROW(parsePieces("x"), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()
