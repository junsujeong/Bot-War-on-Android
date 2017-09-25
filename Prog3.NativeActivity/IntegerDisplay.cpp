//---------------------------------------------------------------------
// Name:    James Etten, Junsu Jeong, Vang Xiong. 
// Project: Program 3, Bot Wars, Making bots fight to their deaths.
// Purpose: Creates an integer that can be displayed on the screen.
//---------------------------------------------------------------------

#include "IntegerDisplay.h"

#define MAX_X  10
#define MAX_Y  14
#define SPACING 5

IntegerDisplay * IntegerDisplay::_instance = NULL;

//------------------------------------------------------------------
// Constructor, can't directly make instances.
//------------------------------------------------------------------
IntegerDisplay::IntegerDisplay()
{
   InitSegs();
}

//------------------------------------------------------------------
// Creates a new instance of an integer display.
//------------------------------------------------------------------
IntegerDisplay * IntegerDisplay::Instance()
{
   if (_instance == NULL)
      _instance = new IntegerDisplay();
   return _instance;
}

//------------------------------------------------------------------
// Creates the integer at a given location, number to
// display, size of the integer and the color.
// params: xPos, in.  yPos, in.  val, in.  scale, in. red, in.
//         green, in.  blue, in.
//------------------------------------------------------------------
void IntegerDisplay::DisplayIntAt(int xPos, int yPos, unsigned int val,
   float scale, uint8_t red, uint8_t green, uint8_t blue)
{
   glColor4ub(red, green, blue, 255);

   if (val >= NUMDIGS)
      DisplayIntAt(xPos - scale * (MAX_X + SPACING),
         yPos, val / NUMDIGS, scale, red, blue, green);
   DisplayDigitAt(xPos, yPos, val % NUMDIGS, scale, red, green, blue);
}

//------------------------------------------------------------------
// Creates a rectangle around an integer display with given a
// location, number to display, size of the integer and the color.
// params: xPos, in.  yPos, in.  val, in.  scale, in. red, in.
//         green, in.  blue, in.
//------------------------------------------------------------------
void IntegerDisplay::DrawBoundingRect(int xPos, int yPos, unsigned int val, float scale,
   uint8_t red, uint8_t green, uint8_t blue)
{
   int topY = yPos - scale * SPACING;
   int bottomY = yPos + scale * (MAX_Y + SPACING);
   int rightX = xPos + scale * (MAX_X + SPACING);

   int numDigits = 0;
   if (val == 0)
      numDigits = 1;
   else
   {
      int num = val;
      while (num > 0)
      {
         ++numDigits;
         num /= 10;
      }
   }
   --numDigits;
   int leftX = xPos - numDigits * scale * (MAX_X + SPACING) - 2 * SPACING;

   short verts[] = { leftX, bottomY, leftX, topY, rightX, topY, rightX, bottomY };
   glLineWidth(2.0);
   glColor4ub(red, green, blue, 255);
   glVertexPointer(2, GL_SHORT, 0, verts);
   glLoadIdentity();
   glEnableClientState(GL_VERTEX_ARRAY);
   glDrawArrays(GL_LINE_LOOP, 0, 4);
   glEnableClientState(GL_VERTEX_ARRAY);
}

//------------------------------------------------------------------
// Draws a line segment for the integer display given a location to
// start and end. In addition to the width and color of the line.
// params: x1, in.  y1, in.  x2, in.  y2, in.  width, in.
//         red, in.  green, in.  blue, in.
//------------------------------------------------------------------
void IntegerDisplay::DrawLine(int x1, int y1, int x2, int y2, float width,
   uint8_t red, uint8_t green, uint8_t blue)
{
   short verts[] = { x1, y1, x2, y2 };
   glLineWidth(width);
   glColor4ub(red, green, blue, 255);
   glLoadIdentity();
   glVertexPointer(2, GL_SHORT, 0, verts);
   glEnableClientState(GL_VERTEX_ARRAY);
   glDrawArrays(GL_LINES, 0, 2);
   glEnableClientState(GL_VERTEX_ARRAY);
}

