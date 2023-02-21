/*-------------------------------------------------------------------
 * File:        sprite.c
 * Author:      Ahmed Shehata
 * Date:        February, 2023
 *
 * Description: Source file of the sprites actions. 
 *------------------------------------------------------------------*/

// Included Header Files
// ----------------------
#include <stdint.h>
#include <stdbool.h>
#include "Nokia5110.h"
#include "sprite.h"
#include "ADC.h"
#include "Systick.h"
#include "tm4c123gh6pm.h"
#include "Random.h"
#include "DAC.h"

// Sprites Dimensions
// ------------------
#define BUNKERW     ((uint8_t)Bunker0[18])
#define BUNKERH     ((uint8_t)Bunker0[22])
#define ENEMY30W    ((uint8_t)SmallEnemy30PointA[18])
#define ENEMY30H    ((uint8_t)SmallEnemy30PointA[22])
#define ENEMY20W    ((uint8_t)SmallEnemy20PointA[18])
#define ENEMY20H    ((uint8_t)SmallEnemy20PointA[22])
#define ENEMY10W    ((uint8_t)SmallEnemy10PointA[18])
#define ENEMY10H    ((uint8_t)SmallEnemy10PointA[22])
#define ENEMYBONUSW ((uint8_t)SmallEnemyBonus0[18])
#define ENEMYBONUSH ((uint8_t)SmallEnemyBonus0[22])
#define LASERW      ((uint8_t)Laser0[18])
#define LASERH      ((uint8_t)Laser0[22])
#define MISSILEW    ((uint8_t)Missile0[18])
#define MISSILEH    ((uint8_t)Missile0[22])
#define PLAYERW     ((uint8_t)PlayerShip0[18])
#define PLAYERH     ((uint8_t)PlayerShip0[22])

// structs
// ----------
typedef struct State{
  uint8_t x;      								// x coordinate
  uint8_t y;      								// y coordinate
  const uint8_t *image; 					// ptr->image
  uint32_t life;           	 			// 0=dead, 1=alive
}STyp;

// externs
// -------------
extern const uint8_t SmallEnemy30PointA[];
extern const uint8_t SmallEnemy30PointB[];
extern const uint8_t PlayerShip0[];
extern const uint8_t Bunker0[];
extern const uint8_t Bunker1[];
extern const uint8_t Bunker2[];
extern const uint8_t SmallExplosion0[];
extern const uint8_t BigExplosion0[];
extern const uint8_t Missile0[];
extern const uint8_t Missile1[];
extern const uint8_t Laser0[];

// Global Variables
// -----------------
uint8_t b_state;							// Bunker state counter
uint16_t e_state;							// Enemy state counter
uint8_t count;								// Enemy kill counter
STyp Enemy[4];								// 4 Enemies
STyp Ship;										// Player Ship
STyp Bunker;									// Bunker
STyp n_missile;								// Ship normal missile
STyp missile[2];							// Ship special missile
STyp laser;										// Enemy missile
STyp laser1;									// Enemy missile

// Constans
// ---------
const uint8_t *Bunker_state[]={Bunker1, Bunker2, SmallExplosion0};				//	bunker state images
const uint8_t *Enemy_state[]={SmallEnemy30PointB, SmallEnemy30PointA};		//	Enemy state images

// Function Prototypes
// --------------------
static void n_missile_Init(void);
static void missile_Init(void);
static void move_n_missile(void);
static void move_laser(void);
static void move_laser1(void);
static void move_missile0(void);
static void move_missile1(void);
static void enemy_laser_Init(uint8_t);
static void enemy_laser1_Init(uint8_t);
static void move_enemy_x(void);
static void move_enemy_y(void);

