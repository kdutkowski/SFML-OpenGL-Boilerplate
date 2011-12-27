/**
 * The Game class (I just lost).
 * This will undoubtedly become huge and bloated. Hopefully, I'll be able
 * to avoid that.
 * @author Chris Brenton
 * @date 12-26-11
 */

#include <map>
#include <string>
#include <sstream>
#include <iomanip>

#include <SFML/Graphics.hpp>

#ifndef __GAME_H
#define __GAME_H

class Game {
   public:
      Game(sf::RenderWindow *_window);
      virtual ~Game() {};
      void addText(std::string varName, sf::String varText);
      void updateText(std::string varName, std::string varText);
      void updateFramerate(float tick);
      void update(float tick);
      void drawAllText();
      void draw();
   private:
      sf::RenderWindow *window;
      std::map<std::string, sf::String> textMap;
      std::vector<GLuint> bufferVec;
      std::stringstream fpsStream;
      sf::Font hudFont;
};

#endif
