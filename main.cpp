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
#include <sstream>
#include <iomanip>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define FPS_MAX 60

#define mIsKey(x,y) (x.Key.Code == Key::y)

using namespace std;
using namespace sf;

bool running = true;
int width, height, colorDepth;
string windowTitle;
Event event;
Font hudFont;
String text;
float tick, fps;
string fpsText;
stringstream fpsStream;

void initialize(RenderWindow &app);
void setupGL(int width, int height);
void processEvent(Event e);

void initialize(RenderWindow &app)
{
   // Setup OpenGL.
   setupGL(width, height);

   if (!hudFont.LoadFromFile("resources/Orbitron/orbitron-medium.otf"))
   {
      perror("loading font");
      exit(EXIT_FAILURE);
   }

   text.SetFont(hudFont);
   text.SetScale(0.5f, 0.5f);
   text.Move(width - 150.f, height - 30.f);

   app.SetFramerateLimit(FPS_MAX);
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

void processEvent(Event e)
{
   // Window closed
   if (e.Type == Event::Closed)
   {
      running = false;
   }

   // Key pressed
   if (e.Type == Event::KeyPressed)
   {
      if (mIsKey(e, Q))
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
   tick = 0.f;
   // Set up window.
   RenderWindow app(VideoMode(width, height, colorDepth), windowTitle);

   // Initialize OpenGL.
   initialize(app);

   // Main loop.
   while (running)
   {
      // Process events.
      while (app.GetEvent(event))
      {
         processEvent(event);
      }
      tick = app.GetFrameTime();
      fps = 1.f / tick;
      fpsStream.str(string());
      fpsStream << "FPS: " << fixed << setprecision(2) << fps;
      text.SetText(fpsStream.str());
      app.Clear();
      app.Draw(text);
      // Update the main window.
      app.Display();
   }
   
   // Clean up.
   app.Close();

   // Exit.
   return EXIT_SUCCESS;
}
