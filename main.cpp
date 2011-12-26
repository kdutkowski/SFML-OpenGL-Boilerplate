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
#include <SFML/Window/Input.hpp>

#define FPS_MAX 60

//#define mIsKey(x,y) (x.Key.Code == Key::y)
#define mIsKey(x,y) (x.IsKeyDown(Key::y))

using namespace std;
using namespace sf;

bool running = true;
bool showFramerate = true;
int width, height, colorDepth;
string windowTitle;
Font hudFont;
String text;
float tick, fps;
stringstream fpsStream;
RenderWindow *app;

void initialize();
void setupGL(int width, int height);
void resize();
void controlKeys();
void triggerKeyDown(Event e);
void triggerKeyUp(Event e);
void processEvent(Event e);
void updateFramerate();

void initialize()
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

   app->SetFramerateLimit(FPS_MAX);
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

void resize()
{
   cout << "Window resized to " << app->GetWidth() << " x " <<
      app->GetHeight() << endl;
}

void controlKeys()
{
   const Input& input = app->GetInput();
   // Keys that are used as controls go here (i.e. activate while held).
   if (mIsKey(input,W))
   {
      cout << "W" << endl;
   }
   if (mIsKey(input,A))
   {
      cout << "A" << endl;
   }
   if (mIsKey(input,S))
   {
      cout << "S" << endl;
   }
   if (mIsKey(input,D))
   {
      cout << "D" << endl;
   }
   if (input.IsMouseButtonDown(Mouse::Left))
   {
      cout << "LEFT MOUSE" << endl;
   }
}

void triggerKeyDown(Event e)
{
   // Keys that trigger events go here (i.e. activate once on keypress).
   if (e.Key.Code == Key::F1)
   {
      showFramerate = !showFramerate;
   }
}

void triggerKeyUp(Event e)
{
   // Same as triggerKeyDown, but for keys that trigger on release.
   if (e.Key.Code == Key::Q)
   {
      running = false;
   }
}

void processEvent(Event e)
{
   // Window closed.
   if (e.Type == Event::Closed)
   {
      running = false;
   }

   // Window resized.
   if (e.Type == Event::Resized)
   {
      resize();
   }

   /*
      if (e.Type == Event::KeyPressed ||
      e.Type == Event::KeyReleased ||
      e.Type == Event::MouseButtonPressed ||
      e.Type == Event::MouseButtonReleased ||
      e.Type == Event::JoyButtonPressed ||
      e.Type == Event::JoyButtonReleased)
   */

   // Key pressed.
   if (e.Type == Event::KeyPressed)
   {
      triggerKeyDown(e);
   }
   else if (e.Type == Event::KeyReleased)
   {
      triggerKeyUp(e);
   }
}

void updateFramerate()
{
   // Get framerate.
   tick = app->GetFrameTime();
   fps = 1.f / tick;
   fpsStream.str(string());
   fpsStream << "FPS: " << fixed << setprecision(2) << fps;
   text.SetText(fpsStream.str());
   // Display the framerate.
   app->Draw(text);
}

int main(int argc, char **argv)
{
   width = 800;
   height = 600;
   colorDepth = 32;
   windowTitle = "I LIKE TURTLES";
   tick = 0.f;
   Event event;

   // Set up window.
   app = new RenderWindow(VideoMode(width, height, colorDepth), windowTitle);

   // Initialize OpenGL.
   initialize();

   // Main loop.
   while (running)
   {
      // Clear the window.
      app->Clear();

      // Process events.
      controlKeys();
      while (app->GetEvent(event))
      {
         processEvent(event);
      }
      if (showFramerate)
      {
         updateFramerate();
      }
      // Update the main window.
      app->Display();
   }

   // Clean up.
   app->Close();
   delete app;

   // Exit.
   return EXIT_SUCCESS;
}
