#include "abs.h"
#include "state.h"
#include <vector>

void getChildren(const State& state, std::vector<State*>& children) {
	/*
		NOTE: it's the responsibility of the caller to manually delete
		each State in children
	*/
	piece new_piece = state.last_move._piece == piece::us ? piece::them : piece::us;
    for (uint8_t i=0; i<BOARD_COLS; ++i) {
		State* s = new State(state);
        if (state.make_move(new_piece, i, s)) {
            children.push_back(s);
		} else {
			delete s;	//todo: improve performance
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
	//don't use the return value, just get max_state
    max_value(state, neg_inf, pos_inf, &max_state);
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
        std::vector<State*> children;
        // reserve the max possible capacity
        // to improve performance when pushing new states
        children.reserve(BOARD_COLS);
        int max_util = neg_inf;
        getChildren(state, children);
        for (auto it = children.begin(); it != children.end(); ++it) {
			auto child_ptr = *it;
            piece child_value = min_value(*child_ptr, alpha, beta);
            max_util = max_util > child_value ? max_util : child_value;
            // cutoff - stop looking in the other children if max_util
            // is already out of acceptable range [alpha, beta]
            if (max_state != nullptr) {
                // update with state that has max_util so far, so the
                // caller can knows which state has this max_util,
                // note that there might be multiple states with the
                // same max_util value, this way we will just choose
                // the last state of the children that has max_util
                max_state->board[child_ptr->last_move.col][child_ptr->last_move.row] = 
					child_ptr->last_move._piece;
            }
            if (max_util > beta) {
                break;
            }
            alpha = max_util > alpha ? max_util : alpha;
        }
		//delete all children
		for (auto it = children.begin(); it != children.end(); ++it) {
			delete *it;
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
        std::vector<State*> children;
        // reserve the max possible capacity
        // to improve performance when pushing new states
        children.reserve(BOARD_COLS);
        int min_util = pos_inf;
        getChildren(state, children);
        for (auto it = children.begin(); it != children.end(); ++it) {
			auto child_ptr = *it;
            piece child_value = max_value(*child_ptr, alpha, beta, nullptr);
            min_util = min_util < child_value ? min_util : child_value;
            // cutoff - stop looking in the other children if min_util
            // is already out of acceptable range [alpha, beta]
            if (min_util < alpha) {
				break;
            }
            beta = min_util < beta ? min_util : beta;
        }
		//delete all children
		for (auto it = children.begin(); it != children.end(); ++it) {
			delete *it;
		}
        return (piece) min_util;
    }
}
