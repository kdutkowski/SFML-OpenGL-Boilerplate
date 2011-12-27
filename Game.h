/**
 * The Game class (I just lost).
 * This will undoubtedly become huge and bloated. Hopefully, I'll be able
 * to avoid that.
 * @author Chris Brenton
 * @date 12-26-11
 */

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#ifndef __GAME_H
#define __GAME_H

class Game {
   public:
      Game(sf::RenderWindow *_window);
      virtual ~Game() {};
      void addText(std::string varName, sf::String varText);
      void update(float tick);
      void drawAllText();
      void draw();
   private:
      sf::RenderWindow *window;
      std::map<std::string, sf::String> textMap;
};

#endif
