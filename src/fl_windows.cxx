//
// "$Id: fl_windows.cxx,v 1.8 1999/11/14 04:36:58 carl Exp $"
//
// Theme plugin file for FLTK
//
// Copyright 1999 Bill Spitzak and others.
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

// Windows-98 style

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Style.H>
#include <stdio.h>
#include <string.h>

#ifdef WIN32
#include <windows.h>
#include <winuser.h>
#endif

// a boxtype drawing function in fl_boxtype.cxx
extern void fl_frame(Fl_Boxtype b, int x, int y, int w, int h,
                     Fl_Color c, Fl_Flags f);

// a boxtype drawing function in fl_boxtype.cxx
extern void fl_flatx(Fl_Boxtype b, int x, int y, int w, int h,
                     Fl_Color c, Fl_Flags f);

// some new boxtypes (look familiar?)
static const Fl_Boxtype_ thick_motif_down_box = {
};

static const Fl_Boxtype_ win98_menu_title_box = {
  fl_flatx, 0, FL_THIN_DOWN_BOX, FL_THIN_UP_BOX, 1,1,2,2,1
};

static const Fl_Boxtype_ win98_menu_window_box = {
#ifndef WIN32
  fl_frame, "2AAUUIIXX", FL_DOWN_BOX, &win98_menu_window_box, 2,2,4,4, 1
#else
  fl_frame, "2AARRMMUU", FL_DOWN_BOX, &win98_menu_window_box, 2,2,4,4, 1
#endif
};

#ifdef WIN32
static Fl_Color what_color(int wincol) {
  int R = wincol&0xff;
  int G = (wincol >> 8)&0xff;
  int B = (wincol >> 16)&0xff;
  Fl_Color col = fl_rgb(R, G, B);
  if (col) return col;
  return FL_BLACK;
}
#endif

extern int fl_extra_menu_spacing;

