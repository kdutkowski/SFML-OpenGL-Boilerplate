/**
 * I lost again.
 * @author Chris Brenton
 * @date 12-26-11
 */

#include "Game.h"

using namespace sf;

Game::Game(RenderWindow *_window) : window(_window)
{
}

void Game::addText(std::string varName, String varText)
{
   textMap.insert(std::pair<std::string, String>(varName, varText));
}

void Game::update(float tick)
{
   // TODO: Update here.
}

void Game::drawAllText()
{
   std::map<std::string, String>::iterator it;
   for (it = textMap.begin(); it != textMap.end(); ++it)
   {
      window->Draw((*it).second);
   }
}

void Game::draw()
{
   // TODO: Draw everything.
   drawAllText();
}
