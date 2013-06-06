/***************************************************************************
 *   Copyright (C) 2013 by Ralf Kaestner                                   *
 *   ralf.kaestner@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef BLINKM_FADETORANDOMCOLOR_H
#define BLINKM_FADETORANDOMCOLOR_H

/** \brief BlinkM fade to random color request
  */

#include "color/rgb.h"

#include "request.h"

namespace BlinkM {
  class FadeToRandomColor :
    public Request {
  public:
    /** Construct a BlinkM fade to random color request
      */
    FadeToRandomColor(const Color::Rgb& range = Color::Rgb());

    /** Access the request's range
      */
    Color::Rgb getRange() const;
    void setRange(const Color::Rgb& range);

    FadeToRandomColor* clone() const;

    void read(std::istream& stream);
  };
};

#endif
