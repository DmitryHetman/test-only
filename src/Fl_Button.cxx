//
// "$Id: Fl_Button.cxx,v 1.46 2002/01/29 08:05:56 spitzak Exp $"
//
// Button widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#include <fltk/Fl.h>
#include <fltk/Fl_Button.h>
#include <fltk/Fl_Group.h>
#include <config.h>

int Fl_Button::set() {
  clear_changed();
  if (!value()) {set_value(); redraw(); return 1;}
  return 0;
}

int Fl_Button::clear() {
  clear_changed();
  if (value()) {clear_value(); redraw(); return 1;}
  return 0;
}

int Fl_Button::value(int v) {
  v ? set() : clear();
  return value();
}

void Fl_Button::setonly() { // set this radio button on, turn others off
  set();
  for (int i = parent()->children(); i--;) {
    Fl_Widget* o = parent()->child(i);
    if (o != this && o->type() == RADIO)
      ((Fl_Button*)o)->clear();
  }
}

int Fl_Button::handle(int event) {
  static int oldval;
  int newval;
  switch (event) {
  case FL_ENTER:
  case FL_LEAVE:
    if (highlight_color() && takesevents()) redraw(FL_DAMAGE_HIGHLIGHT);
  case FL_MOVE:
    return 1;
  case FL_PUSH:
#if CLICK_MOVES_FOCUS
    take_focus();
#endif
    oldval = value();
  case FL_DRAG:
    if (Fl::event_inside(0,0,w(),h())) {
      if (type() == RADIO) newval = 1;
      else newval = !oldval;
    } else
      newval = oldval;
    if (value(newval) && when()&FL_WHEN_CHANGED) do_callback();
    return 1;
  case FL_RELEASE:
    if (!Fl::pushed()) {
      if (value() == oldval) return 1;
      if (type() == RADIO)
	setonly();
      else if (type()) // TOGGLE
	  ; // leave it as set
      else {
	value(oldval);
	if (when() & FL_WHEN_CHANGED) do_callback();
      }
      if (when() & FL_WHEN_RELEASE) do_callback(); else set_changed();
    }
    return 1;
  case FL_FOCUS:
  case FL_UNFOCUS:
    redraw(FL_DAMAGE_HIGHLIGHT);
    // grab initial focus if we are an Fl_Return_Button:
    return shortcut()==FL_Enter ? 2 : 1;
  case FL_KEY:
    if (Fl::event_key() == FL_Enter || Fl::event_key() == ' ') goto EXECUTE;
    return 0;
  case FL_SHORTCUT:
    if (!test_shortcut()) return 0;
  EXECUTE:
    if (type() == RADIO && !value()) {
      setonly();
      if (when() & FL_WHEN_CHANGED) do_callback();
    } else if (type()) { // TOGGLE
      value(!value());
      if (when() & FL_WHEN_CHANGED) do_callback();
    }
    if (when() & FL_WHEN_RELEASE) do_callback(); else set_changed();
    return 1;
  default:
    return 0;
  }
}

////////////////////////////////////////////////////////////////

#include <fltk/fl_draw.h>

extern Fl_Widget* fl_did_clipping;

extern void fl_dotted_box(int,int,int,int);

// Draw button-like widgets with an optional glyph. The glyph is given
// a size (negative to put it on the right)
void Fl_Button::draw(int glyph, int glyph_width) const
{
  // Figure out the colors to use. The flags are used by the label and
  // glyph functions to figure out their colors:
  Fl_Flags flags;
  Fl_Color color;
  if (!active_r()) {
    flags = FL_INACTIVE;
    color = this->color();
  } else if (belowmouse()) {
    flags = FL_HIGHLIGHT;
    color = highlight_color();
    if (!color) color = this->color();
  } else {
    flags = 0;
    color = this->color();
  }
  Fl_Flags glyph_flags = flags;
  if (glyph_width) {
    if (pushed()) flags |= FL_VALUE;
    if (value()) glyph_flags |= FL_VALUE;
  } else if (value()) {
    flags |= FL_VALUE;
    // Use the pushed-in color if the user has explicitly set it
    // on this widget:
    if (style()->selection_color) {
      color = style()->selection_color;
      flags |= FL_SELECTED; // this makes label use selected_text_color()
    }
  }

  Fl_Boxtype box = this->box();

  // FL_NO_BOX does not need to draw anything other than the glyph
  // unless this is a regular draw or the focus is going away. This
  // avoids blinking and avoids double-drawing the label (which makes
  // it bold if antialiasing is on):
  if (box == FL_NO_BOX && !(damage()&FL_DAMAGE_EXPOSE) &&
      !(damage()&FL_DAMAGE_HIGHLIGHT && !focused())) {
    if (glyph_width < 0) {
      int g = -glyph_width;
      draw_glyph(glyph, w()-g-3, (h()-g)/2, g, g, glyph_flags);
    } else if (glyph_width > 0) {
      int g = glyph_width;
      draw_glyph(glyph, 3, (h()-g)/2, g, g, glyph_flags);
    }
    if (focused()) {
      fl_color(text_color());
      fl_dotted_box(1, 1, w()-2, h()-2);
    }
    return;
  }

  // Erase the area around non-square boxes, or the entire background
  // for a no-box widget:
  if (box==FL_NO_BOX || damage()&FL_DAMAGE_EXPOSE && !box->fills_rectangle()) {
    fl_push_clip(0, 0, this->w(), this->h());
    parent()->draw_group_box();
    fl_pop_clip();
  }

  // Draw the box:
  box->draw(0,0, this->w(), this->h(), color, flags);
  int x,y,w,h;
  x = y = 0; w = this->w(); h = this->h(); box->inset(x,y,w,h);

  if (glyph_width < 0) {
    int g = -glyph_width;
    draw_glyph(glyph, x+w-g-3, y+(h-g)/2, g, g, glyph_flags);
    draw_inside_label(x, y, w-g-3, h, flags);
  } else if (glyph_width > 0) {
    int g = glyph_width;
    draw_glyph(glyph, x+3, y+(h-g)/2, g, g, glyph_flags);
    draw_inside_label(x+g+3, y, w-g-3, h, flags);
  } else {
    draw_inside_label(x, y, w, h, flags);
  }

  if (focused()) {
    fl_color(text_color());
    fl_dotted_box(x+1, y+1, w-2, h-2);
  }
}

void Fl_Button::draw() {
  if (type() == HIDDEN) {
    fl_did_clipping = this;
    return;
  }
  draw(0,0);
}

////////////////////////////////////////////////////////////////

static void revert(Fl_Style* s) {
  s->color = FL_GRAY;
  s->box = FL_UP_BOX;
}

static Fl_Named_Style style("Button", revert, &Fl_Button::default_style);
Fl_Named_Style* Fl_Button::default_style = &::style;

Fl_Button::Fl_Button(int x,int y,int w,int h, const char *l) : Fl_Widget(x,y,w,h,l) {
  style(default_style);
}

//
// End of "$Id: Fl_Button.cxx,v 1.46 2002/01/29 08:05:56 spitzak Exp $".
//
