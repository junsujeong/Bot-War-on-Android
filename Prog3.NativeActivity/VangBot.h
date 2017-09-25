//---------------------------------------------------------------------
// Name:    Vang Xiong
// Project: Program 3, Bot Wars, Making bots fight to their deaths.
// Purpose: This header file which is the descendant class of VBot and
//          will be used to help destroy the other bots.
//---------------------------------------------------------------------
#ifndef __VangBot_h
#define __VangBot_h

#include "VBot.h"
#include <cstdlib>
// ----------------------------------------------------------------
// This class extends the VBot class and creates VangBot
// ----------------------------------------------------------------
class VangBot : public VBot
{
public:
   // ----------------------------------------------------------------
   // This constructor has the information given to create the bot at
   // the certain locations of the screen and giving the bot the 
   // energy generated.
   // Params: x: in, y: in, width: in, height: in, energy: in. 
   // ----------------------------------------------------------------
   VangBot(int x, int y, int width, int height, int energy);

   // ----------------------------------------------------------------
   // Destructor keeping track of number destroyed of bots.
   // ----------------------------------------------------------------
   ~VangBot() { numDestroyed++; }

   // ----------------------------------------------------------------
   // Returns the number of created bots.
   // ----------------------------------------------------------------
   static int NumBotCreated() { return numCreated; }

   // ----------------------------------------------------------------
   // Returns the number of bots destroyed. 
   // ----------------------------------------------------------------
   static int NumBotDestroy() { return numDestroyed; }

   // ----------------------------------------------------------------
   // Resets the counter.
   // ----------------------------------------------------------------
   static void ResetCounter();

   // ----------------------------------------------------------------
   // This is the unique move function of VangBot.
   // ----------------------------------------------------------------
   virtual void Move();

   // ----------------------------------------------------------------
   // Energy that the bot has to fight.
   // ----------------------------------------------------------------
   virtual int EnergyToFightWith();

   // ----------------------------------------------------------------
   // Has the information in oder to make the bot.
   // ----------------------------------------------------------------
   virtual void SetUpData();


private:
   static int numCreated;
   static int numDestroyed;
   static int _TWO;
   static int _TEN;
   int xToMove;
   int yToMove;
   
   static float NUM_ENERGY;
};

#endif