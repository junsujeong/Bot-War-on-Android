//---------------------------------------------------------------------
// Name:    James Etten, Junsu Jeong, Vang Xiong. 
// Project: Program 3, Bot Wars, Making bots fight to their deaths.
// Purpose: Holds created bots in a list and modifies them through,
//          adding new bots, drawing the bots, moving them, doing
//          battles and removing dead bots.
//---------------------------------------------------------------------

#pragma once
#ifndef __BOTLIST_H
#define __BOTLIST_H

#include "VBot.h"

//---------------------------------------------------------------------
// This class hold bots in a list and modifies them.
//---------------------------------------------------------------------
class BotList
{
public:

   //------------------------------------------------------------------
   // Constructor, creates a list to hold bots.
   //------------------------------------------------------------------
   BotList() : VBotPtr(NULL) { }

   //------------------------------------------------------------------
   // Destructor, deletes all of the bots currently in the list.
   //------------------------------------------------------------------
   ~BotList();

   //------------------------------------------------------------------
   // Moves all of the bots to another location on the screen.
   //------------------------------------------------------------------
   void Move();

   //------------------------------------------------------------------
   // Adds a new bot to the list of bots.
   // params: Ptr, in.
   //------------------------------------------------------------------
   void Add(VBot *Ptr);

   //------------------------------------------------------------------
   // Removes a bot from the list if its energy is at or below zero.
   //------------------------------------------------------------------
   void Remove();

   //------------------------------------------------------------------
   // Draws all of the bots on the screen.
   //------------------------------------------------------------------
   void Draw();

   //------------------------------------------------------------------
   // Battles two bots that are currently touching.
   //------------------------------------------------------------------
   void Battle();

private:

   //------------------------------------------------------------------
   // Creates a node for holding a bot.
   //------------------------------------------------------------------
   struct Node
   {
      Node(VBot * x, Node * p = NULL) : botPtr(x), next(p) { }
      VBot * botPtr;
      Node * next;
   };

   Node *VBotPtr;

   //------------------------------------------------------------------
   // Copy Constructor, not used and not to be used.
   //------------------------------------------------------------------
   BotList(const BotList & copyFrom);

   //------------------------------------------------------------------
   // Assignment operator, not used and not to be used.
   //------------------------------------------------------------------
   BotList & operator= (const BotList & assignFrom);
};
#endif
