/**
 * This contains definitions for key/mouse bindings.
 * THIS IS A HACK.
 * TODO: FIX THIS HACK. Make this a map or something.
 * @author Chris Brenton
 * @date 1-12-12
 */

#ifndef __KEYMAP_H
#define __KEYMAP_H

#include <SFML/Window/Input.hpp>

//#define mIsKey(x,y) (x.Key.Code == Key::y)
#define mIsKey(x,y) (x.IsKeyDown(sf::Key::y))

#define IS_MOVE_FORWARD mIsKey(input,W)
#define IS_MOVE_BACK mIsKey(input,S)
#define IS_MOVE_LEFT mIsKey(input,A)
#define IS_MOVE_RIGHT mIsKey(input,D)

#define IS_CLICK input.IsMouseButtonDown(sf::Mouse::Left)
#define IS_RCLICK input.IsMouseButtonDown(sf::Mouse::Right)
#define IS_MCLICK input.IsMouseButtonDown(sf::Mouse::Middle)

#endif
