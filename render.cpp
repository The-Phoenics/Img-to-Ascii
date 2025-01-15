#include "render.hpp"

void init()
{
    initscr();
    // cbreak();             // Line buffering disabled, pass all input to the program
    // noecho();             // Don't echo typed characters
    // keypad(stdscr, TRUE); // Enable function and arrow keys
    start_color(); 
}


void draw_character(char ch, RGB color)
{
    // Define custom RGB color (replace with your desired RGB values)
    short r = 500;          // Red (0-1000)
    short g = 300;          // Green (0-1000)
    short b = 700;          // Blue (0-1000)
    short color_id = 10;    // Custom color ID (must be >= 0 and < COLORS)

    // Initialize the color
    init_color(color_id, r, g, b);

    // Create a color pair with the custom color as the foreground
    short pair_id = 1;
    init_pair(pair_id, color_id, COLOR_BLACK); // Use black as the background

    // Apply the color pair
    attron(COLOR_PAIR(pair_id));
    mvprintw(5, 10, std::string(1, ch).c_str());
    attroff(COLOR_PAIR(pair_id));
    refresh();

}

void render(std::string& text)
{
    if (!has_colors() || !can_change_color()) {
        endwin();
        printf("Your terminal does not support changing colors.\n");
    }

    draw_character('a', RGB(200, 100, 206));

}

int main()
{
    init();

    // update
    update();

    // draw
    draw();

    endwin();
}