// Initialize enemies, ship and bunker position and missiles
// ----------------------------------------------------------
void Init(void){ uint8_t i;
	//Enemies
	for(i=0;i<4;i++){
		Enemy[i].x = 20*i;
		Enemy[i].y = ENEMY30H;
		Enemy[i].image = SmallEnemy30PointA;
		Enemy[i].life = 1;
	}
	//Ship
	Ship.x = 32;
	Ship.y = 47;
	Ship.image = PlayerShip0;
	Ship.life =1;
	//Bunker
	 Bunker.x = 32;
	 Bunker.y = 47- PLAYERH -1;
	 Bunker.image = Bunker0;
	 Bunker.life = 1;
	 //Missiles
	 n_missile.life = 0;
	 missile[0].life = 0;
	 missile[1].life = 0;
	 laser.life = 0;
	 laser1.life = 0;
	 //Global variables
	 count = 0;
	 b_state = 0;
	 e_state = 0;
}
static void n_missile_Init(void){ 
		n_missile.x = Ship.x+8;
		n_missile.y = 42;
		n_missile.image = Missile0;
		n_missile.life = 1;
}
static void missile_Init(void){
		missile[0].x = Ship.x + 8;
		missile[0].y = 42;
		missile[0].image = Missile0;
		missile[0].life = 1;
		missile[1].x = Ship.x + 8;
		missile[1].y = 42;
		missile[1].image = Missile1;
		missile[1].life = 1;
}
static void enemy_laser_Init(uint8_t i){
		laser.x = Enemy[i].x + 8;
		laser.y = Enemy[i].y + 6;
		laser.image = Laser0;
		laser.life = 1;
}
static void enemy_laser1_Init(uint8_t i){
		laser1.x = Enemy[i].x + 8;
		laser1.y = Enemy[i].y + 6;
		laser1.image = Laser0;
		laser1.life = 1;
}


// Check if player draw missile and draw enemy missiles by RNG
// ------------------------------------------------------------
void check_missile(void){uint8_t r, m;
		r = Random() % 4;
		m = Random() % 4;
		// If SW1 is pressed, initialize special missile and generate sound
		if((GPIO_PORTE_DATA_R&0x01) && (!missile[0].life) && (!missile[1].life) && (!n_missile.life)){
				missile_Init();
				Sound_Shoot();
		}
		// If SW2 is pressed, initialize normal missile and generate sound
		else if((GPIO_PORTE_DATA_R&0x02) && (!missile[0].life) && (!missile[1].life) && (!n_missile.life)){
				n_missile_Init();
				Sound_Shoot();
		}
		// If missile is initialized, move them
		if(n_missile.life){
				move_n_missile();
		}
		if(missile[0].life){
				move_missile0();
		}
		if(missile[1].life){
				move_missile1();
		}
		// If enemy laser is initialized, move it. else initialize it
		if(laser.life){
				move_laser();
		}else{
				enemy_laser_Init(r);
		}
		if(laser1.life){
				move_laser1();
		}else{
				enemy_laser1_Init(m);
		}
}

// Move ship normal missile
// ------------------------
static void move_n_missile(void){uint8_t i;
		n_missile.y -= 3;		// Missile speed
		// If it goes off screen or hit bunker, erase the missile
		if((n_missile.y <= 1) || ((n_missile.y >= Bunker.y) && (n_missile.x+1 >= Bunker.x && n_missile.x <= Bunker.x +17))){
				n_missile.life = 0;
		}
		// If it hit enemy, explode enemy and generate sound
		else{
			for(i=0; i<4; i++){
				if(n_missile.y <= Enemy[i].y+8 && (n_missile.x >= Enemy[i].x+2 && n_missile.x <= Enemy[i].x+11)){
					Enemy[i].image =SmallExplosion0;
					Sound_Killed();
					n_missile.life =0;				// Erase missile
					count ++;						// Increase enemy counter
				}
			}
		}
}

// Move ship special missile 1
// ---------------------------
static void move_missile0(void){uint8_t i;
		missile[0].y -= 3;			// Missile speed
		missile[0].x -= 1;			// Missile speed
		// If it goes off screen or hit bunker, erase the missile
		if((missile[0].x <= 1 || missile[0].y <= 1)|| ((missile[0].y >= Bunker.y) && (missile[0].x+1 >= Bunker.x && missile[0].x <= Bunker.x +17))){
				missile[0].life = 0;
		}
		// If it hit enemy, explode enemy and generate sound
		else{
			for(i=0; i<4; i++){
				if(missile[0].y <= Enemy[i].y+8 && (missile[0].x >= Enemy[i].x+2 && missile[0].x <= Enemy[i].x+11)){
					Enemy[i].image =SmallExplosion0;
					Sound_Killed();
					missile[0].life =0;							// Erase missile
					count ++;									// Increase enemy counter
				}
			}
		}
}

