//
// "$Id: HoldBrowser.h 8022 2010-12-12 23:21:03Z AlbrechtS $"
//
// Hold browser header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

/* \file
 fltk3::HoldBrowser widget . */

#ifndef Fltk3_Hold_Browser_H
#define Fltk3_Hold_Browser_H

#include "Browser.h"


namespace fltk3 {
  
  /**
   The fltk3::HoldBrowser is a subclass of fltk3::Browser
   which lets the user select a single item, or no items by clicking on
   the empty space.  As long as the mouse button is held down the item
   pointed to by it is highlighted, and this highlighting remains on when
   the mouse button is released. Normally the callback is done when the
   user releases the mouse, but you can change this with when().
   <P>See fltk3::Browser for methods to add and remove lines from the browser.
   */
  class FLTK3_EXPORT HoldBrowser : public fltk3::Browser {
  public:
    /**
     Creates a new fltk3::HoldBrowser widget using the given
     position, size, and label string. The default boxtype is fltk3::DOWN_BOX.
     The constructor specializes fltk3::Browser() by setting the type to fltk3::HOLD_BROWSER.
     The destructor destroys the widget and frees all memory that has been allocated.
     */
#if defined(FL_DLL)	// implementation in src/Fl_Browser.cxx
    HoldBrowser(int X,int Y,int W,int H,const char *L=0);
#else
    HoldBrowser(int X,int Y,int W,int H,const char *l=0)
    : fltk3::Browser(X,Y,W,H,l) {type(fltk3::HOLD_BROWSER);}
#endif
  };
  
}

#endif

//
// End of "$Id: HoldBrowser.h 8022 2010-12-12 23:21:03Z AlbrechtS $".
//
