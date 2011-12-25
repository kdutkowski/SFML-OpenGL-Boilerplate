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
#include <iostream>
#include <string>

#include <SFML/Window.hpp>

using namespace std;

bool running = true;
int width, height, colorDepth;
string windowTitle;
sf::Event event;
sf::Window *app;

void initialize();
void setupGL(int width, int height);
void processEvent(sf::Event e);

void initialize()
{
   // Set up window.
   app = new sf::Window(sf::VideoMode(width, height, colorDepth),
         windowTitle);
   // Setup OpenGL.
   setupGL(width, height);
}

void setupGL(int width, int height)
{
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 5000.0f);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glClearColor(0, 0, 0, 0);
   glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void processEvent(sf::Event e)
{
   // Window closed
   if (e.Type == sf::Event::Closed)
   {
      running = false;
   }

   // Key pressed
   if (e.Type == sf::Event::KeyPressed)
   {
      if (e.Key.Code == sf::Key::Escape)
      {
         running = false;
      }
   }
}

int main(int argc, char **argv)
{
   width = 800;
   height = 600;
   colorDepth = 32;
   windowTitle = "I LIKE TURTLES";

   // Initialize OpenGL.
   initialize();

   // Main loop.
   while (running)
   {
      // Process events.
      while (app->GetEvent(event))
      {
         processEvent(event);
      }
      // Update the main window.
      app->Display();
   }
   
   // Clean up.
   delete app;

   // Exit.
   return EXIT_SUCCESS;
}
