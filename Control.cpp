#include "Control.h"

//#define mIsKey(x,y) (x.Key.Code == Key::y)
#define mIsKey(x,y) (x.IsKeyDown(Key::y))

using namespace std;
using namespace sf;

Control::Control(RenderWindow *windowPtr, Game *gamePtr) :
   boundWindow(windowPtr), boundGame(gamePtr)
{
}

void Control::controlKeys()
{
   const Input& input = boundWindow->GetInput();
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

void Control::triggerKeyDown(Event e)
{
   // Keys that trigger events go here (i.e. activate once on keypress).
   if (e.Key.Code == Key::F1)
   {
      boundGame->toggleFramerate();
   }
}

void Control::triggerKeyUp(Event e)
{
   // Same as triggerKeyDown, but for keys that trigger on release.
   if (e.Key.Code == Key::Q)
   {
      //running = false;
      boundWindow->Close();
   }
}
