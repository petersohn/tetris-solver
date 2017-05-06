#ifndef _HOME_PEET_WORKSPACE_TETRIS_SOLVER_NODE_HPP
#define _HOME_PEET_WORKSPACE_TETRIS_SOLVER_NODE_HPP

#include <util/matrix/Matrix.hpp>

#include <array>

namespace mx = util::matrix;

struct Node {
    mx::Matrix<bool> field;

};

#endif // _HOME_PEET_WORKSPACE_TETRIS_SOLVER_NODE_HPP
