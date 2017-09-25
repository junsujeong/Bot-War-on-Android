// botlist->Remove(); only removes 1
// all missed questions about linked list
// BotList::Battle() is wrong - checks first against all (including itself)
// JamesBot - EnergyToFightWith() cn return 0.  Movement is light
// JeongBot::EnergyToFightWith() can return 0
// int VangBot::EnergyToFightWith() can return 0


/*
* Copyright (C) 2010 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

//---------------------------------------------------------------------
// Name:    James Etten, Junsu Jeong, Vang Xiong. 
// Project: Program 3, Bot Wars, Making bots fight to their deaths.
// Purpose: Runs the bot game through calling methods in BotList,
//          GL_Button, IntegerDisplay and interacts with the user.
//---------------------------------------------------------------------

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "AndroidProject1.NativeActivity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "AndroidProject1.NativeActivity", __VA_ARGS__))

#include "VBot.h"
#include "BotList.h"
#include "IntegerDisplay.h"
#include "GL_Button.h"
#include "JeongBot.h"
#include "JamesBot.h"
#include "VangBot.h"
#include <cstdlib> 

static BotList * botlist;
static GL_Button *btnAddBotType1, *btnAddBotType2, *btnAddBotType3;

const int DIS_C_X = 60;
const int DIS_C_X_TO_X = 200;
const int DIS_D_X = 160;
const int DIS_D_X_TO_X = 200;
const int DIS_CD_Y = 100;
const int BUT_X = 100;
const int BUT_X_TO_X = 200;
const int BUT_Y = 40;
const int BUT_1_NUM = 1;
const int BUT_2_NUM = 2;
const int BUT_3_NUM = 3;
const int SCALE_DIS = 2;
const int RN_MOD_LOC = 20;
const int RN_MOD_ENE = 50;

//------------------------------------------------------------------
// Shared state for our app.
//------------------------------------------------------------------
struct engine
{
   struct android_app* app;

   int animating;
   EGLDisplay display;
   EGLSurface surface;
   EGLContext context;
   int32_t width;
   int32_t height;
};

//------------------------------------------------------------------
// Initialize an EGL context for the current display.
//------------------------------------------------------------------
static int engine_init_display(struct engine* engine)
{
   /*
   * Here specify the attributes of the desired configuration.
   * Below, we select an EGLConfig with at least 8 bits per color
   * component compatible with on-screen windows
   */
   const EGLint attribs[] = {
      EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
      EGL_BLUE_SIZE, 8,
      EGL_GREEN_SIZE, 8,
      EGL_RED_SIZE, 8,
      EGL_NONE
   };
   EGLint w, h, format;
   EGLint numConfigs;
   EGLConfig config;
   EGLSurface surface;
   EGLContext context;

   EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

   eglInitialize(display, 0, 0);

   /* Here, the application chooses the configuration it desires. In this
   * sample, we have a very simplified selection process, where we pick
   * the first EGLConfig that matches our criteria */
   eglChooseConfig(display, attribs, &config, 1, &numConfigs);

   /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
   * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
   * As soon as we picked a EGLConfig, we can safely reconfigure the
   * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
   eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

   ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

   surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);
   context = eglCreateContext(display, config, NULL, NULL);

   if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
   {
      LOGW("Unable to eglMakeCurrent");
      return -1;
   }

   eglQuerySurface(display, surface, EGL_WIDTH, &w);
   eglQuerySurface(display, surface, EGL_HEIGHT, &h);

   engine->display = display;
   engine->context = context;
   engine->surface = surface;
   engine->width = w;
   engine->height = h;

   glDisable(GL_DEPTH_TEST);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrthof(0, w, h, 0, -1, 1);
   glMatrixMode(GL_MODELVIEW);

   IntegerDisplay::Initialize();
   botlist = new BotList();

   JamesBot::ResetCounters();
   JeongBot::ResetCounters();
   VangBot::ResetCounter();
   btnAddBotType1 = new GL_Button(BUT_X, BUT_Y, BUT_1_NUM, SCALE_DIS);
   btnAddBotType2 = new GL_Button(BUT_X + BUT_X_TO_X, BUT_Y, BUT_2_NUM, SCALE_DIS);
   btnAddBotType3 = new GL_Button(BUT_X + BUT_X_TO_X + BUT_X_TO_X, BUT_Y, BUT_3_NUM, SCALE_DIS);
   return 0;
}

//------------------------------------------------------------------
// Just the current frame in the display.
//------------------------------------------------------------------
static void engine_draw_frame(struct engine* engine)
{
   if (engine->display == NULL)
   {
      return;
   }

   glClearColor(0, 0, 0, 1);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   botlist->Move();
   botlist->Draw();
   botlist->Battle();
   botlist->Remove();

   btnAddBotType1->Draw();
   btnAddBotType2->Draw();
   btnAddBotType3->Draw();

   int numCreatedJames = JamesBot::NumCreated();
   IntegerDisplay::Instance()->DisplayIntAt(DIS_C_X, DIS_CD_Y, numCreatedJames, SCALE_DIS);
   int numCreatedJeong = JeongBot::NumCreated();
   IntegerDisplay::Instance()->DisplayIntAt(DIS_C_X + DIS_C_X_TO_X, DIS_CD_Y, numCreatedJeong, SCALE_DIS);
   int numCreatedVang = VangBot::NumBotCreated();
   IntegerDisplay::Instance()->DisplayIntAt(DIS_C_X + DIS_C_X_TO_X + DIS_C_X_TO_X, 
                                            DIS_CD_Y, numCreatedVang, SCALE_DIS);
   int numDestroyedJames = JamesBot::NumDestroyed();
   IntegerDisplay::Instance()->DisplayIntAt(DIS_D_X, DIS_CD_Y, numDestroyedJames, SCALE_DIS);
   int numDestroyedJeong = JeongBot::NumDestroyed();
   IntegerDisplay::Instance()->DisplayIntAt(DIS_D_X + DIS_D_X_TO_X, DIS_CD_Y, numDestroyedJeong, SCALE_DIS);
   int numDestroyedVang = VangBot::NumBotDestroy();
   IntegerDisplay::Instance()->DisplayIntAt(DIS_D_X + DIS_D_X_TO_X + DIS_D_X_TO_X, 
                                            DIS_CD_Y, numDestroyedVang, SCALE_DIS);

   eglSwapBuffers(engine->display, engine->surface);
}

