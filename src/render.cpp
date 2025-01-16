#include "render.hpp"
#include <ncurses.h>

void init()
{
    initscr();
    cbreak();             // Line buffering disabled, pass all input to the program
    noecho();             // Don't echo typed characters
    keypad(stdscr, TRUE); // Enable function and arrow keys
    curs_set(0);          // Hide the cursor
    start_color();
}


void draw_character(char ch, size_t posx, size_t posy, RGB color)
{
    short r = (color.r * 1000) / 255;
    short g = (color.g * 1000) / 255;
    short b = (color.b * 1000) / 255;
    short color_id = 10;

    // Initialize the color
    init_color(color_id, r, g, b);

    // Create a color pair with the custom color as the foreground
    short pair_id = 1;
    init_pair(pair_id, color_id, COLOR_BLACK); // Use black as the background

    // Apply the color pair
    attron(COLOR_PAIR(pair_id));
    mvprintw(posx, posy, std::string(1, ch).c_str());
    attroff(COLOR_PAIR(pair_id));
    refresh();
}

void render(std::vector<std::string>& text)
{
    if (!has_colors() || !can_change_color()) {
        endwin();
        printf("Your terminal does not support changing colors.\n");
    }
}