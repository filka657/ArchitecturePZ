#pragma once

enum Event
{
    none = 0,
    press_start1 = 1,
    press_stop1 = 2,
    waiting_command = 3,
    receive_move = 4,
    receive_turn = 5,
    set_hand = 6,
    receive_spray = 7,
    on_error = 8,
    move_error = 9,
    turn_error = 10,
    hand_error = 11,
    spray_error = 12,
};