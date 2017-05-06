#ifndef FLOODFILL_HPP
#define FLOODFILL_HPP

#include <util/matrix/Matrix.hpp>
#include <util/matrix/SquareMatrix.hpp>

namespace mx = util::matrix;

template <typename Action>
mx::Matrix<bool> floodFill(const mx::Matrix<int>& matrix, mx::Point p0,
        Action action)
{
    mx::Matrix<bool> reached{matrix.width(), matrix.height(), false};

    std::vector<mx::Point> pointsToVisit;
    pointsToVisit.reserve(matrix.width()*matrix.height());
    pointsToVisit.push_back(p0);

    while (!pointsToVisit.empty()) {
        mx::Point p = pointsToVisit.back();
        pointsToVisit.pop_back();

        if (matrixAt(reached, p, true)) {
            continue;
        }
        action(p);

        reached[p] = true;
        for (auto direction : mx::square::Neighbors::Range{}) {
            mx::Point target = p + mx::square::neighbors[direction];
            if (!isInsideMatrix(matrix, target)) {
                continue;
            }
            if (matrix[p] >= 0) {
                pointsToVisit.push_back(target);
            }
        }
    }
    return reached;
}

#endif // FLOODFILL_HPP
