#pragma once

#include <ncurses.h>
#include <string>

#include "RGB.hpp"

void init();
void draw_character(char ch, RGB color);
void render(std::string& text);
