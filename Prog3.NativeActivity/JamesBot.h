//---------------------------------------------------------------------
// Name:    James Etten
// Project: Program 3, Bot Wars, Making bots fight to their deaths.
// Purpose: Created a JamesBot that is used as a bot to fight in
//          the bot battles.
//---------------------------------------------------------------------

#pragma once
#ifndef __JAMES_BOT_H
#define __JAMES_BOT_H
#include "VBot.h"

//---------------------------------------------------------------------
// This class creates, modifies and keeps track of its own creations.
//---------------------------------------------------------------------
class JamesBot : public VBot
{
public:

   //------------------------------------------------------------------
   // Constructor, creates a JamesBot with the given starting position,
   // devices screen height and width, energy for the bot to fight
   // and the direction to move. In addition to initializing the
   // graphics and adding to the created counter.
   // params: x, in.  y, in.  width, in.  height, in.  energy, in.
   //         xMove, in.  yMove, in.
   //------------------------------------------------------------------
   JamesBot(int x, int y, int width, int height, int energy,
      int xMove, int yMove);

   //------------------------------------------------------------------
   // Destructor, counts how many bots have been destroyed.
   //------------------------------------------------------------------
   ~JamesBot();

   //------------------------------------------------------------------
   // Returns the number of created bots.
   //------------------------------------------------------------------
   static int NumCreated();

   //------------------------------------------------------------------
   // Returns the number of destroyed bots.
   //------------------------------------------------------------------
   static int NumDestroyed();

   //------------------------------------------------------------------
   // Resets the counters back to zero.
   //------------------------------------------------------------------
   static void ResetCounters();

   //------------------------------------------------------------------
   // Moves the bot to a new position on the screen.
   //------------------------------------------------------------------
   virtual void Move();

   //------------------------------------------------------------------
   // Returns the energy that the bot gets to fight with.
   //------------------------------------------------------------------
   virtual int EnergyToFightWith();

   //------------------------------------------------------------------
   // Sets up the image for the bot.
   //------------------------------------------------------------------
   virtual void SetUpData();


private:

   static int numCreated;
   static int numDestroyed;
   static float divEnergy;
   int xToMove;
   int yToMove;

};

#endif