//------------------------------------------------------------------
// Displays the integer display at a given location with the digit
// to display, the scale and color of the display.
// params: xPos, in.  yPos, in.  digit, in.  scale, in. red, in.
//         green, in.  blue, in.
//------------------------------------------------------------------
void IntegerDisplay::DisplayDigitAt(int xPos, int yPos, int digit,
   float scale, uint8_t red, uint8_t green, uint8_t blue)
{
   glLoadIdentity();
   glTranslatef(xPos, yPos, 0);
   glScalef(scale, scale, 1);

   glVertexPointer(2, GL_FLOAT, 0, vertices + digitOffsets[digit]);

   glEnableClientState(GL_VERTEX_ARRAY);
   glDrawArrays(GL_LINES, 0, numVerts[digit]);
   glDisableClientState(GL_VERTEX_ARRAY);
}

//------------------------------------------------------------------
// Creates a number for the integer display to display.
//------------------------------------------------------------------
static GLfloat digitVerts[] =
{
   // Zero
   0, 0, MAX_X, 0,
   MAX_X, 0, MAX_X, MAX_Y,
   MAX_X, MAX_Y, 0, MAX_Y,
   0, MAX_Y, 0, 0,

   // One
   MAX_X / 2, 0, MAX_X / 2, MAX_Y,

   // Two
   0, 0, MAX_X, 0,
   MAX_X, 0, MAX_X, MAX_Y / 2,
   MAX_X, MAX_Y / 2, 0, MAX_Y / 2,
   0, MAX_Y / 2,  0, MAX_Y,
   0, MAX_Y, MAX_X, MAX_Y,

   // Three
   MAX_X, 0, MAX_X, MAX_Y,
   0, 0, MAX_X, 0,
   0, MAX_Y / 2, MAX_X, MAX_Y / 2,
   0, MAX_Y, MAX_X, MAX_Y,

   // Four
   0, 0, 0, MAX_Y / 2,
   0, MAX_Y / 2, MAX_X, MAX_Y / 2,
   MAX_X, 0, MAX_X, MAX_Y,

   // Five
   MAX_X, 0, 0, 0,
   0, 0, 0, MAX_Y / 2,
   0, MAX_Y / 2, MAX_X, MAX_Y / 2,
   MAX_X, MAX_Y / 2, MAX_X, MAX_Y,
   MAX_X, MAX_Y, 0, MAX_Y,

   // Six
   MAX_X, 0, 0, 0,
   0, 0, 0, MAX_Y,
   0, MAX_Y, MAX_X, MAX_Y,
   MAX_X, MAX_Y, MAX_X, MAX_Y / 2,
   MAX_X, MAX_Y / 2, 0, MAX_Y / 2,

   // Seven
   0, 0, MAX_X, 0,
   MAX_X, 0, MAX_X, MAX_Y,

   // Eight
   0, 0, MAX_X, 0,
   MAX_X, 0, MAX_X, MAX_Y,
   0, MAX_Y / 2, MAX_X, MAX_Y / 2,
   MAX_X, MAX_Y, 0, MAX_Y,
   0, MAX_Y, 0, 0,

   // Nine
   MAX_X, 0, 0, 0,
   0, 0, 0, MAX_Y / 2,
   0, MAX_Y / 2, MAX_X, MAX_Y / 2,
   MAX_X, 0, MAX_X, MAX_Y
};

//------------------------------------------------------------------
// Creates different integer segments.
//------------------------------------------------------------------
void IntegerDisplay::InitSegs()
{
   vertices = digitVerts;

   numVerts[0] = 8;
   numVerts[1] = 2;
   numVerts[2] = 10;
   numVerts[3] = 8;
   numVerts[4] = 6;
   numVerts[5] = 10;
   numVerts[6] = 10;
   numVerts[7] = 4;
   numVerts[8] = 10;
   numVerts[9] = 8;

   totalVerts = 0;
   for (int i = 0; i < NUMDIGS; i++)
   {
      digitOffsets[i] = 2 * totalVerts;
      totalVerts += numVerts[i];
   }
}