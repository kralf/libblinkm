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

#ifndef BLINKM_COLOR_HSV_H
#define BLINKM_COLOR_HSV_H

/** \brief BlinkM HSV color
  */

#include <iostream>

#include "base/exception.h"

namespace BlinkM {
  namespace Color {
    class Rgb;

    class Hsv {
    friend class Rgb;
    public:
      /** Types and non-static subclasses
        */
      class RangeError :
        public Exception {
      public:
        /** Construct an HSV color range error
          */
        RangeError();
      };

      /** Construct a BlinkM HSV color object
        */
      Hsv(unsigned char hue = 0, unsigned char saturation = 0,
        unsigned char value = 0);
      Hsv(double hue, double saturation, double value);
      Hsv(const Rgb& rgb);
      Hsv(const Hsv& src);
      /** Destroy a BlinkM HSV color object
        */
      virtual ~Hsv();

      /** Access the color channels
        */
      void setChannels(unsigned char hue, unsigned char saturation,
        unsigned char value);
      void setChannels(double hue, double saturation, double value);
      /** Access the hue channel
        */
      void setHue(unsigned char hue);
      void setHue(double hue);
      unsigned char getHue() const;
      /** Access the saturation channel
        */
      void setSaturation(unsigned char saturation);
      void setSaturation(double saturation);
      unsigned char getSaturation() const;
      /** Access the value channel
        */
      void setValue(unsigned char value);
      void setValue(double value);
      unsigned char getValue() const;

      /** BlinkM HSV color assignments
        */
      Hsv& operator=(size_t id);
      Hsv& operator=(const Rgb& rgb);
      Hsv& operator=(const Hsv& src);

      /** BlinkM HSV color operations
        */
      Hsv interpolate(const Hsv& to, double value) const;

      /** Read the HSV color from the given stream
        */
      void read(std::istream& stream);
      /** Write the HSV color to the given stream
        */
      void write(std::ostream& stream) const;
    protected:
      unsigned char hue;
      unsigned char saturation;
      unsigned char value;
    };
  };
};

std::istream& operator>>(std::istream& stream,
  BlinkM::Color::Hsv& hsv);
std::ostream& operator<<(std::ostream& stream,
  const BlinkM::Color::Hsv& hsv);

#endif