// Move ship special missile 2
// ---------------------------
static void move_missile1(void){uint8_t i;
		missile[1].y -= 3;				// Missile speed
		missile[1].x += 1;				// Missile speed
		// If it goes off screen or hit bunker, erase the missile
		if((missile[1].x >= 82 || missile[1].y <= 1) || ((missile[1].y >= Bunker.y) && (missile[1].x+1 >= Bunker.x && missile[1].x <= Bunker.x +17))){
				missile[1].life = 0;
		}
		// If it hit enemy, explode enemy and generate sound
		else{
			for(i=0; i<4; i++){
				if(missile[1].y <= Enemy[i].y+8 && (missile[1].x >= Enemy[i].x+2 && missile[1].x <= Enemy[i].x+11)){
					Enemy[i].image =SmallExplosion0;
					Sound_Killed();
					missile[1].life =0;							// Erase missile
					count ++;									// Increase enemy counter
				}
			}
		}
}

// Move enemy missile 1
// --------------------
static void move_laser(void){
		laser.y += 2;					// Missile speed
		if((laser.y > 47)){		// If it goes off screen , erase the missile
				laser.life = 0;
		}
		// If it hit bunker, damage it
		else{
			if(((laser.y >= Bunker.y-5) && (laser.x >= Bunker.x && laser.x <= Bunker.x +17))){		//hit bunker
					laser.life = 0;
					Bunker.image = Bunker_state[b_state++];
					if(Bunker.image == Bunker_state[2])
					Sound_Explosion();
			}
			// If it hit ship, explode it and generate sound
			else if(((laser.y >= Ship.y-7) && (laser.x >= Ship.x+2 && laser.x <= Ship.x +17))){
					laser.life = 0;
					Ship.image = BigExplosion0; 
					Sound_Explosion();
			}
	}
}

// Move enemy missile 2
// --------------------
static void move_laser1(void){
		laser1.y += 2;					// Missile speed
		if((laser1.y > 47)){			// If it goes off screen , erase the missile
			laser1.life = 0;
		}
		// If it hit bunker, damage it
		else{
			if(((laser1.y >= Bunker.y-5) && (laser1.x >= Bunker.x && laser1.x <= Bunker.x +17))){		//hit bunker
					laser1.life = 0;
					Bunker.image = Bunker_state[b_state++];
					if(Bunker.image == Bunker_state[2])
								Sound_Explosion();
			}
			// If it hit ship, explode it and generate sound
			else if(((laser1.y >= Ship.y-7) && (laser1.x >= Ship.x+2 && laser1.x <= Ship.x +17))){
					laser1.life = 0;
					Ship.image = BigExplosion0; 
					Sound_Explosion();
			}
		}
}

// Move player ship
// -----------------
void move_ship(void){
		if(Ship.life){
			uint16_t in = ADC0_In();
			uint32_t c = convert(in);
			Ship.x = c;
		}
}

// Move enemy at x direction
// -------------------------
static void move_enemy_x(void){
		uint8_t i, r, x;
		int8_t m;
		int8_t enemy_pos[16] = {-2, 2, -2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2};
		r = Random() % 200;
		if(r < 16){
			m = enemy_pos[r];
			for(i=0;i<4;i++){				// If one enemy will go off screen, return
				if(Enemy[i].life ){
					x = Enemy[i].x;
					if(((x + m) > 68) || ((x + m) < 1)){
						return;
					}
				}
			}
			e_state++;
			for(i=0; i<4; i++){
				Enemy[i].x += m;
				Enemy[i].image = Enemy_state[e_state&0x01];	// Change enemy image if it moves in x direction
			}
		}
}

// Move enemy at y direction
// -------------------------
static void move_enemy_y(void){
		uint8_t i, r, y;
		int8_t m;
		int8_t enemy_pos[16] = {1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1};
		r = Random() % 200;
		if(r < 16){
			m = enemy_pos[r];
			for(i=0;i<4;i++){			// If one enemy will go off screen, return
				if(Enemy[i].life){
					y = Enemy[i].y;
					if(((y + m) > 20) || ((y + m) < 10)){
						return;
					}
				}
			}
			for(i=0; i<4; i++){
				Enemy[i].y += m;
			}
		}
}

// Move enemy
// -----------
void move_enemy(void){
	move_enemy_x();
	move_enemy_y();
}

// Return 1 if ship is destroyed, else return 0
// --------------------------------------------
bool ship_dead(void){
	if(Ship.life == 0)
			return 1;
	else 
			return 0;
}

// Return 1 if all enemies are destroyed, else return 0
// ----------------------------------------------------
bool victory(void){
		if(count == 4)
			return 1;
		else
			return 0;
}
