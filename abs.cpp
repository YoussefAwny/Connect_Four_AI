#include "abs.h"
#include "state.h"
#include <vector>

void getChildren(const State& state, std::vector<State>& children) {
    State s(state);
	piece new_piece = state.last_move._piece == piece::us ? piece::them : piece::us;
    for (uint8_t i=0; i<BOARD_COLS; ++i) {
        if (state.make_move(new_piece, i, &s)) {
            children.push_back(s);
		}
	}
    return;
}

State alpha_beta_search(const State& state) {
    /*
        return one of the children states that has max
        value, or if there are more than on state with
        the same value, you can search more for the best
        one of them, for example, search for the  state
        that will guarantee winning (if it exists),
        however this is not done here, we just return one
        of the children that has the max value
    */
    State max_state(state); //initialize with the current state
    piece p = max_value(state, neg_inf, pos_inf, &max_state);
    return max_state;
}

piece max_value(const State& state, int alpha, int beta, State* max_state) {
    /*
        alpha is lower bound of the acceptable return value
        of this function, beta is the upper bound, these
        bounds can only get narrower, 
        if the function cannot return a value in this range
        inclusive, it should stop looking,
        for example:
        if one of the possible return values (coming
        from the children) is greater than the upper bound (beta), 
        then we are sure we will choose this value or 
        greater because we are maximizing, then there is no need
        to keep looking in the other children, just return the
        value found (which is the least value we can return)
    */

    // check if terminal node
    piece p = state.utility();
    if (p != piece::empty) {
        return p;
    } else if (state.is_full()) {
        // no winner, and board is full, therefore it's a draw and
        // a leaf node in the tree
        return p;
    } else {
        // no winner, board is not full yet, there must exist
        // children to this state
        // initialize the vector with the max possible capacity
        // to improve performance when pushing new states
        std::vector<State> children(BOARD_COLS);
        int max_util = neg_inf;
        getChildren(state, children);
        for (auto it = children.begin(); it != children.end(); ++it) {
            piece child_value = min_value(*it, alpha, beta);
            max_util = max_util > child_value ? max_util : child_value;
            // cutoff - stop looking in the other children if max_util
            // is already out of acceptable range [alpha, beta]
            if (max_state != nullptr) {
                // update with state that has max_util so far, so the
                // caller can knows which state has this max_util,
                // note that there might be multiple states with the
                // same max_util value, this way we will just choose
                // the last state of the children that has max_util
                max_state->board[it->last_move.col][it->last_move.row];
            }
            if (max_util > beta) {
                return (piece) max_util;
            }
            alpha = max_util > alpha ? max_util : alpha;
        }
        return (piece) max_util;
    }
}

piece min_value(const State& state, int alpha, int beta) {
    // check if terminal node
    piece p = state.utility();
    if (p != piece::empty) {
        return p;
    } else if (state.is_full()) {
        // no winner, and board is full, therefore it's a draw and
        // a leaf node in the tree
        return p;
    } else {
        // no winner, board is not full yet, there must exist
        // children to this state
        // initialize the vector with the max possible capacity
        // to improve performance when pushing new states
        std::vector<State> children(BOARD_COLS);
        int min_util = pos_inf;
        getChildren(state, children);
        for (auto it = children.begin(); it != children.end(); ++it) {
            piece child_value = max_value(*it, alpha, beta, nullptr);
            min_util = min_util < child_value ? min_util : child_value;
            // cutoff - stop looking in the other children if min_util
            // is already out of acceptable range [alpha, beta]
            if (min_util < alpha) {
                return (piece) min_util;
            }
            beta = min_util < beta ? min_util : beta;
        }
        return (piece) min_util;
    }
}
