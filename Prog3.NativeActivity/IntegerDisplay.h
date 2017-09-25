//---------------------------------------------------------------------
// Name:    James Etten, Junsu Jeong, Vang Xiong. 
// Project: Program 3, Bot Wars, Making bots fight to their deaths.
// Purpose: Creates an integer that can be displayed on the screen.
//---------------------------------------------------------------------

#ifndef __INTEGER_DISPLAY_H
#define __INTEGER_DISPLAY_H

//---------------------------------------------------------------------
// This class creates and manages an integer display.
//---------------------------------------------------------------------
class IntegerDisplay
{
public:

   //------------------------------------------------------------------
   // Initializes an integer display.
   //------------------------------------------------------------------
   static void Initialize() { delete _instance; _instance = NULL; }

   //------------------------------------------------------------------
   // Creates a new instance of an integer display.
   //------------------------------------------------------------------
   static IntegerDisplay * Instance();

   //------------------------------------------------------------------
   // Creates the integer at a given location, number to
   // display, size of the integer and the color.
   // params: xPos, in.  yPos, in.  val, in.  scale, in. red, in.
   //         green, in.  blue, in.
   //------------------------------------------------------------------
   void DisplayIntAt(int xPos, int yPos, unsigned int val, float scale = 1.0,
      uint8_t red = 255, uint8_t green = 255, uint8_t blue = 255);

   //------------------------------------------------------------------
   // Creates a rectangle around an integer display with given a
   // location, number to display, size of the integer and the color.
   // params: xPos, in.  yPos, in.  val, in.  scale, in. red, in.
   //         green, in.  blue, in.
   //------------------------------------------------------------------
   void DrawBoundingRect(int xPos, int yPos, unsigned int val, float scale = 1.0,
      uint8_t red = 255, uint8_t green = 255, uint8_t blue = 255);

   //------------------------------------------------------------------
   // Draws a line segment for the integer display given a location to
   // start and end. In addition to the width and color of the line.
   // params: x1, in.  y1, in.  x2, in.  y2, in.  width, in.
   //         red, in.  green, in.  blue, in.
   //------------------------------------------------------------------
   void DrawLine(int x1, int y1, int x2, int y2, float width = 1.0,
      uint8_t red = 255, uint8_t green = 255, uint8_t blue = 255);


private:

   //------------------------------------------------------------------
   // Constructor, can't directly make instances.
   //------------------------------------------------------------------
   IntegerDisplay();

   static IntegerDisplay * _instance;

   static const int NUMDIGS = 10;
   GLfloat * vertices;
   int digitOffsets[NUMDIGS];
   int totalVerts;
   int numVerts[NUMDIGS];

   //------------------------------------------------------------------
   // Creates different integer segments.
   //------------------------------------------------------------------
   void InitSegs();

   //------------------------------------------------------------------
   // Displays the integer display at a given location with the digit
   // to display, the scale and color of the display.
   // params: xPos, in.  yPos, in.  digit, in.  scale, in. red, in.
   //         green, in.  blue, in.
   //------------------------------------------------------------------
   void DisplayDigitAt(int xPos, int yPos, int digit, float scale,
      uint8_t red, uint8_t green, uint8_t blue);
};

#endif

