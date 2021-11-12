#ifndef GAME_STRUCT
#define GAME_STRUCT

struct game_state{

	int total_stick_count;

	int remaining_sticks;

	int turn_number;

	int first_turn_taken_by;

	int game_mode;

	int current_turn;

};

typedef struct game_state game;

#endif