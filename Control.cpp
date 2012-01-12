/**
 * @author Chris Brenton
 * @date 1-12-12
 */

#include "Control.h"

using namespace std;
using namespace sf;

Control::Control(RenderWindow *windowPtr, Game *gamePtr) :
   boundWindow(windowPtr), boundGame(gamePtr)
{
}

/**
 * "Control" keys are ones that should be handled even when focus is lost. For
 * example, if the player is holding down the "move forward" key and accidentally
 * clicks outside of the window, they should not continue to move forward if the key
 * is released. The handlers for these will be called on keypress; they do not have
 * to be polled. Key definitions are in "Keymap.h".
 */
void Control::controlKeys()
{
   const Input& input = boundWindow->GetInput();
   // Keys that are used as controls go here (i.e. activate while held).
   if (IS_MOVE_FORWARD)
   {
      cout << "W" << endl;
   }
   if (IS_MOVE_BACK)
   {
      cout << "A" << endl;
   }
   if (IS_MOVE_LEFT)
   {
      cout << "S" << endl;
   }
   if (IS_MOVE_RIGHT)
   {
      cout << "D" << endl;
   }
   if (IS_CLICK)
   {
      cout << "LEFT MOUSE" << endl;
   }
   if (IS_RCLICK)
   {
      cout << "RIGHT MOUSE" << endl;
   }
   if (IS_MCLICK)
   {
      cout << "MIDDLE MOUSE" << endl;
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
