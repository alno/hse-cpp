#include <gtkmm/window.h>
#include <gtkmm/main.h>
#include <gtkmm/drawingarea.h>
#include <cmath>

class MyDrawingArea : public Gtk::DrawingArea {
protected:

	double f(double x) {
		return sin(x);
	}

	virtual bool on_expose_event(GdkEventExpose * ev) {
		Cairo::RefPtr<Cairo::Context> cr = get_window()->create_cairo_context();
		Gtk::Allocation allocation = get_allocation();

		double ch = allocation.get_height() / 2;
		double scale = 100;

		double x_max = allocation.get_width() / scale;
		double x_step = 10/scale;

		cr->save();
		cr->translate(0, ch);
		cr->scale(scale, -scale);

		cr->set_line_width(5 / scale);
		cr->move_to(0, f(0));
		for ( double x = 0; x <= x_max; x += x_step )
			cr->line_to(x, f(x));
		cr->stroke();

		cr->restore();

		return true;
	}
};

void main(int argc, char**argv) {
	Gtk::Main gtk(argc, argv);

	Gtk::Window win;
	MyDrawingArea area;

	win.add(area);
	win.show_all_children();

	gtk.run(win);
}
