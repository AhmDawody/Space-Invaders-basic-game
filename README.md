# Game Descripiton
This repository contains the source code for a simple game of Space Invaders, written in C language and designed to run on the TM4C123GH6PM microcontroller. The game is played on a Nokia 5110 LCD screen.

The game includes all of the basic features of the original Space Invaders game, such as alien invaders that move back and forth across the screen, a player-controlled spaceship that can move left and right and shoot missiles, and shields that protect the player from alien missiles. The game also includes a score display and sound effects.   

<div>
<img src="https://user-images.githubusercontent.com/107086104/220419753-74388a01-7d59-4124-bab8-a5ef6fe2d342.png" width="150">
<img src="https://user-images.githubusercontent.com/107086104/220421351-55a605a0-1a7e-4a20-9481-50519f6fd643.png" width="150">
<img src="https://user-images.githubusercontent.com/107086104/220426568-f42973fe-e49b-4ad7-a5ad-77b2712bf2a6.png" width="150">
</div>
 
 The code is organized into several modules that handle different aspects of the game, including the LCD screen display, the game logic, the input controls, and the sound effects. The code is written in C language and is well-documented, making it easy to understand and modify. The game size is only 21 KB.
 ## Software Requirements
 You can build the game only on simulation using keil free version and use texas simulator of the launchpad.
 ## Hardware Requirements
 To use this code, you will need to have TM4C123GH6PM microcontroller (Tiva C LaunchPad), Nokia 5110 LCD screen, two 10k resistors (pull-up), four resistors with ratios: R-2R-4R-8R(DAC), two push buttons(fire), Linear Slide Potentiometer 10K, audio female socket 5-pin, jumpers and speaker.
## Hardware Connections
 * Slide pot pin 1 connected to ground
 * Slide pot pin 2 connected to PE2/AIN1
 * Slide pot pin 3 connected to +3.3V 
 * fire button connected to PE1 with R 10k to ground 
 * special weapon fire button connected to PE0 with R 10k to ground 
 * 8*R resistor DAC bit 0 on PB0 (least significant bit)
 * 4*R resistor DAC bit 1 on PB1
 * 2*R resistor DAC bit 2 on PB2
 * 1*R resistor DAC bit 3 on PB3 (most significant bit)
 * Speaker connected to DAC out
 
 <div>
 <img src="https://user-images.githubusercontent.com/107086104/220455302-b4d6dcbb-eead-4e2c-b904-14c25f6bf18e.jpg" width="200">
 </div>
 
 ### Blue Nokia 5110           
 * Signal        (Nokia 5110) LaunchPad pin  				  
 * Reset         (RST, pin 1) connected to PA7								
 * SSI0Fss       (CE,  pin 2) connected to PA3							
 * Data/Command  (DC,  pin 3) connected to PA6				
 * SSI0Tx        (Din, pin 4) connected to PA5								
 * SSI0Clk       (Clk, pin 5) connected to PA2									
 * 3.3V          (Vcc, pin 6) power																	
 * back light    (BL,  pin 7) not connected, consists of 4 white LEDs which draw ~80mA total						
 * Ground        (Gnd, pin 8) ground													
										
 ### Red SparkFun Nokia 5110 (LCD-10168)																					
 * Signal        (Nokia 5110) LaunchPad pin								
 * 3.3V          (VCC, pin 1) power											
 * Ground        (GND, pin 2) ground														
 * SSI0Fss       (SCE, pin 3) connected to PA3										
 * Reset         (RST, pin 4) connected to PA7											
 * Data/Command  (D/C, pin 5) connected to PA6												
 * SSI0Tx        (DN,  pin 6) connected to PA5											
 * SSI0Clk       (SCLK, pin 7) connected to PA2											
 * back light    (LED, pin 8) not connected, consists of 4 white LEDs which draw ~80mA total										
 
