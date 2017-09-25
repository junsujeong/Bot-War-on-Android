//---------------------------------------------------------------------
// Name:    Junsu Jeong
// Project: Program 3, Bot war on Android
// Purpose: 
//---------------------------------------------------------------------

#include "JeongBot.h"

int JeongBot::numCreated = 0;
int JeongBot::numDestroyed = 0;

JeongBot::JeongBot(int x, int y, int width, int height, int energy) : VBot(x, y, width, height, energy)
{
   InitGraphics();
   numCreated++;
   xSpeed = (rand() % CONTROL_INIT_SPEED);
   ySpeed = (rand() % CONTROL_INIT_SPEED);
}

JeongBot::~JeongBot()
{
   JeongBot::numDestroyed++;
}

int JeongBot::NumCreated()
{
   return numCreated;
}

int JeongBot::NumDestroyed()
{
   return numDestroyed;
}

void JeongBot::ResetCounters()
{
   numCreated = 0;
   numDestroyed = 0;
}

void JeongBot::Move()
{
   if (xPos > screenWidth)
   {
      xPos = screenWidth;
      xSpeed = -xSpeed;
   }
   if (yPos > screenHeight)
   {
      yPos = screenHeight;
      ySpeed = -ySpeed;
   }
   if (xPos < 1)
   {
      xPos = 1;
      xSpeed = -xSpeed;
   }
   if (yPos < 1)
   {
      yPos = 1;
      ySpeed = -ySpeed;
   }

   //generate 4-ways random movement
   int randomMove = rand() % GENERATE_UNDER_HUNDRED + 1;
   if (randomMove <= RANDOM_MOVE_CASE_ONE)
      xPos += xSpeed * (rand() % CONTROL_SPEED);
   else if (randomMove <= RANDOM_MOVE_CASE_TWO)
      xPos -= xSpeed * (rand() % CONTROL_SPEED);
   else if (randomMove <= RANDOM_MOVE_CASE_THR)
      yPos += ySpeed * (rand() % CONTROL_SPEED);
   else
      yPos -= ySpeed * (rand() % CONTROL_SPEED);
   xPos += xSpeed;
   yPos += ySpeed;
}

int JeongBot::EnergyToFightWith()
{
   return energy % CONTROL_ENERGY_TO_FIGHT;
}
