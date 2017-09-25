//---------------------------------------------------------------------
// Name:    James Etten, Junsu Jeong, Vang Xiong. 
// Project: Program 3, Bot Wars, Making bots fight to their deaths.
// Purpose: Parent class of different bots. Holds methods that are
//          used by VBots.
//---------------------------------------------------------------------

#include "vbot.h"

//------------------------------------------------------------------
// This method creates the graphics which sets up the colors of
// the objects.
//------------------------------------------------------------------
bool VBot::InitGraphics()
{
   try
   {
      SetUpData();

      glGenBuffers(1, &vboVertexHandle);
      glBindBuffer(GL_ARRAY_BUFFER, vboVertexHandle);
      glBufferData(GL_ARRAY_BUFFER, 2 * numPoints * sizeof(GLfloat),
         vertices, GL_STATIC_DRAW);
      glGenBuffers(1, &vboColorHandle);
      glBindBuffer(GL_ARRAY_BUFFER, vboColorHandle);
      glBufferData(GL_ARRAY_BUFFER, 4 * numPoints * sizeof(GLubyte),
         colors, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      return true;
   }
   catch (...)
   {
      return false;
   }
}

//------------------------------------------------------------------
// This method draws the VBots on the screen after each refresh.
//------------------------------------------------------------------
void VBot::Draw()
{
   glLoadIdentity();
   glTranslatef(xPos, yPos, 0);

   glBindBuffer(GL_ARRAY_BUFFER, vboVertexHandle);
   glVertexPointer(2, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, vboColorHandle);
   glColorPointer(4, GL_UNSIGNED_BYTE, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glDrawArrays(GL_POINTS, 0, numPoints);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
}

//------------------------------------------------------------------
// This method checks if two VBots have collided with each other
// and returns true if two have collided, false otherwise.
// params: b, in.
//------------------------------------------------------------------
bool VBot::CollidedWith(VBot * b) const
{
   if (b == NULL)
      return false;

   return   (xPos + width) >= b->xPos
      && (b->xPos + b->width) >= xPos
      && (yPos + height) >= b->yPos
      && (b->yPos + b->height) >= yPos;

}

//------------------------------------------------------------------
// This method does battle for two given bots and changes their
// energy.
// params: b, in.
//------------------------------------------------------------------
void VBot::DoBattleWith(VBot * b)
{
   int mine = EnergyToFightWith();
   int yours = b->EnergyToFightWith();
   if (mine == yours)
   {
      energy = energy - mine / 2;
      b->energy = b->energy - yours / 2;
   }
   else if (mine > yours)
   {
      if (b->energy > 1)
      {
         b->energy = b->energy - yours;
         energy = energy + yours / 2;
      }
      else
      {
         b->energy = b->energy - 1;
         energy = energy + 1;
      }
   }
   else
   {
      if (energy > 1)
      {
         energy = energy - mine;
         b->energy = b->energy + mine / 2;
      }
      else
      {
         b->energy = b->energy + 1;
         energy = energy - 1;
      }
   }
}

