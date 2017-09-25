//---------------------------------------------------------------------
// Name:    Junsu Jeong
// Project: Program 3, Bot war on Android
// Purpose: This class which is descendent class that inherit from 
//          virtual VBot class which has its own movement pattern 
//          and strategy in EnergyToFightWith. This class will be used 
//          as a Bot in this program
//---------------------------------------------------------------------

#pragma once
#ifndef __JeongBot_H
#define __JeongBot_H
#include "VBot.h"
#include <cstdlib> 

//---------------------------------------------------------------------
// creates the bot which will be used in Bot fight. This class will
// have movement and fighting strategy of the bot. Also, keep track
// of the energy, numCreated, and numDestroyed of the Bot
//---------------------------------------------------------------------
class JeongBot : public VBot
{
public:

   //------------------------------------------------------------------
   // Constructor of the JeongBot class which set the starting X-axis,
   // y-axis, initial energy of the bot, gets the screen width, height.
   // it also calls InitGraphics() which initialize the graphics of 
   // the bot and increments the number of bot created 
   // param int x, int y, int width, int height, int energy
   //------------------------------------------------------------------
   JeongBot(int x, int y, int width, int height, int energy);

   //------------------------------------------------------------------
   // Destructor of the JeongBot class
   // Basically it increment the number of destroyed
   //------------------------------------------------------------------
   ~JeongBot();

   //------------------------------------------------------------------
   // Static int 
   // Returns the number of bots that was created.
   //------------------------------------------------------------------
   static int NumCreated();

   //------------------------------------------------------------------
   // Returns the number of bots that was destroyed.
   //------------------------------------------------------------------
   static int NumDestroyed();

   //------------------------------------------------------------------
   // Resets the number of bots that were created and destroyed
   //------------------------------------------------------------------
   static void ResetCounters();

   //------------------------------------------------------------------
   // Move method that moves bot, this method makes bot to move
   // randomly in 4 ways (up, down, left, right) and moves diagonally
   // in order the bot to be smooth and have more ative movement
   //------------------------------------------------------------------
   virtual void Move();

   //------------------------------------------------------------------
   // returns the energy to fight which will be dealing while Bot fight
   //------------------------------------------------------------------
   virtual int EnergyToFightWith();

   //------------------------------------------------------------------
   // virtual function that sets up vertex and color data
   // in JeongBot_Data file
   //------------------------------------------------------------------
   virtual void SetUpData();


private:

   static int numCreated;
   static int numDestroyed;
   static const int RANDOM_MOVE_CASE_ONE = 25;
   static const int RANDOM_MOVE_CASE_TWO = 50;
   static const int RANDOM_MOVE_CASE_THR = 75;
   static const int GENERATE_UNDER_HUNDRED = 100;
   static const int CONTROL_SPEED = 3;
   static const int CONTROL_ENERGY_TO_FIGHT = 10;
   static const int CONTROL_INIT_SPEED = 30;
   int xSpeed;
   int ySpeed;
};

#endif