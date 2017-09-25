//---------------------------------------------------------------------
// Name:    James Etten, Junsu Jeong, Vang Xiong. 
// Project: Program 3, Bot Wars, Making bots fight to their deaths.
// Purpose: Holds created bots in a list and modifies them through,
//          adding new bots, drawing the bots, moving them, doing
//          battles and removing dead bots.
//---------------------------------------------------------------------

#include "BotList.h"

//------------------------------------------------------------------
// Destructor, deletes all of the bots currently in the list.
//------------------------------------------------------------------
BotList::~BotList()
{
   while (VBotPtr != NULL)
   {
      Node * temp = VBotPtr;
      VBotPtr = temp->next;
      delete temp;
   }
}

//------------------------------------------------------------------
// Moves all of the bots to another location on the screen.
//------------------------------------------------------------------
void BotList::Move()
{
   if (VBotPtr != NULL)
   {
      Node * temp = VBotPtr;
      while (temp != NULL)
      {
         temp->botPtr->Move();
         temp = temp->next;
      }
   }
}

//------------------------------------------------------------------
// Adds a new bot to the list of bots.
// params: Ptr, in.
//------------------------------------------------------------------
void BotList::Add(VBot * Ptr)
{
   if (VBotPtr == NULL)
      VBotPtr = new Node(Ptr, NULL);
   else
      VBotPtr = new Node(Ptr, VBotPtr);
}

//------------------------------------------------------------------
// Removes a bot from the list if its energy is at or below zero.
//------------------------------------------------------------------
void BotList::Remove()
{
   Node *fp = VBotPtr, *bp = NULL;
   while (fp != NULL && !(fp->botPtr->IsDead()))
   {
      bp = fp;
      fp = fp->next;
   }
   if (fp != NULL)
   {
      if (bp == NULL)
         VBotPtr = VBotPtr->next;
      else
         bp->next = fp->next;
      delete fp->botPtr;
      delete fp;
   }
}

//------------------------------------------------------------------
// Draws all of the bots on the screen.
//------------------------------------------------------------------
void BotList::Draw()
{
   if (VBotPtr != NULL)
   {
      Node * temp = VBotPtr;
      while (temp != NULL)
      {
         temp->botPtr->Draw();
         temp = temp->next;
      }
      delete temp;
   }

}

//------------------------------------------------------------------
// Battles two bots that are currently touching.
//------------------------------------------------------------------
void BotList::Battle()
{
   if (VBotPtr != NULL)
   {
      Node *temp = VBotPtr;
      Node *tempTwo = VBotPtr;
      while (temp != NULL)
      {
         while (tempTwo != NULL)
         {
            if (temp->botPtr->CollidedWith(tempTwo->botPtr))
               temp->botPtr->DoBattleWith(tempTwo->botPtr);
            tempTwo = tempTwo->next;
         }
         temp = temp->next;
      }
      delete temp;
      delete tempTwo;
   }
}
