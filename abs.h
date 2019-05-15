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
void getChildren(const State& state, std::vector<State>& children);

State alpha_beta_search(const State& state);
piece max_value(const State& state, int alpha, int beta, State* max_state);
piece min_value(const State& state, int alpha, int beta);

#endif //ABS_H
