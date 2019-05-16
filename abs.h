/*
    Alpha-Beta Search
*/
#ifndef ABS_H
#define ABS_H

#include "state.h"
#include <vector>

#define neg_inf (piece::them - 1)
#define pos_inf (piece::us + 1)

//todo: move getChildren function to State class
void getChildren(const State& state, std::vector<State*>& children);

// note: max_level default value is set to greatest possible value (unsigned of -1)
State alpha_beta_search(const State& state, const unsigned int max_level = -1);
piece max_value(State& state, int alpha, int beta, const unsigned int max_level, std::vector<State>* max_states);
piece min_value(State& state, int alpha, int beta, const unsigned int max_level);

#endif //ABS_H
