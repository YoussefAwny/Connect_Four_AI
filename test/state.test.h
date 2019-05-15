#include "../state.h"
#include <vector>

const int num = 4;                      //4 pieces to win
const piece fill_piece = piece::us;     //piece used to fill the board

void print_board (State s);
std::vector<State> generate_win_rows(int last_move = 4);
std::vector<State> generate_win_cols(int last_move = 4);
std::vector<State> generate_win_45(int last_move = 4);
std::vector<State> generate_win_135(int last_move = 4);
void generate_all_and_draw();
