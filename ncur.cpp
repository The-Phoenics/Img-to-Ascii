#include <ncurses.h>


void init()
{
    initscr();
    cbreak();             // Line buffering disabled, pass all input to the program
    noecho();             // Don't echo typed characters
    keypad(stdscr, TRUE); // Enable function and arrow keys
    start_color(); 
}

void update()
{

}

void draw()
{
    if (!has_colors() || !can_change_color()) {
        endwin();
        printf("Your terminal does not support changing colors.\n");
    }

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
    mvprintw(5, 10, "Hello, colorful world!"); // Print a colored message
    attroff(COLOR_PAIR(pair_id));

    refresh();
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
