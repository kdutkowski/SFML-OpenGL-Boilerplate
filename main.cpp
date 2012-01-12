#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game.h"
#include "Control.h"

#define FPS_MAX 60

using namespace std;
using namespace sf;

bool running = true;
bool novid = false;
int width, height, colorDepth;
string windowTitle;
Font hudFont;
float tick;
stringstream fpsStream;
RenderWindow *app;
Control *gameControl;
sf::Clock myClock;

void initialize();
void setupGL(int width, int height);
void resize(Event e);
void controlKeys();
void triggerKeyDown(Event e);
void triggerKeyUp(Event e);
void processEvent(Event e);
void drawText(vector<String> textVec);

void initialize()
{
   // Setup OpenGL.
   setupGL(width, height);

   if (!hudFont.LoadFromFile("resources/Orbitron/orbitron-medium.otf"))
   {
      perror("loading font");
      exit(EXIT_FAILURE);
   }

   app->SetFramerateLimit(FPS_MAX);
}

void setupGL(int width, int height)
{
   // Set color and depth clear value
   glClearDepth(1.f);
   glClearColor(0.f, 0.f, 0.f, 0.f);

   // Enable Z-buffer read and write
   glEnable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);

   // Setup a perspective projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(90.f, 1.f, 1.f, 500.f);
}

void resize(Event e)
{
   cout << "Window resized to " << app->GetWidth() << " x " <<
      app->GetHeight() << endl;
   glViewport(0, 0, e.Size.Width, e.Size.Height);
}

void processEvent(Event e)
{
   // Window resized.
   if (e.Type == Event::Resized)
   {
      resize(e);
   }

   // Key pressed.
   if (e.Type == Event::KeyPressed)
   {
      gameControl->triggerKeyDown(e);
   }
   else if (e.Type == Event::KeyReleased)
   {
      gameControl->triggerKeyUp(e);
   }

   /*
      if (e.Type == Event::KeyPressed ||
      e.Type == Event::KeyReleased ||
      e.Type == Event::MouseButtonPressed ||
      e.Type == Event::MouseButtonReleased ||
      e.Type == Event::JoyButtonPressed ||
      e.Type == Event::JoyButtonReleased)
      */
}

void drawText(vector<String> textVec)
{
   // Before drawing text.
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT |
         GL_TEXTURE_BIT | GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);

   glDisable(GL_ALPHA_TEST);
   glDisable(GL_DEPTH_TEST);
   glDisable(GL_LIGHTING);
   glDisable(GL_DEPTH_TEST);

   // Draw text.
   for (vector<String>::iterator i = textVec.begin(); i != textVec.end(); ++i)
   {
      app->Draw((*i));
   }

   // After drawing the text
   glEnable(GL_DEPTH_TEST);
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
   glPopAttrib();
}

int main(int argc, char **argv)
{
   width = 800;
   height = 600;
   colorDepth = 32;
   windowTitle = "I LIKE TURTLES";
   tick = 0.f;
   Event event;

   // Parse and handle command line arguments.
   struct option longOptions[] =
   {
      {"debug", 0, 0, 'd'},
      {"novid", 0, 0, 'n'},
      {0, 0, 0, 0}
   };
   int optionIndex = 0;
   int optResult = -1;

   do
   {
      optResult = getopt_long (argc, argv, "dn", longOptions, &optionIndex);
      switch (optResult)
      {
      case 0:
         printf ("option %s (%d)", longOptions[optionIndex].name, optind);
         if (optarg)
         {
            printf (" with arg %s", optarg);
         }
         printf ("\n");
         break;
      case 'n':
         printf("-n novid flag\n");
         novid = true;
         break;
      case 'd':
         printf("debug flag\n");
         break;
      }
   } while (optResult != -1);

   // Set up window.
   app = new RenderWindow(VideoMode(width, height, colorDepth), windowTitle);

   app->Show(!novid);

   Game theGame(app);
   gameControl = new Control(app, &theGame);

   // Initialize OpenGL.
   initialize();

   // Main loop.
   while (app->IsOpened())
   {
      // Process events.
      gameControl->controlKeys();
      while (app->GetEvent(event))
      {
         processEvent(event);
      }

      tick = app->GetFrameTime();

      // Clear the window.
      app->Clear();

      // Draw the game (I just lost). This is OpenGL.
      theGame.update(tick);
      theGame.draw();

      // Update the main window. This is SFML.
      if (!novid)
      {
         app->Display();
      }
   }

   // Clean up.
   app->Close();
   delete app;
   delete gameControl;

   // Exit.
   return EXIT_SUCCESS;
}
