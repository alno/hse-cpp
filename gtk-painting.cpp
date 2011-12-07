#include <gtkmm/window.h>
#include <gtkmm/main.h>
#include <gtkmm/drawingarea.h>

class MyDrawingArea : public Gtk::DrawingArea {
protected:

	virtual bool on_expose_event(GdkEventExpose * ev) {
		Cairo::RefPtr<Cairo::Context> cr = get_window()->create_cairo_context();

		cr->save();

		cr->set_line_width(10);
		cr->set_source_rgb(1, 0, 0);
		cr->move_to(0, 0);
		cr->line_to(100, 100);
		cr->line_to(50, 200);
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
