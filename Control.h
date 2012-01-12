/**
 * The Control class.
 * Ideally, all mouse/keyboard controls will go here.
 * @author Chris Brenton
 * @date 1-12-12
 */

#ifndef __CONTROL_H
#define __CONTROL_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Window/Input.hpp>

#include "Game.h"
#include "Keymap.h"

class Control {
   public:
      Control(sf::RenderWindow *windowPtr, Game *gamePtr);
      ~Control() {};
      void controlKeys();
      void triggerKeyDown(sf::Event e);
      void triggerKeyUp(sf::Event e);
   private:
      sf::RenderWindow *boundWindow;
      Game *boundGame;
};

#endif
