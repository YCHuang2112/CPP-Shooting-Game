# A Monster Shooting Game 
# (along with POSTFIX)

## Final project of C++ programming, NCTU ECE, 2016 Fall.

----

#### Credited to (14th group members): 
		
		Yu-Cheng Huang (Game interface, logic, and hitting instances), 

		林以鑫 (Start panel and frequency domain signal processing),
 
		高璿哲 (integration, composing songs, sound sampling, and time domain signal processing).

-----

## prerequisite:

	Linux environment

	g++ compiler

## To Compile & Run:
	Open Terminal and go to directory: Shooting-Game Main Program

	Then, executing following commands:
		rm start  
		(optional) rm score_board.txt
		g++ -o start main.cpp
	
	Finally, type ./start to enjoy your game
	
	use direction key to move, space to shoot;
	return key can halt/exit the game.
	ctrl+s starts/continues the game.
	
## Game Operation and Logic:
	
	symbol p: player
	
	symbol I: monsters
	
	symbol o: bullets
	
	symbol x around p: activated traps
	

	Direction Key: controls player movement
	
	Space Key:     shoot bullets 
	
	
	player shoot monsters, while monsters can "Bonk"/attack and bounce player back.
	
	
	traps can freeze player for few seconds.
	
	Once the player HP becomes zero, then game ends.
	
	If the number of killed monsters reaches requirement, player advanced to next stage.
	
	There're infite stages of the game.  Further you go, numbers of monsters increase accompanied by the increment of player HP, numbers of bullets and traps.

## Game Screen:
//![screen-gif](./GIF/Screen1.gif)
	
<!-- <img src="./GIF/Screen1.gif" alt="My Project GIF" width="500" height="600"> -->


## User Settings:

	See file: parameters.h
	*To activate new settings, please recompile the whole project.
	
## Scoreboard:

	See file: Score_board.txt
	


	
	


