#include "render.hpp"
#include <cstddef>
#include <ncurses.h>
#include <vector>

void init()
{
    initscr();
    cbreak();             // Line buffering disabled, pass all input to the program
    noecho();             // Don't echo typed characters
    keypad(stdscr, TRUE); // Enable function and arrow keys
    curs_set(0);          // Hide the cursor
    start_color();
    scrollok(stdscr, true);
}

enum COLOR {
    RED = 1, GREEN = 2, BLUE = 4
};

void draw_character(char ch, size_t posx, size_t posy, RGB color)
{
    short r = (color.r * 1000) / 255;
    short g = (color.g * 1000) / 255;
    short b = (color.b * 1000) / 255;

    COLOR c = COLOR::BLUE;
    if (r > g && r > b) {
        c = COLOR::RED;
    } else if (g > r && g > b) {
        c = COLOR::GREEN;
    }

    short color_id = 10;
    init_color(color_id, r, g, b);

    // Create a color pair with the custom color as the foreground
    short pair_id = 1;
    init_pair(pair_id, c, COLOR_BLACK); // Use black as the background

    // Apply the color pair
    attron(COLOR_PAIR(pair_id));
    mvaddch(posx, posy, ch);
    refresh();
}

void render(std::vector<std::string>& text, std::vector<std::vector<RGB>>& colors)
{
    if (!has_colors() || !can_change_color()) {
        endwin();
        printf("Your terminal does not support changing colors.\n");
    }

    for (size_t x = 0; x < text.size(); x++) {
        for (size_t y = 0; y < text.size(); y++) {
            draw_character(text[x][y], x, y, colors[x][y]);
        }    
    }
}