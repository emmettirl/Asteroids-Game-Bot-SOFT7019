#include "asteroids.h"

struct ship_action move_ship(int field[][FIELD_WIDTH], void *ship_state){
    // Your code should go here

    struct ship_action turn = {-1,ship_state};
    return turn;
}
