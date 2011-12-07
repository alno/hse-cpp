#include <gtkmm/window.h>
#include <gtkmm/main.h>
#include <gtkmm/drawingarea.h>
#include <iostream>
#include <cmath>

class FunArea : public Gtk::DrawingArea {
	int x_offset;
	int y_offset;

	int last_mouse_x;
	int last_mouse_y;

public:
	int funindex;

	FunArea() : x_offset(0), y_offset(0), funindex(0) {
		add_events(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::KEY_PRESS_MASK);
	}

	double f(double v) {
		switch(funindex) {
		case 0:
			return sin(v) * sqrt(abs(v));
		case 1:
			return cos(v);
		case 2:
			return v*v - 2*v - cos(v);
		}
		return 0;
	}

	virtual bool on_expose_event(GdkEventExpose * e) {
		Cairo::RefPtr<Cairo::Context> cr = get_window()->create_cairo_context();
		Gtk::Allocation al = get_allocation();

		cr->save();
		cr->translate(0, al.get_height() / 2);
		cr->scale(1, -1);

		int x_min = 0;
		int x_max = al.get_width();
		double scale = 50;

		cr->move_to(x_min, f((x_min - x_offset) / scale) * scale - y_offset);
		for (int x = x_min; x < x_max; x += 5)
			cr->line_to(x, f((x - x_offset) / scale ) * scale - y_offset);

		cr->set_line_width(3);
		cr->stroke();

		cr->set_source_rgb(0, 0, 1);
		cr->move_to(x_min, -y_offset);
		cr->line_to(x_max, -y_offset);
		cr->stroke();

		cr->restore();

		return true;
	}

	virtual bool on_motion_notify_event(GdkEventMotion * e) {
		if (e->state & Gdk::BUTTON1_MASK) {
			x_offset += e->x - last_mouse_x;
			y_offset += e->y - last_mouse_y;

			queue_draw();
		}

		last_mouse_x = e->x;
		last_mouse_y = e->y;

		return true;
	}

};


bool on_key_press_event(GdkEventKey * e, FunArea * a) {
	std::cout << e->keyval << std::endl;
	if ( e->keyval >= '0' && e->keyval <= '9') {
		a->funindex = e->keyval - '0';
		a->queue_draw();
	}
	return true;
}

int main(int argc, char ** argv) {
	Gtk::Main kit(argc, argv);

	Gtk::Window win;
	FunArea area;

	win.signal_key_press_event().connect(sigc::bind(sigc::ptr_fun(on_key_press_event), &area));
	win.add(area);
	win.show_all_children();

	kit.run(win);

	return 0;
}
