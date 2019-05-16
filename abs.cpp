#include "abs.h"
#include "state.h"
#include <vector>

// define NDEBUG before including cassert to
// disable all asserts in code
// #define NDEBUG
#include <cassert>

// define VERBOSE = 1 to enable logging more info,
// disable by setting VERBOSE = 0
#define VERBOSE 0

/* for VERBOSE option */
#include <iostream>
using namespace std;
namespace verbose {
    // even tree levels are maximizers, odd are minimizers
    int tree_level = 0;
}

//todo: unused function
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
    // create state to receive result, initialize with the current state
    State max_state(state);
    // keep the passed state unchanged, make a copy
    State working_state(state);
	// don't use the return value, just get max_state
    max_value(working_state, neg_inf, pos_inf, &max_state);
    return max_state;
}

piece max_value(State& state, int alpha, int beta, State* max_state) {
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
    if (VERBOSE) ++verbose::tree_level;
    // check if terminal node
    piece p = state.utility();
    if (p != piece::empty) {
        if (VERBOSE) --verbose::tree_level;
        return p;
    } else if (state.is_full()) {
        // no winner, and board is full, therefore it's a draw and
        // a leaf node in the tree
        if (VERBOSE) --verbose::tree_level;
        return p;
    } else {
        // no winner, board is not full yet, there must exist
        // children to this state
        int max_util = neg_inf;
        piece new_piece = state.last_move._piece == piece::us ? piece::them : piece::us;
        for (int i=0; i<BOARD_COLS; ++i) {
            game_move gm = state.last_move;
            if (state.insert_piece(new_piece, i)) {
                if (VERBOSE && verbose::tree_level == 1) {
                    std::cout << "<<<<<<<<<<<<<<<<<<<<< child started" << std::endl;
                    std::cout << "<<<<<<<<<<<<<<<<<<<<< alpha, beta: " << alpha << ", " << beta << endl;
                }
                piece child_value = min_value(state, alpha, beta);
                if (VERBOSE && verbose::tree_level == 1) {
                    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>> child finished" << std::endl;
                    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>> child utility: " << child_value << ", max_util: " << max_util << endl;
                }
                if (child_value > max_util) {
                    max_util = child_value;
                    if (max_state != nullptr) {
                        // update with state that has max_util so far, so the
                        // caller can knows which state has this max_util,
                        // note that there might be multiple states with the
                        // same max_util value, this way we will just choose
                        // the last state of the children that has max_util
                        *max_state = State(state);
                    }
                }
                // reset last_move (before loop iteration ends (before any
                // breaks) but after the state is possibly saved in max_state)
                state.remove_piece(state.last_move.row, state.last_move.col, gm);
                // cutoff - stop looking in the other children if max_util
                // is already out of acceptable range [alpha, beta]
                if (max_util >= beta) {
                    break;
                }
                alpha = max_util > alpha ? max_util : alpha;
            }
        }
        // assert that we at least found one child
        assert(max_util != neg_inf);
        if (VERBOSE) --verbose::tree_level;
        return (piece) max_util;
    }
}

piece min_value(State& state, int alpha, int beta) {
    if (VERBOSE) ++verbose::tree_level;
    // check if terminal node
    piece p = state.utility();
    if (p != piece::empty) {
        if (VERBOSE) --verbose::tree_level;
        return p;
    } else if (state.is_full()) {
        // no winner, and board is full, therefore it's a draw and
        // a leaf node in the tree
        if (VERBOSE) --verbose::tree_level;
        return p;
    } else {
        // no winner, board is not full yet, there must exist
        // children to this state
        int min_util = pos_inf;
        piece new_piece = state.last_move._piece == piece::us ? piece::them : piece::us;
        for (int i=0; i<BOARD_COLS; ++i) {
            game_move gm = state.last_move;
            if (state.insert_piece(new_piece, i)) {
                if (VERBOSE && verbose::tree_level == 2) {
                    std::cout << "                  <<<< child started" << std::endl;
                    std::cout << "                  <<<< alpha, beta: " << alpha << ", " << beta << endl;
                }
                piece child_value = max_value(state, alpha, beta, nullptr);
                if (VERBOSE && verbose::tree_level == 2) {
                    std::cout << "                  >>>>>>>>>>>>>>>> child finished" << std::endl;
                    std::cout << "                  >>>>>>>>>>>>>>>> child utility: " << child_value << ", min_util: " << min_util << endl;
                }
                if (child_value < min_util) {
                    min_util = child_value;
                }
                // reset last_move (before loop iteration ends)
                state.remove_piece(state.last_move.row, state.last_move.col, gm);
                // cutoff - stop looking in the other children if min_util
                // is already out of acceptable range [alpha, beta]
                if (min_util <= alpha) {
                    break;
                }
                beta = min_util < beta ? min_util : beta;
            }
        }
        // assert that we at least found one child
        assert(min_util != pos_inf);
        if (VERBOSE) --verbose::tree_level;
        return (piece) min_util;
    }
}
