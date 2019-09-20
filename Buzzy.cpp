#include "Buzzy.h"
#include "Ghosts.h"
#include "BuzzyGraphics.h"
#include "uLCD_4DGL.h"
#include "Speaker.h"

extern char gDynaMaze[MAZE_NUM_ROW][MAZE_NUM_COL]; 
extern Ghosts gGhosts[NUM_GHOSTS];
extern Buzzy gBuzzy;
extern uLCD_4DGL guLCD;
extern Speaker gSpeakerOut;
extern int needHoneyDrops;

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// Constructor
Buzzy::Buzzy(enDIRECTIONS inDir, unsigned int inRow, unsigned int inCol):
Sprite(inDir, inRow, inCol)
{
    
}    

//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void Buzzy::Move()
{    
    int nRow = m_RowPos, nCol = m_ColPos;       // next direction
    int px = m_RowPos, py = m_ColPos;           // Previous direction
    // Try to move buzzy in the desired direction
    if (m_DesiredDirection == NO_DIR ) {
        nRow = m_RowPos, nCol = m_ColPos;
        gSpeakerOut.SwitchSound(Speaker::SIREN);
        return;
    }
    if (m_DesiredDirection == UP_DIR ) {
        nRow += 1;    
    } 
    if (m_DesiredDirection == DOWN_DIR) {
        nRow -= 1;    
    }
    if (m_DesiredDirection == RIGHT_DIR) {
        nCol += 1; 
    }
    if (m_DesiredDirection == LEFT_DIR) {
        nCol -= 1;  
    } 
    
        if(IsMoveAllowed(nRow, nCol)) { 
            m_CurrentDirection = m_DesiredDirection;
            gSpeakerOut.SwitchSound(Speaker::CHOMP);
            DrawInNewLocation(nRow,nCol);
            return;
        } 
        // If failed to move in desired direction the try to move Buzzy in old direction
       if(!IsMoveAllowed(nRow,nCol)) {   // checking if it can move in current direction
            switch(m_CurrentDirection) {
                case UP_DIR:
                    if (IsMoveAllowed(px + 1, py)){
                        DrawInNewLocation(px + 1, py);
                        gSpeakerOut.SwitchSound(Speaker::CHOMP);
                        break;
                    }
                case DOWN_DIR:
                    if (IsMoveAllowed(px - 1, py)) {
                        DrawInNewLocation(px - 1, py);
                        gSpeakerOut.SwitchSound(Speaker::CHOMP);
                        break;
                    }
                case RIGHT_DIR:
                    if (IsMoveAllowed(px, py + 1)) {
                        DrawInNewLocation(px, py + 1);
                        gSpeakerOut.SwitchSound(Speaker::CHOMP);
                        break;
                    }
                case LEFT_DIR:
                    if (IsMoveAllowed(px, py - 1)) {
                        DrawInNewLocation(px, py - 1);
                        gSpeakerOut.SwitchSound(Speaker::CHOMP);
                        break;
                    }
                case NO_DIR:
                    gSpeakerOut.SwitchSound(Speaker::SIREN);
                    break;
            }

        }

}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Buzzy::DrawInNewLocation(const int &nRow,const int &nCol)
{
    int x1, y1;
    // Test if we hit a honeydrop or fruit or ghost
    
    if (gDynaMaze[nRow][nCol] == HONEYDROP_SQUARE)
    {
        needHoneyDrops++;
        gDynaMaze[nRow][nCol] = EMPTY;
    }
        
    if (gDynaMaze[nRow][nCol] == PWRUP_SQUARE) {
        gSpeakerOut.SwitchSound(Speaker::EAT_FRUIT);
        gDynaMaze[nRow][nCol] = EMPTY;
    }
    if (gDynaMaze[nRow][nCol] == GHOST_ICON) {
        // END GAME IF WE HIT GHOST 
       gSpeakerOut.SwitchSound(Speaker::EAT_GHOST);
       gDynaMaze[nRow][nCol] = EMPTY;
    } 
    x1 = (3*m_RowPos+1)-4;
    y1 = (3*m_ColPos+1)-4;        
    // Clean up the part that will be left
    guLCD.filled_rectangle(x1, y1, x1 + 8, y1 + 8, BLACK); 
    
    gBuzzy.SetLocation(nRow, nCol);     
    guLCD.BLIT(x1, y1, 9, 9, &BuzzyIcon[GetImageIndex()][0][0]);      
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool Buzzy::DidGhostGetBuzzy()
{

    return false;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool Buzzy::IsMoveAllowed(const int &nNewRow, const int &nNewCol)
{
     
     if ((gDynaMaze[nNewRow+1][nNewCol] == BLUE_SQUARE) 
            || (gDynaMaze[nNewRow-1][nNewCol] == BLUE_SQUARE)
            || (gDynaMaze[nNewRow][nNewCol+1] == BLUE_SQUARE)
            || (gDynaMaze[nNewRow][nNewCol-1] == BLUE_SQUARE)
            || (gDynaMaze[nNewRow+1][nNewCol+1] == BLUE_SQUARE)
            || (gDynaMaze[nNewRow+1][nNewCol-1] == BLUE_SQUARE)
            || (gDynaMaze[nNewRow-1][nNewCol+1] == BLUE_SQUARE)
            || (gDynaMaze[nNewRow-1][nNewCol-1] == BLUE_SQUARE)
            || (gDynaMaze[nNewRow+1][nNewCol] == TRAP_LINE) 
            || (gDynaMaze[nNewRow-1][nNewCol] == TRAP_LINE)
            || (gDynaMaze[nNewRow][nNewCol+1] == TRAP_LINE)
            || (gDynaMaze[nNewRow][nNewCol-1] == TRAP_LINE)
            || (gDynaMaze[nNewRow+1][nNewCol+1] == TRAP_LINE)
            || (gDynaMaze[nNewRow+1][nNewCol-1] == TRAP_LINE)
            || (gDynaMaze[nNewRow-1][nNewCol+1] == TRAP_LINE)
            || (gDynaMaze[nNewRow-1][nNewCol-1] == TRAP_LINE)) 
    { 
        return false;
    } else {
        return true;
    }

}

