//---------------------------------------------------------------------
// Name:    James Etten, Junsu Jeong, Vang Xiong. 
// Project: Program 3, Bot Wars, Making bots fight to their deaths.
// Purpose: Creates a button for the user to press to activate a
//          corresponding action.
//---------------------------------------------------------------------

#ifndef __GL_BUTTON_H
#define __GL_BUTTON_H

//---------------------------------------------------------------------
// This class creates a botton that can be assigned to do different
// actions.
//---------------------------------------------------------------------
class GL_Button
{
public:

   //------------------------------------------------------------------
   // Constructor, creates a GL_Button with the given location,
   // integer to display, the size of the button and color info.
   // params: posX, in.  posY, in.  digitDisp, in. scale, in.
   //         rfg, in.  gfg, in.  bfg, in.  rbg, in.  gbg, in.
   //         bbg, in.
   //------------------------------------------------------------------
   GL_Button(int posX, int posY, int digitDisp, float scale = 1.0,
      uint8_t rfg = 255, uint8_t gfg = 255, uint8_t bfg = 255,
      uint8_t rbg = 100, uint8_t gbg = 100, uint8_t bbg = 100);

   //------------------------------------------------------------------
   // Draws the button on the screen.
   //------------------------------------------------------------------
   void Draw();

   //------------------------------------------------------------------
   // Detects if the button has been pressed.
   //------------------------------------------------------------------
   bool PressInside(int x, int y);

private:
   int xPos, yPos;
   uint8_t rFG, gFG, bFG;
   uint8_t rBG, gBG, bBG;
   int digitDisplay;
   float scaleAmt;
   int numVerts;
};

#endif

