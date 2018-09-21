#ifndef __ESC__
#define __ESC__

#define ESC "\033"
#define home() printf(ESC "[H")
#define gotoxy(x,y) printf(ESC "[%d;%dH", x, y)
#define set_display_atrib(color) printf(ESC "[%dm", color)
#define clrscr() printf(ESC "[2J")

//Format text
#define RESET 0
#define BRIGHT 1
#define DIM 2
#define UNDERSCORE 3
#define BLINK 4
#define REVERSE 5
#define HIDDEN 6

//Foreground Colours (text)

#define F_BLACK 30
#define F_RED 31
#define F_GREEN 32
#define F_YELLOW 33
#define F_BLUE 34
#define F_MAGENTA 35
#define F_CYAN 36
#define F_WHITE 37

//Background Colours
#define B_BLACK 40
#define B_RED 41
#define B_GREEN 42
#define B_YELLOW 43
#define B_BLUE 44
#define B_MAGENTA 45
#define B_CYAN 46
#define B_WHITE 47

#endif /*__ESC__*/
