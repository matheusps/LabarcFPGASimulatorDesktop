// Labarc FPGA Simulator
// This program is based in part on the work of the FLTK project (http://www.fltk.org).
// This program is free software; you can
// redistribute it and/or modify it under the terms of either the GNU
// Lesser General Public License Version 3 or the Perl Artistic License
// Version 2.0.
// Icaro Dantas de Araujo Lima and Elmar Melcher at UFCG, 2018

#include <sstream>
#include <iomanip>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Toggle_Button.H>
#include <FL/Fl_Window.H>

#define XMARGIN 10
#define SWIS_OFFSET 64
#define LEDS_VERTICAL_OFFSET 230
#define DISPLAY_FONT ((Fl_Font)55)

class SWI : public Fl_Widget {
	int id;
	Fl_PNG_Image *swi_on, *swi_off;
public:
	bool state;
	
	virtual void draw();
	virtual int handle(int event);
	SWI(int x, int y, int id, Fl_PNG_Image *swi_on, Fl_PNG_Image *swi_off);
};

class SWIs : public Fl_Widget {
	SWI *swis[8];
public:
	static Fl_PNG_Image *swi_on, *swi_off;

	SWIs(int x, int y, int offset);
	virtual void draw();
};

class LEDs : public Fl_Widget {
	int x_origin, y_origin, offset;	
public:	
	static Fl_PNG_Image *led_on, *led_off;

	LEDs(int x_origin, int y_origin, int offset);
	virtual void draw();
};

// show SystemVerilog output signal in graphic interface
class display : public Fl_Widget {  // FLTK Widget
public:
  void draw();
  void lcd_labels(int start, int step);
  void register_labels(int start, int step);
  display(int x, int y);
private:
  int offset;
};

class SegmentsDisplay : public Fl_Widget {
	bool *previous;
	Fl_PNG_Image *point_on, *point_off, *vertical_on, *vertical_off, *horizontal_on, *horizontal_off;
	
public:
	static Fl_PNG_Image *base;

	virtual void draw();
	SegmentsDisplay(int x, int y);
};

class Board : public Fl_Widget {		
public:
	static Fl_PNG_Image *image;

	SWIs *swis;
	SegmentsDisplay *segments;

	virtual void draw();
	Board(int x, int y);
};

class FPGA : public Fl_Widget {	
public:
	static Fl_PNG_Image *image;

	display *disp;
	Board *board;
	LEDs *leds;

	virtual void draw();
	FPGA(int x, int y);
};

extern Fl_Window *window;
extern FPGA *fpga;

void init_gui(int, char**);
void delete_gui();
void callback(void*);