int fl_windows() {
  Fl_Style::revert(); // revert to FLTK default styles

// Matches KDE, but not Windows!
#ifndef WIN32
  fl_up_box.data = "2AAXXIIUU";
  fl_up_box.dx_ = 2;
  fl_up_box.dy_ = 2;
  fl_up_box.dw_ = 4;
  fl_up_box.dh_ = 4;
  fl_down_box.data = "2XXIIUUAA";
  fl_down_box.dx_ = 2;
  fl_down_box.dy_ = 2;
  fl_down_box.dw_ = 4;
  fl_down_box.dh_ = 4;
#endif

  Fl_Widget::default_style.set_selection_color(FL_GRAY);
  Fl_Widget::default_style.set_label_size(12);

  fl_extra_menu_spacing = 2;

  Fl_Style* s;
  if ((s = Fl_Style::find("menu window"))) {
    s->set_box(&win98_menu_window_box);
  }

  if ((s = Fl_Style::find("menu title"))) {
    s->set_box(&win98_menu_title_box);
    s->set_glyph_box(FL_NO_BOX);
  }

  // highlighting must be on both the menu bar and menu title!
  if ((s = Fl_Style::find("menu item"))) {
    s->set_glyph_box(FL_NO_BOX);
  }

  if ((s = Fl_Style::find("menu bar"))) {
    s->set_highlight_color(FL_GRAY); // needed for title highlighting
  }

  if ((s = Fl_Style::find("input"))) {
    s->set_box(FL_DOWN_BOX);
  }

  if ((s = Fl_Style::find("slider"))) {
    s->set_glyph_box(&win98_menu_window_box);
    s->set_box(FL_DOWN_BOX);
  }

  if ((s = Fl_Style::find("value slider"))) {
    s->set_glyph_box(&win98_menu_window_box);
    s->set_box(FL_DOWN_BOX);
  }

  if ((s = Fl_Style::find("scrollbar"))) {
    s->set_glyph_box(&win98_menu_window_box);
  }

  if ((s = Fl_Style::find("output"))) {
    s->set_box(FL_DOWN_BOX);
  }

  if ((s = Fl_Style::find("counter"))) {
    s->set_box(FL_DOWN_BOX);
  }

// use FLTK default Windows colors
#ifndef WIN32
  if ((s = Fl_Style::find("output"))) {
    s->set_color(FL_WHITE);
  }

  if ((s = Fl_Style::find("counter"))) {
    s->set_color(FL_WHITE);
  }

  if ((s = Fl_Style::find("scrollbar"))) {
    s->set_color(52);
  }

  if ((s = Fl_Style::find("highlight button"))) {
    s->set_highlight_color(FL_GRAY);
  }

  if ((s = Fl_Style::find("menu title"))) {
    s->set_selection_color(FL_GRAY);
    s->set_selection_text_color(FL_BLACK);
    s->set_highlight_color(FL_GRAY);
  }

// use the real Windows colors
#else
  Fl_Color background = what_color(GetSysColor(COLOR_BTNFACE));
  Fl_Color foreground = what_color(GetSysColor(COLOR_BTNTEXT));
  Fl_Color select_background = what_color(GetSysColor(COLOR_HIGHLIGHT));
  Fl_Color select_foreground = what_color(GetSysColor(COLOR_HIGHLIGHTTEXT));
  Fl_Color window_background = what_color(GetSysColor(COLOR_WINDOW));
  Fl_Color window_foreground = what_color(GetSysColor(COLOR_WINDOWTEXT));
  Fl_Color menuitem_background = what_color(GetSysColor(COLOR_MENU));
  Fl_Color menuitem_foreground = what_color(GetSysColor(COLOR_MENUTEXT));
  Fl_Color tooltip_background = what_color(GetSysColor(COLOR_INFOBK));
  Fl_Color tooltip_foreground = what_color(GetSysColor(COLOR_INFOTEXT));
// Windows doesn't seem to honor this one
// Fl_Color slider_background = what_color(GetSysColor(COLOR_SCROLLBAR));

  fl_background(background);
  Fl_Widget::default_style.set_off_color(background);

  Fl_Widget::default_style.set_label_color(foreground);
  Fl_Widget::default_style.set_highlight_label_color(foreground);
  Fl_Widget::default_style.set_selection_text_color(foreground);

  Fl_Widget::default_style.set_text_color(window_foreground);

  Fl_Style* style;
  if ((style = Fl_Style::find("input"))) {
    style->set_off_color(foreground); // cursor
    style->set_color(window_background);
    style->set_text_color(window_foreground);
    style->set_selection_color(select_background);
    style->set_selection_text_color(select_foreground);
  }

  if ((style = Fl_Style::find("output"))) {
    style->set_color(window_background);
    style->set_text_color(window_foreground);
    style->set_selection_color(select_background);
    style->set_selection_text_color(select_foreground);
  }

  if ((style = Fl_Style::find("counter"))) {
    style->set_color(window_background);
    style->set_text_color(window_foreground);
  }

  if ((style = Fl_Style::find("browser"))) {
    style->set_color(window_background);
    style->set_text_color(window_foreground);
    style->set_selection_color(select_background);
    style->set_selection_text_color(select_foreground);
  }

  if ((style = Fl_Style::find("check button"))) {
    style->set_selection_color(window_foreground);
    style->set_off_color(window_background);
  }

  if ((style = Fl_Style::find("scrollbar"))) {
//    style->set_color(fl_color_average(slider_background, window_background, .5));
    style->set_color(fl_color_average(background, window_background, .5));
  }

  if ((style = Fl_Style::find("menu item"))) {
    style->set_color(menuitem_background);
    style->set_label_color(menuitem_foreground);
    style->set_highlight_color(select_background);
    style->set_highlight_label_color(select_foreground);
  }

  if ((style = Fl_Style::find("menu title"))) {
    style->set_highlight_color(background);
    style->set_highlight_label_color(foreground);
    style->set_selection_color(background);
    style->set_selection_text_color(foreground);
  }

  if ((style = Fl_Style::find("tooltip"))) {
    style->set_color(tooltip_background);
    style->set_label_color(tooltip_foreground);
  }

/* CET - FIXME - Font stuff not yet implemented

   This needs either a working

      Fl_Font fl_font(const char* fontname)

   or

      int fl_list_fonts(Fl_Font* fontlist)

   Currently, the Windows code has neither.  :-(


  if (font) {
    if (*fontencoding) fl_encoding = fontencoding;
    Fl_Widget::default_style.set_label_font(font);
    Fl_Widget::default_style.set_text_font(font);
    Fl_Widget::default_style.set_label_size(fontsize);
    Fl_Widget::default_style.set_text_size(fontsize);
  }
*/
#endif

  static Fl_Boxtype_Definer win98_menu_title("win98 menu title", win98_menu_title_box);
  static Fl_Boxtype_Definer win98_menu_window("win98 menu window", win98_menu_window_box);

  Fl::redraw();

  return 0;
}

//
// End of "$Id: fl_windows.cxx,v 1.8 1999/11/14 04:36:58 carl Exp $".
//
