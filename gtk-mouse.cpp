#include <gtkmm/window.h>
#include <gtkmm/main.h>
#include <iostream>

bool mouse_moved(GdkEventMotion * e) {
	std::cout << e->x << " " << e->y << std::endl;
	return true;
}

bool mouse_button(GdkEventButton * e, const char * name) {
	std::cout << name << " " << e->button << std::endl;
	return true;
}

int main(int argc, char ** argv) {
	Gtk::Main kit(argc, argv);

	Gtk::Window win;

	win.add_events(Gdk::POINTER_MOTION_MASK);
	win.signal_motion_notify_event().connect(sigc::ptr_fun(mouse_moved));
	win.signal_button_press_event().connect(sigc::bind(sigc::ptr_fun(mouse_button), "pressed"));
	win.signal_button_release_event().connect(sigc::bind(sigc::ptr_fun(mouse_button), "released"));

	kit.run(win);

	return 0;
}
