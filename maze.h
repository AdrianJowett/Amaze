/*
* The maze is manually defined currently
* May 2023
*/
#ifndef MAZE_H
#define MAZE_H

#include <SPI.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7789 driver chip

#include "amaze_generic.h"


// Function prototypes
void maze_init();
void draw_maze();

#define screenWidth VIEW_WIDTH//640
#define screenHeight VIEW_HEIGHT//480
#define mapWidth 21
#define mapHeight 21

#define START_X 19.5 // Start in the middle of the tile
#define START_Y 19.5

#define MAZE_PIXELS_PER_CELL (VIEW_WIDTH/mapWidth)

#define MAX_MAZE_CHOICES 3 // How many maze arrays  worlds are there?

// WORLD MAP format v02 as of 2023-06-06
/*
15 UNDEFINED
14- Bit 14 set makes a cell an exit 'portal' when hit by the player, usually a wall but not required
13- Bit 13 set to only draw when side=1 for running North-South, ie clear to draw East-West when side=0
12- Bit 12 set for transparency to be recognised as colour 0x00000000 in a texture, cleared means a solid texture

11 UNDEFINED
10 UNDEFINED
9-  Bit 9 set for texture, cleared means it is a colour
8-  Bit 8 set for wall, cleared means it is assumed to be a floor cell

7 UNDEFINED -¦ Bits 4 to 7 may be invoked to allow more colours or textures without reallocation of other bits
6 UNDEFINED  ¦
5 UNDEFINED  ¦
4 UNDEFINED -¦

3-¦ Bits 0 to 3 give 16 options for solid palette or textures
2 ¦
1 ¦
0-¦
*/

#define MAP_CHOICE_MASK  0x000f // lowest 4 bits give a choice of 16 textures and colours
#define MAP_WALL_FLAG    0x0100 // Set to be a wall
#define MAP_TEXTURE_FLAG 0x0200 // TEMPORARY TO BLOCK TEXTURE 0x0200 // Set for texture, cleared means it is a colour
#define MAP_TRANSP_FLAG  0x1000 // set to make a wall component that has transparent pixels
#define MAP_RUNS_NORTH   0x2000 // set to only draw side '1' for running North-South, ie clear East=West
#define MAP_TARGET_FLAG  0x4000 // set to be the portal - note this is independent of its texture or colour

uint16_t worldMap[MAX_MAZE_CHOICES][mapWidth][mapHeight]=
{
{// An easy open plan environment with blocky bricks, a central portal
  {0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302}, // 1
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 2
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 3
  {0x0302,0x0203,0x0203,0x0104,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0104,0x0203,0x0203,0x0302}, // 4
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 5
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 6
  {0x0302,0x0302,0x0302,0x0203,0x0203,0x0302,0x0100,0x0100,0x0100,0x0100,0x0203,0x0100,0x0100,0x0100,0x0100,0x0302,0x0203,0x0203,0x0302,0x0302,0x0302}, // 7
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0100,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0100,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 8
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0100,0x0203,0x0203,0x0203,0x0104,0x0203,0x0203,0x0203,0x0100,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 9
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0100,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0100,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 10
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0104,0x0203,0x4306,0x0203,0x0104,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 11
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0100,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0100,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 12
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0100,0x0203,0x0203,0x0203,0x0104,0x0203,0x0203,0x0203,0x0100,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 13
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0100,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0100,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 14
  {0x0302,0x0302,0x0302,0x0203,0x0203,0x0302,0x0100,0x0100,0x0100,0x0100,0x0203,0x0100,0x0100,0x0100,0x0100,0x0302,0x0203,0x0203,0x0302,0x0302,0x0302}, // 15
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 16
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 17 
  {0x0302,0x0203,0x0203,0x0104,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0104,0x0203,0x0203,0x0302}, // 18
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 19
  {0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302,0x0203,0x0203,0x0203,0x0203,0x0203,0x0302}, // 20
  {0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302,0x0302}  // 21
},
{// A garden labyrinth, an edge portal
  {0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304}, // 1
  {0x0304,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0304,0x0203,0x0203,0x0203,0x0304,0x0203,0x0203,0x0203,0x0304}, // 2
  {0x0304,0x0203,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 3
  {0x0304,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 4
  {0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 5
  {0x0304,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 6
  {0x0304,0x0203,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 7
  {0x0304,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 8
  {0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 9
  {0x0304,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 10
  {0x0304,0x0203,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 11
  {0x0304,0x0203,0x0304,0x0203,0x0203,0x0203,0x0304,0x0203,0x0203,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 12
  {0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 13
  {0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 14
  {0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 15
  {0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 16
  {0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 17 
  {0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 18
  {0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304,0x0203,0x0304}, // 19
  {0x0304,0x0203,0x0203,0x0203,0x0304,0x0203,0x0203,0x0203,0x0304,0x4306,0x0304,0x0203,0x0203,0x0203,0x0304,0x0203,0x0203,0x0203,0x0304,0x0203,0x0304}, // 20
//  {0x0304,0x0203,0x0203,0x0203,0x0304,0x0203,0x0203,0x0203,0x0304,0x4306,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0203,0x0304}, // 20 A SHORTCUT FOR TESTING!!!
  {0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304,0x0304}  // 21
},

{// A field area with flowers, a near-edge portal
  {0x0300,0x0300,0x0300,0x0300,0x0107,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0107,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300}, // 1
  {0x0300,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0300}, // 2
  {0x0300,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0300}, // 3
  {0x0300,0x0201,0x0201,0x0201,0x3308,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0300}, // 4
  {0x0300,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0300}, // 5
  {0x0300,0x0201,0x0201,0x0201,0x0305,0x0201,0x0201,0x0107,0x1307,0x1307,0x1307,0x0107,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0300}, // 6
  {0x0300,0x0201,0x0201,0x0201,0x0305,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0300}, // 7
  {0x0300,0x0201,0x0201,0x0201,0x0305,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0300}, // 8
  {0x0300,0x0201,0x0201,0x0201,0x0305,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0300}, // 9
  {0x0300,0x1307,0x1307,0x0201,0x0305,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0300}, // 10
  {0x0300,0x0201,0x0201,0x0201,0x0305,0x0201,0x0201,0x0107,0x1308,0x1307,0x1307,0x0107,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0300}, // 11
  {0x0300,0x0201,0x0201,0x0201,0x0305,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0300}, // 12
  {0x0300,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0300}, // 13
  {0x0300,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0300}, // 14
  {0x0300,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x0107,0x1307,0x1307,0x1307,0x1307,0x1308,0x1307,0x0107,0x0201,0x0300}, // 15
  {0x0300,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x3307,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x3307,0x0201,0x0300}, // 16
  {0x0300,0x0201,0x0201,0x0201,0x0305,0x0305,0x0305,0x0107,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x3307,0x0201,0x0300}, // 17 
  {0x0300,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x0107,0x0201,0x0201,0x0201,0x0201,0x4306,0x0201,0x3307,0x0201,0x0300}, // 18
  {0x0300,0x0201,0x0201,0x0201,0x0305,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x3308,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x3307,0x0201,0x0300}, // 19
  {0x0300,0x0201,0x0201,0x0201,0x0305,0x0201,0x0201,0x0201,0x0201,0x0305,0x0201,0x3307,0x0201,0x0201,0x0201,0x0201,0x0201,0x0201,0x3307,0x0201,0x0300}, // 20
  {0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0107,0x0300,0x0300,0x0300,0x0300,0x0300,0x0300,0x0107,0x0300,0x0300}  // 21
}
};

#endif