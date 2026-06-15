#include <myos>

int main() {
	Ginfo screen;
	get_ginfo(&screen);
	Window* window = new Window({0,0,screen.width, screen.height},WINDOW_NOHEADER,WINDOW_EX_GUI);
}