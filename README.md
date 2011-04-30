INFO
=====================================================================
Game Name  : Towers that Annoi  
Written by : Gregory McQuillan <gmcquillan@gmail.com>

DESCRIPTION
=====================================================================
Towers that Annoi is a puzzle game based on the game "Towers of Hanoi"
There are 3 towers, and depending on the "difficulty" level, there
may be between 3 and 10 rings located on the first tower.

DEPENDENCIES
=====================================================================
The following libraries are required to compile Towers that Annoi:

- libsdl
- libsdl_image
- libsdl_mixer

COMPILING
=====================================================================

Linux / MacX via commandline & Make

1. Type `make` from the hanoi/ directory:  
        $ make
2. Then run annoi:  
        $ ./annoi

RULES
=====================================================================
The rules are simple:

1. You must move all rings from the first Tower to the third tower.
2. You can only move one ring at a time
3. You can only place a smaller ring on top of a larger ring.

CONTROLS
=====================================================================

Choosing a tower:
---------------------------------------------------------------------

Use Left and Right arrow keys (Or J and L keys, respectively) to change
the active tower, the current tower will highlight in red.

Selecting a Ring:
---------------------------------------------------------------------
To select a ring, press the Up arrow key (or I key). After selecting
a ring, you can move it left or right and then drop it using the down
arrow (or K key).

Dropping a ring:
---------------------------------------------------------------------

Once a ring has been selected, it can be placed down by using the Down
arrow (or K key).


