/**
 * I lost again.
 * @author Chris Brenton
 * @date 12-26-11
 */

#include "Game.h"

using namespace sf;

Game::Game(RenderWindow *_window) : window(_window)
{
   if (!hudFont.LoadFromFile("resources/Orbitron/orbitron-medium.otf"))
   {
      perror("loading font");
      exit(EXIT_FAILURE);
   }

   String fpsText;
   fpsText.SetFont(hudFont);
   fpsText.SetScale(0.5f, 0.5f);
   fpsText.Move(window->GetWidth() - 150.f, window->GetHeight() - 30.f);
   fpsText.SetColor(Color(255, 255, 255));

   addText("fps", fpsText);
}

void Game::addText(std::string varName, String varText)
{
   textMap.insert(std::pair<std::string, String>(varName, varText));
}

void Game::toggleTextVisibility(std::string varName)
{
   std::map<std::string, String>::iterator it;
   it = textMap.find(varName);
   sf::Color newColor = (*it).second.GetColor();
   int a = newColor.a;
   // TODO: Make this allow partial text transparency.
   if (a == 0)
   {
      newColor.a = 255;
   }
   else
   {
      newColor.a = 0;
   }
   (*it).second.SetColor(newColor);
}

void Game::updateText(std::string varName, std::string varText)
{
   std::map<std::string, String>::iterator it;
   it = textMap.find(varName);
   (*it).second.SetText(varText);
}

void Game::updateFramerate(float tick)
{
   // Get framerate.
   float fps = 1.f / tick;
   fpsStream.str(std::string());
   fpsStream << "FPS: " << std::fixed << std::setprecision(2) << fps;
   updateText("fps", fpsStream.str());
}

void Game::update(float tick)
{
   // TODO: Update here.
   updateFramerate(tick);
}

void Game::toggleFramerate()
{
   toggleTextVisibility("fps");
}

void Game::drawAllText()
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
   std::map<std::string, String>::iterator it;
   for (it = textMap.begin(); it != textMap.end(); ++it)
   {
      window->Draw((*it).second);
   }

   // After drawing the text
   glEnable(GL_DEPTH_TEST);
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
   glPopAttrib();
}

void Game::draw()
{
   // TODO: Draw everything.
   drawAllText();
}
