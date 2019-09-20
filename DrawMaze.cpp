#include "uLCD_4DGL.h"
#include "BuzzyGraphics.h"
#include "Buzzy.h"

extern uLCD_4DGL guLCD;
extern char gDynaMaze[MAZE_NUM_ROW][MAZE_NUM_COL]; 
extern Buzzy gBuzzy;
/////////////////////////////////////////////////////////////////////
// The maze is a scaled down version of the LCD display
// Each element in the maze is really a 3x3 segment of the LCD
// This must be taken into account when drawing the maze on the LCD


// Draw a wall tile when 
void DrawMazeWall(int const &x1, int const &y1)
{
    int ii = 3*x1+1;
    int jj = 3*y1+1;
    guLCD.filled_rectangle(ii-1, jj-1, ii+1, jj+1, _BLUE);
}
// Draw TrapLine
void DrawTrapLine(int const &x1, int const &y1)
{
    int ii = (3*x1+1) - 4;
    int jj = (3*y1+1) - 4;
    guLCD.BLIT(ii, jj, 9, 9, &TrapLine[0][0]);
}

// Draw honey drops when
void DrawMazeHoneyDrop(int const &x1, int const &y1)
{
 
    int ii = 3*x1 + 1;
    int jj = 3*y1 + 1;
    guLCD.BLIT(ii, jj, 3, 3, &HoneyDropIcon[0][0]);
}
// Draw PowerUp Square 
void DrawMazePowerUp(int const &x1, int const &y1)
{
 
    int ii = 3*x1 + 1;
    int jj = 3*y1 + 1;
    guLCD.BLIT(ii, jj, 9, 9, &PowerUpIcon[0][0]);
}
// Draw Ghosts
void DrawVioletGhost(const int &x1, const int &y1) 
{
    int ii = (3 * x1 + 1) - 4;
    int jj = (3 * y1 + 1) - 4;
    guLCD.BLIT(ii, jj, 9, 9, &VioletGhost[gBuzzy.GetImageIndex()][0][0]);
}
void DrawBlueGhost(const int &x1, const int &y1) 
{
    int ii = (3 * x1 + 1) - 4;
    int jj = (3 * y1 + 1) - 4;
    guLCD.BLIT(ii, jj, 9, 9, &BlueGhost[gBuzzy.GetImageIndex()][0][0]);
}
void DrawPinkGhost(const int &x1, const int &y1) 
{
    int ii = (3 * x1 + 1) - 4;
    int jj = (3 * y1 + 1) - 4;
    guLCD.BLIT(ii, jj, 9, 9, &PinkGhost[gBuzzy.GetImageIndex()][0][0]);
}
void DrawGreenGhost(const int &x1, const int &y1) 
{
    int ii = (3 * x1 + 1) - 4;
    int jj = (3 * y1 + 1) - 4;
    guLCD.BLIT(ii, jj, 9, 9, &GreenGhost[gBuzzy.GetImageIndex()][0][0]);
}
/*
//////////////////////////////////////////////////////////////////////
Use the following #defines to determine which icon to draw in the LCD
#define BLUE_SQUARE 1
#define HONEYDROP_SQUARE 2
#define PWRUP_SQUARE 3
#define GHOST_ICON 4
#define BUZZY_ICON 5
#define TRAP_LINE 6

When drawing the ghosts draw one of each color
*/

void DrawMaze()
{
    for (int ii = 0 ; ii < MAZE_NUM_ROW ; ii++)
    {
        for (int jj = 0 ; jj < MAZE_NUM_COL ; jj++)
        {
            gDynaMaze[ii][jj] = gCnstMaze[ii][jj];
            if(gDynaMaze[ii][jj] == 1) {
                DrawMazeWall(ii,jj);
            } else if(gDynaMaze[ii][jj] == 2) {
                DrawMazeHoneyDrop(ii,jj);
            } else if(gDynaMaze[ii][jj] == 3) {
                DrawMazePowerUp(ii - 1,jj - 1);
            } else if(gDynaMaze[ii][jj] == 5) {
                gBuzzy.DrawInNewLocation(ii,jj);
            } else if(gDynaMaze[ii][jj] == 6) {
                DrawTrapLine(ii,jj);    
            } else if(gDynaMaze[ii][jj] == 8) {
                DrawVioletGhost(ii, jj); 
            } else if (gDynaMaze[ii][jj] == 9) {
                DrawBlueGhost(ii, jj);
            } else if (gDynaMaze[ii][jj] == 10) {
                DrawGreenGhost(ii, jj);
            }
        }
    }
}

