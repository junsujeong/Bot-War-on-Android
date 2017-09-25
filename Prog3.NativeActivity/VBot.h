//---------------------------------------------------------------------
// Name:    James Etten, Junsu Jeong, Vang Xiong. 
// Project: Program 3, Bot Wars, Making bots fight to their deaths.
// Purpose: Parent class of different bots. Holds methods that are
//          used by VBots.
//---------------------------------------------------------------------

#ifndef __VBOT_H
#define __VBOT_H

//---------------------------------------------------------------------
// This class handles and makes VBots.
//---------------------------------------------------------------------
class VBot
{
public:

   //------------------------------------------------------------------
   // Constructor, Creates a VBot with the given information of the
   // bot's initial stating location, the screen height and width of
   // the device and the energy for the bot.
   // params: startX_Pos, in.  startY_Pos, in.  scrWidth, in.
   //         scrHeight, in.  startEnergy, in.
   //------------------------------------------------------------------
   VBot(int startX_Pos, int startY_Pos,
      int scrWidth, int scrHeight, int startEnergy) :
      xPos(startX_Pos), yPos(startY_Pos),
      screenWidth(scrWidth), screenHeight(scrHeight),
      energy(startEnergy)
   { }

   //------------------------------------------------------------------
   // This method creates the graphics which sets up the colors of
   // the objects.
   //------------------------------------------------------------------
   bool InitGraphics();

   //------------------------------------------------------------------
   // Destructor for VBot.
   //------------------------------------------------------------------
   virtual ~VBot() { }

   //------------------------------------------------------------------
   // Moves a bot from its current location to a new location.
   //------------------------------------------------------------------
   virtual void Move() = 0;

   //------------------------------------------------------------------
   // The given amount of energy the bot has to fight with.
   //------------------------------------------------------------------
   virtual int EnergyToFightWith() = 0;

   //------------------------------------------------------------------
   // Returns true if the bot's energy is less than or equal to zero.
   //------------------------------------------------------------------
   bool IsDead() const { return energy <= 0; }

   //------------------------------------------------------------------
   // This method draws the VBots on the screen after each refresh.
   //------------------------------------------------------------------
   void Draw();

   //------------------------------------------------------------------
   // This method checks if two VBots have collided with each other
   // and returns true if two have collided, false otherwise.
   // params: b, in.
   //------------------------------------------------------------------
   bool CollidedWith(VBot * b) const;

   //------------------------------------------------------------------
   // This method does battle for two given bots and changes their
   // energy.
   // params: b, in.
   //------------------------------------------------------------------
   void DoBattleWith(VBot * b);

protected:

   int xPos, yPos;
   int width, height;
   int screenWidth, screenHeight;
   int energy;

   GLuint vboVertexHandle;
   GLuint vboColorHandle;
   GLfloat * vertices;
   GLubyte * colors;
   int numPoints;

   virtual void SetUpData() = 0;
};

#endif