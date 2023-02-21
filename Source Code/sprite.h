#ifndef SPRITE_H_
#define SPRITE_H_
/*-------------------------------------------------------------------
 * File:        sprite.h
 * Author:      Ahmed Shehata
 * Date:        February, 2023
 *
 * Description: Header file of the sprites actions. 
 *------------------------------------------------------------------*/
 
// Included Header Files
// ----------------------
#include <stdint.h>
#include <stdbool.h>

// Function Prototypes
// --------------------
void move_ship(void);
void check_missile(void);
void Init(void);
bool ship_dead(void);
bool victory(void);
void move_enemy(void);

#endif
