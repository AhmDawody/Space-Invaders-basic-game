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
 You can build the game only on simulation using keil free version and use texas simulator of the launcpad.
 ## Hardware Requirements
 To use this code, you will need to have TM4C123GH6PM microcontroller (Tiva C LaunchPad), Nokia 5110 LCD screen, two 10k resistors (pull-up), four resistors with ratios: R-2R-4R-8R(DAC), two push buttons(fire), Linear Slide Potentiometer 10K, audio female socket 5-pin, jumpers and speaker.
