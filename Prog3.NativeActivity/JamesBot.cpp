//---------------------------------------------------------------------
// Name:    James Etten
// Project: Program 3, Bot Wars, Making bots fight to their deaths.
// Purpose: Created a JamesBot that is used as a bot to fight in
//          the bot battles.
//---------------------------------------------------------------------

#include "JamesBot.h"
#include <cstdlib>

int JamesBot::numCreated = 0;
int JamesBot::numDestroyed = 0;
float JamesBot::divEnergy = 1.1;

//------------------------------------------------------------------
// Constructor, creates a JamesBot with the given starting position,
// devices screen height and width, energy for the bot to fight
// and the direction to move. In addition to initializing the
// graphics and adding to the created counter.
// params: x, in.  y, in.  width, in.  height, in.  energy, in.
//         xMove, in.  yMove, in.
//------------------------------------------------------------------
JamesBot::JamesBot(int x, int y, int width, int height, int energy,
                   int xMove, int yMove) : VBot(x, y, width, height, energy)
{
   xToMove = xMove;
   yToMove = yMove;
   InitGraphics();
   numCreated++;
}

//------------------------------------------------------------------
// Destructor, counts how many bots have been destroyed. 
//------------------------------------------------------------------
JamesBot::~JamesBot()
{
   JamesBot::numDestroyed++;
}

//------------------------------------------------------------------
// Returns the number of created bots.
//------------------------------------------------------------------
int JamesBot::NumCreated()
{
   return numCreated;
}

//------------------------------------------------------------------
// Returns the number of destroyed bots. 
//------------------------------------------------------------------
int JamesBot::NumDestroyed()
{
   return numDestroyed;
}

//------------------------------------------------------------------
// Resets the counters back to zero. 
//------------------------------------------------------------------
void JamesBot::ResetCounters()
{
   numCreated = 0;
   numDestroyed = 0;
}

//------------------------------------------------------------------
// Moves the bot to a new position on the screen.
//------------------------------------------------------------------
void JamesBot::Move()
{
   xPos = xPos + xToMove;
   yPos = yPos + yToMove;

   if (xPos >= screenWidth)
      xToMove = -xToMove;
   if (yPos >= screenHeight)
   {
      yToMove = -yToMove;
      xToMove = -xToMove;
   }
   if (xPos <= 0)
      xToMove = -xToMove;
   if (yPos <= 0)
      yToMove = -yToMove;
}

//------------------------------------------------------------------
// Returns the energy that the bot gets to fight with. 
//------------------------------------------------------------------
int JamesBot::EnergyToFightWith()
{
   return energy / divEnergy;
}
