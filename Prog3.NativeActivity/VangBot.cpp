//---------------------------------------------------------------------
// Name:    Vang Xiong
// Project: Program 3, Bot Wars, Making bots fight to their deaths.
// Purpose: Implement the VangBot and makes the bots movements along
//          with its energy. 
//---------------------------------------------------------------------
#include "VangBot.h"

int VangBot::numCreated = 0;
int VangBot::numDestroyed = 0;
float VangBot::NUM_ENERGY = 1.5;
int VangBot::_TWO = 2;
int VangBot::_TEN = 10;
const int FIVE = 5;

// ----------------------------------------------------------------
// This constructor has the information given to create the bot at
// the certain locations of the screen and giving the bot the 
// energy generated.
// Params: x: in, y: in, width: in, height: in, energy: in. 
// ----------------------------------------------------------------
VangBot::VangBot(int x, int y, int width, int height, int energy) : VBot(x, y, width, height, energy)
{
   //This makes the VangBot
   InitGraphics();
   numCreated++;
   xToMove = FIVE;
   yToMove = -FIVE;
}

// ----------------------------------------------------------------
// Reset the counters to 0.
// ----------------------------------------------------------------
void VangBot::ResetCounter()
{
   numDestroyed = 0;
   numCreated = 0;
}

// ----------------------------------------------------------------
// This is the unique movement of the bot. 
// ----------------------------------------------------------------
void VangBot::Move()
{
   xPos = xPos + xToMove;
   yPos = yPos + yToMove;
   if (xPos > screenWidth)
   {
      if (EnergyToFightWith() < EnergyToFightWith() / _TWO)
      {
         xPos = screenWidth;
         xToMove = -xToMove * (1 + rand() % _TEN);
      }
      else
      {
         xPos = screenWidth;
         xPos = -xPos;
      }
   }
   if (yPos > screenHeight)
   {
      if (EnergyToFightWith() < EnergyToFightWith() / _TWO)
      {
         yPos = screenHeight;
         yToMove = -yToMove * (1 + rand() % _TEN);
      }
      else
      {
         yPos = screenHeight;
         yPos = -yPos;
      }
   }
   if (xPos < 0)
   {
      xPos = 0;
      xToMove = -xToMove;
   }
   if (yPos < 0)
   {
      yPos = 0;
      yToMove = -yToMove;
   }
}

// ----------------------------------------------------------------
// Returns the energy of the robot. 
// ----------------------------------------------------------------
int VangBot::EnergyToFightWith()
{
   return energy / NUM_ENERGY;
}
