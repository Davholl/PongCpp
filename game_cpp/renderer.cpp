#include "utilities.cpp"

void render_background() {
	unsigned int* pixel = (unsigned int*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = x * y;
		}
	}
}

void clear_screen(unsigned int color) {
	unsigned int* pixel = (unsigned int*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

void draw_rect_in_pixels(int x0, int y0, int x1, int y1, unsigned int color) {
	x0 = clamp(x0, 0, render_state.width);
	x1 = clamp(x1, 0, render_state.width);
	y0 = clamp(y0, 0, render_state.height);
	y1 = clamp(y1, 0, render_state.height);

	for (int y = y0; y < y1; y++) {
		unsigned int* pixel = (unsigned int*)render_state.memory + x0 + y*render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}


void draw_rect(float x, float y, float half_size_x, float half_size_y, unsigned int color) {
	x *= render_state.height * render_state.scale;
	y *= render_state.height * render_state.scale;

	half_size_x *= render_state.height * render_state.scale;
	half_size_y *= render_state.height * render_state.scale;
	
	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	//Change to Pixels
	int x0 = x - half_size_x;
	int y0 = y - half_size_y;
	int x1 = x + half_size_x;
	int y1 = y + half_size_y;
	draw_rect_in_pixels(x0, y0, x1, y1, color);
}