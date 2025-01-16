#pragma once

#include <ncurses.h>
#include <string>
#include <vector>

#include "RGB.hpp"

void init();
void draw_character(char ch, size_t posx, size_t posy, RGB color);
void render(std::vector<std::string>& text);
