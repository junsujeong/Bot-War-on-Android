//---------------------------------------------------------------------
// Name:    James Etten, Junsu Jeong, Vang Xiong. 
// Project: Program 3, Bot Wars, Making bots fight to their deaths.
// Purpose: Creates a button for the user to press to activate a
//          corresponding action.
//---------------------------------------------------------------------

#include "GL_Button.h"
#include "IntegerDisplay.h"

#define BUTTON_WIDTH  20
#define BUTTON_HEIGHT 28

//------------------------------------------------------------------
// Render as two triangles.
//------------------------------------------------------------------
static GLfloat btnVerts[] =
{
   0, 0, 0, BUTTON_HEIGHT, BUTTON_WIDTH, 0,
   BUTTON_WIDTH, 0, 0, BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT,
};

//------------------------------------------------------------------
// Constructor, creates a GL_Button with the given location,
// integer to display, the size of the button and color info.
// params: posX, in.  posY, in.  digitDisp, in. scale, in.
//         rfg, in.  gfg, in.  bfg, in.  rbg, in.  gbg, in.
//         bbg, in.
//------------------------------------------------------------------
GL_Button::GL_Button(int posX, int posY, int digitDisp, float scale,
   uint8_t rfg, uint8_t gfg, uint8_t bfg,
   uint8_t rbg, uint8_t gbg, uint8_t bbg) : xPos(posX), yPos(posY),
   rFG(rfg), gFG(gfg), bFG(bfg), rBG(rbg), gBG(gbg), bBG(bbg),
   digitDisplay(digitDisp), scaleAmt(scale)
{
   numVerts = sizeof(btnVerts) / sizeof(GLfloat) / 2;
}

//------------------------------------------------------------------
// Detects if the button has been pressed.
//------------------------------------------------------------------
bool GL_Button::PressInside(int x, int y)
{
   return x >= xPos && y >= yPos &&
      x < (xPos + scaleAmt * BUTTON_WIDTH) &&
      y < (yPos + scaleAmt * BUTTON_HEIGHT);
}

//------------------------------------------------------------------
// Draws the button on the screen.
//------------------------------------------------------------------
void GL_Button::Draw()
{
   glLoadIdentity();
   glTranslatef(xPos, yPos, 0);
   glScalef(scaleAmt, scaleAmt, 1);

   glColor4ub(rBG, gBG, bBG, 255);

   glVertexPointer(2, GL_FLOAT, 0, btnVerts);

   glEnableClientState(GL_VERTEX_ARRAY);
   glDrawArrays(GL_TRIANGLES, 0, numVerts);
   glDisableClientState(GL_VERTEX_ARRAY);

   IntegerDisplay::Instance()->DisplayIntAt(xPos +
      scaleAmt * BUTTON_WIDTH / 4,
      yPos + scaleAmt * BUTTON_HEIGHT / 4, digitDisplay, scaleAmt,
      rFG, gFG, bFG);
}

