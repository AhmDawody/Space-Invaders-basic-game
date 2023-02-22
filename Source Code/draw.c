/*-------------------------------------------------------------------
 * File:        draw.c
 * Author:      Ahmed Shehata
 * Date:        February, 2023
 * Description: Source file of the drawing functions.
 *------------------------------------------------------------------*/
 
// Included Header Files
// ----------------------
#include <stdint.h>
#include <stdbool.h>
#include "Nokia5110.h"
#include "sprite.h"
#include "tm4c123gh6pm.h"
#include "Systick.h"
#include "draw.h"

// Structs
// --------
typedef struct State{
  uint8_t x;      					// x coordinate
  uint8_t y;      					// y coordinate
  const uint8_t *image; 			// ptr->image
  uint32_t life;           	 		// 0=dead, 1=alive
}STyp;

// Externs
// --------
extern const uint8_t SmallEnemy30PointA[];
extern const uint8_t SmallEnemy30PointB[];
extern const uint8_t PlayerShip0[];
extern const uint8_t Bunker0[];
extern const uint8_t SmallExplosion0[];
extern const uint8_t BigExplosion0[];
extern const uint8_t Missile0[];
extern const uint8_t Missile1[];
extern const uint8_t Laser0[];
extern STyp Enemy[];
extern STyp Ship;
extern STyp Bunker;
extern STyp n_missile;
extern STyp missile[];
extern STyp laser;
extern STyp laser1;
extern uint8_t b_state;
extern uint8_t count;

// Draw Welcome
// -------------
void Draw_welcome(void){
	Nokia5110_ClearBuffer();
	Nokia5110_Clear();
  	Nokia5110_SetCursor(3, 0);
  	Nokia5110_OutString("SPACE");
  	Nokia5110_SetCursor(2, 1);
  	Nokia5110_OutString("INVADERS");
 	Nokia5110_SetCursor(1, 3);
  	Nokia5110_OutString("Press any");
	Nokia5110_SetCursor(0, 4);
  	Nokia5110_OutString("key to start");
	while(!(GPIO_PORTE_DATA_R&0x01)  && !(GPIO_PORTE_DATA_R&0x02) );
	Delay100ms(2);
}

// Draw Score
// -----------
void Draw_score(void){int8_t s;
	s = count +'0';
	Nokia5110_ClearBuffer();
	Nokia5110_Clear();
  	Nokia5110_SetCursor(2, 1);
  	Nokia5110_OutString("GAME OVER");
  	Nokia5110_SetCursor(1, 3);
  	Nokia5110_OutString("Your Score");
  	Nokia5110_SetCursor(5, 5);
  	Nokia5110_OutString(&s);
	Delay100ms(10);
	Nokia5110_ClearBuffer();
	Nokia5110_Clear();
	Nokia5110_SetCursor(1, 1);
	Nokia5110_OutString("Press any");
	Nokia5110_SetCursor(0, 3);
  	Nokia5110_OutString("key to start");
	while(!(GPIO_PORTE_DATA_R&0x01)  && !(GPIO_PORTE_DATA_R&0x02));
	Delay100ms(2);
}

// Draw Victory
// -------------
void Draw_victory(void){int8_t s;
	s = count +'0';
	Nokia5110_ClearBuffer();
	Nokia5110_Clear();
  	Nokia5110_SetCursor(2, 1);
  	Nokia5110_OutString("Victory!!");
  	Nokia5110_SetCursor(1, 3);
  	Nokia5110_OutString("Your Score");
  	Nokia5110_SetCursor(5, 5);
  	Nokia5110_OutString(&s);
	Delay100ms(10);
	Nokia5110_ClearBuffer();
	Nokia5110_Clear();
	Nokia5110_SetCursor(1, 1);
	Nokia5110_OutString("Press any");
	Nokia5110_SetCursor(0, 3);
  	Nokia5110_OutString("key to start");
	while(!(GPIO_PORTE_DATA_R&0x01)  && !(GPIO_PORTE_DATA_R&0x02));
	Delay100ms(2);
}

// Draw Sprites updates
// ---------------------
void Draw(void){uint8_t i;
	Nokia5110_ClearBuffer();			// Clear buffer	
	// Draw alive enemies
	for(i=0;i<4;i++){
		if(Enemy[i].life > 0){
			Nokia5110_PrintBMP(Enemy[i].x, Enemy[i].y, Enemy[i].image, 0);
			if(Enemy[i].image == SmallExplosion0){
				Enemy[i].life = 0;
				Enemy[i].x = 100;
				Enemy[i].y = 100;
			}
		}
	}
	// Draw alive player ship
	if(Ship.life > 0){
		Nokia5110_PrintBMP(Ship.x, Ship.y, Ship.image, 0);
		if(Ship.image == BigExplosion0){
			Ship.life = 0;
			Ship.x = 100;
			Ship.y = 100;
		}
	}	
	// Draw alive  normal missile		
	if(n_missile.life > 0){
		Nokia5110_PrintBMP(n_missile.x, n_missile.y, n_missile.image, 0);
	}
	// Draw alive bunker
	if(Bunker.life > 0){
		Nokia5110_PrintBMP(Bunker.x, Bunker.y, Bunker.image, 0);
		if(Bunker.image == SmallExplosion0){
			Bunker.life = 0;
			Bunker.x = 100;
			Bunker.y = 100;
		}			
	}
	// Draw special missile	
	if(missile[0].life > 0){
		Nokia5110_PrintBMP(missile[0].x, missile[0].y, missile[0].image, 0);		
	}
	if(missile[1].life > 0){
		Nokia5110_PrintBMP(missile[1].x, missile[1].y, missile[1].image, 0);		
		}
	// Draw alive  enemy missile	
	if(laser.life > 0){
		Nokia5110_PrintBMP(laser.x, laser.y, laser.image, 0);		
	}
	if(laser1.life > 0){
		Nokia5110_PrintBMP(laser1.x, laser1.y, laser1.image, 0);		
	}
	Nokia5110_DisplayBuffer();      // draw buffer
}
