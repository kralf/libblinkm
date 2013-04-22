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

#ifndef BLINKM_COLOR_RGB_H
#define BLINKM_COLOR_RGB_H

/** \file rgb.h
  * \brief BlinkM RGB color
  */

#include <iostream>

#include "base/exception.h"

namespace BlinkM {
  namespace Color {
    class Hsv;

    class Rgb {
    friend class Hsv;
    public:
      /** Types and non-static subclasses
        */
      class RangeError :
        public Exception {
      public:
        /** Construct an RGB color range error
          */
        RangeError();
      };

      /** Construct a BlinkM RGB color object
        */
      Rgb(unsigned char red = 0, unsigned char green = 0,
        unsigned char blue = 0);
      Rgb(double red, double green, double blue);
      Rgb(const Hsv& hsv);
      Rgb(const Rgb& src);
      /** Destroy a BlinkM RGB color object
        */
      virtual ~Rgb();

      /** Access the color channels
        */
      void setChannels(unsigned char red, unsigned char green,
        unsigned char blue);
      void setChannels(double red, double green, double blue);
      /** Access the red channel
        */
      void setRed(unsigned char red);
      void setRed(double red);
      unsigned char getRed() const;
      /** Access the green channel
        */
      void setGreen(unsigned char green);
      void setGreen(double green);
      unsigned char getGreen() const;
      /** Access the blue channel
        */
      void setBlue(unsigned char blue);
      void setBlue(double blue);
      unsigned char getBlue() const;

      /** BlinkM RGB color assignments
        */
      Rgb& operator=(const Hsv& hsv);
      Rgb& operator=(const Rgb& src);

      /** BlinkM RGB color operations
        */
      Rgb interpolate(const Rgb& to, double value) const;

      /** Read the RGB color from the given stream
        */
      void read(std::istream& stream);
      /** Write the RGB color to the given stream
        */
      void write(std::ostream& stream) const;
    protected:
      unsigned char red;
      unsigned char green;
      unsigned char blue;
    };
  };
};

std::istream& operator>>(std::istream& stream,
  BlinkM::Color::Rgb& rgb);
std::ostream& operator<<(std::ostream& stream,
  const BlinkM::Color::Rgb& rgb);

#endif