//------------------------------------------------------------------
// Tear down the EGL context currently associated with the display.
//------------------------------------------------------------------
static void engine_term_display(struct engine* engine)
{
   if (engine->display != EGL_NO_DISPLAY)
   {
      eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
      if (engine->context != EGL_NO_CONTEXT)
      {
         eglDestroyContext(engine->display, engine->context);
      }
      if (engine->surface != EGL_NO_SURFACE)
      {
         eglDestroySurface(engine->display, engine->surface);
      }
      eglTerminate(engine->display);
   }
   engine->animating = 0;
   engine->display = EGL_NO_DISPLAY;
   engine->context = EGL_NO_CONTEXT;
   engine->surface = EGL_NO_SURFACE;
}

//------------------------------------------------------------------
// Process the next input event.
//------------------------------------------------------------------
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event)
{
   VBot * vbotPtr;

   struct engine* engine = (struct engine*)app->userData;
   if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
   {
      // Handle the button touches
      if (AInputEvent_getSource(event) == AINPUT_SOURCE_TOUCHSCREEN)
      {
         // Location of Button press
         int x = AMotionEvent_getX(event, 0);
         int y = AMotionEvent_getY(event, 0);

         int action = AKeyEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
         switch (action)
         {
         case AMOTION_EVENT_ACTION_DOWN:

            if (btnAddBotType1->PressInside(x, y))
            {
               vbotPtr = new JamesBot(rand() % (engine->width), rand() % (engine->height),
                                      engine->width, engine->height, (rand() % RN_MOD_ENE) + 1,
                                      rand() % RN_MOD_LOC, rand() % RN_MOD_LOC);
               botlist->Add(vbotPtr);
            }
            else if (btnAddBotType2->PressInside(x, y))
            {
               vbotPtr = new JeongBot(rand() % (engine->width), rand() % (engine->height), 
                                      engine->width, engine->height, (rand() % RN_MOD_ENE) + 1);
               botlist->Add(vbotPtr);
            }
            else if (btnAddBotType3->PressInside(x, y))
            {
               vbotPtr = new VangBot(rand() % (engine->width), rand() % (engine->height),
                                     engine->width, engine->height, (rand() % RN_MOD_ENE) + 1);
               botlist->Add(vbotPtr);
            }

            break;
         case AMOTION_EVENT_ACTION_UP:

            break;
         case AMOTION_EVENT_ACTION_MOVE:

            break;
         }
      }

      engine->animating = 1;

      return 1;
   }
   return 0;
}

//------------------------------------------------------------------
// Process the next main command.
//------------------------------------------------------------------
static void engine_handle_cmd(struct android_app* app, int32_t cmd)
{
   struct engine* engine = (struct engine*)app->userData;
   switch (cmd)
   {
   case APP_CMD_SAVE_STATE:
      break;
   case APP_CMD_INIT_WINDOW:
      if (engine->app->window != NULL)
      {
         engine_init_display(engine);
         engine_draw_frame(engine);
         engine->animating = 1;
      }
      break;
   case APP_CMD_TERM_WINDOW:
      engine_term_display(engine);
      break;
   case APP_CMD_GAINED_FOCUS:
      break;
   case APP_CMD_LOST_FOCUS:
      engine->animating = 0;
      engine_draw_frame(engine);
      break;
   }
}

//-------------------------------------------------------------------
// This is the main entry point of a native application that is using
// android_native_app_glue.  It runs in its own thread, with its own
// event loop for receiving input events and doing other things.
//-------------------------------------------------------------------
void android_main(struct android_app* state)
{
   struct engine engine;

   memset(&engine, 0, sizeof(engine));
   state->userData = &engine;
   state->onAppCmd = engine_handle_cmd;
   state->onInputEvent = engine_handle_input;
   engine.app = state;

   if (state->savedState != NULL)
   {

   }

   engine.animating = 1;

   while (1)
   {
      int ident;
      int events;
      struct android_poll_source* source;

      while ((ident = ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,
         (void**)&source)) >= 0)
      {
         if (source != NULL)
         {
            source->process(state, source);
         }
         if (state->destroyRequested != 0)
         {
            engine_term_display(&engine);
            return;
         }
      }

      if (engine.animating)
      {
         struct timespec ts;
         ts.tv_sec = 0;
         ts.tv_nsec = 100000000U;
         nanosleep(&ts, &ts);
         engine_draw_frame(&engine);
      }
   }
}
