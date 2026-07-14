#include <myos>
#include <unistd.h>
#include <sched.h>
#include <stdio.h>
int main() {
	Ginfo screen;
	get_ginfo(&screen);
	Window* window = new Window({0,0,screen.width, screen.height},WINDOW_NOHEADER | WINDOW_NOBORDER,WINDOW_EX_GUI);
	for (int y = 0; y < screen.height; y++) {
		for (int x = 0; x < screen.width; x++) {
			((uint32_t*)window->gbuf)[y * window->rect.width + x] = PIXEL_TRANSPARENT;
		}
	}
	window->draw_frame(window->rect);
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			((uint32_t*)window->gbuf)[y * window->rect.width + x] = 0x00FF00FF;
		}
	}
	window->draw_frame({ 0,0,100,100 });
	window->rezorder();
	while (true) {
		wait_for_msg();
		msg_t msg;
		uint64_t result = receive_msg(&msg);
		if (result == 0) {
			printf("mygui got msg type=%x\n", msg.type);
			if (msg.type == MSG_MOUSE_LCLICK) {
				if (fork() == 0) {
					execv("@/myterminal.o", nullptr);
				}
			}
		}
	}
}