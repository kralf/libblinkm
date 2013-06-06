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

#include <cmath>

#include "base/serializable.h"

#include "color/hsv.h"

#include "rgb.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::Color::Rgb::RangeError::RangeError() :
  Exception("RGB channel exceeds range limits") {
}

BlinkM::Color::Rgb::Rgb(unsigned char red, unsigned char green,
    unsigned char blue) :
  red(red),
  green(green),
  blue(blue) {
}

BlinkM::Color::Rgb::Rgb(double red, double green, double blue) :
  red(0),
  green(0),
  blue(0) {
  setChannels(red, green, blue);
}

BlinkM::Color::Rgb::Rgb(const Hsv& hsv) :
  red(0),
  green(0),
  blue(0) {
  operator=(hsv);
}

BlinkM::Color::Rgb::Rgb(const Rgb& src) :
  red(src.red),
  green(src.green),
  blue(src.blue) {
}

BlinkM::Color::Rgb::~Rgb() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

void BlinkM::Color::Rgb::setChannels(unsigned char red, unsigned char green,
    unsigned char blue) {
  this->red = red;
  this->green = green;
  this->blue = blue;
}

void BlinkM::Color::Rgb::setChannels(double red, double green, double blue) {
  setRed(red);
  setGreen(green);
  setBlue(blue);
}

void BlinkM::Color::Rgb::setRed(unsigned char red) {
  this->red = red;
}

void BlinkM::Color::Rgb::setRed(double red) {
  if ((red >= 0.0) && (red <= 1.0))
    this->red = round(red*255.0);
  else
    throw RangeError();
}

unsigned char BlinkM::Color::Rgb::getRed() const {
  return red;
}

void BlinkM::Color::Rgb::setGreen(unsigned char green) {
  this->green = green;
}

void BlinkM::Color::Rgb::setGreen(double green) {
  if ((green >= 0.0) && (green <= 1.0))
    this->green = round(green*255.0);
  else
    throw RangeError();
}

unsigned char BlinkM::Color::Rgb::getGreen() const {
  return green;
}

void BlinkM::Color::Rgb::setBlue(unsigned char blue) {
  this->blue = blue;
}

void BlinkM::Color::Rgb::setBlue(double blue) {
  if ((blue >= 0.0) && (blue <= 1.0))
    this->blue = round(blue*255.0);
  else
    throw RangeError();
}

unsigned char BlinkM::Color::Rgb::getBlue() const {
  return blue;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::Color::Rgb& BlinkM::Color::Rgb::operator=(const Hsv& hsv) {
  if (hsv.value > 0) {
    double hue = hsv.hue/255.0*2.0*M_PI-M_PI;
    double sat = hsv.saturation/255.0;
    double val = hsv.value/255.0;

    hue /= 60.0*M_PI/180.0;
    unsigned char i = floor(hue);

    double f = hue-i;
    double p = val*(1.0-sat);
    double q = val*(1.0-sat*f);
    double t = val*(1.0-sat*(1.0-f));

    switch (i) {
      case 0:
        setChannels(val, t, p);
        break;
      case 1:
        setChannels(q, val, p);
        break;
      case 2:
        setChannels(p, val, t);
        break;
      case 3:
        setChannels(p, q, val);
        break;
      case 4:
        setChannels(t, p, val);
        break;
      default:
        setChannels(val, p, q);
        break;
    }
  }
  else {
    red = hsv.value;
    green = hsv.value;
    blue = hsv.value;
  }
}

BlinkM::Color::Rgb& BlinkM::Color::Rgb::operator=(const Rgb& src) {
  red = src.red;
  green = src.green;
  blue = src.blue;

  return *this;
}

BlinkM::Color::Rgb BlinkM::Color::Rgb::interpolate(const Rgb& to, double value)
    const {
  double red = this->red/255.0;
  double green = this->green/255.0;
  double blue = this->blue/255.0;

  red += (to.red/255.0-red)*value;
  green += (to.green/255.0-green)*value;
  blue += (to.blue/255.0-blue)*value;

  return Rgb(red, green, blue);
}

void BlinkM::Color::Rgb::read(std::istream& stream) {
  Serializable<unsigned char> red, green, blue;

  stream >> red >> green >> blue;

  this->red = red;
  this->green = green;
  this->blue = blue;
}

void BlinkM::Color::Rgb::write(std::ostream& stream) const {
  stream << Serializable<unsigned char>(red) << " " <<
    Serializable<unsigned char>(green) << " " <<
    Serializable<unsigned char>(blue);
}

std::istream& operator>>(std::istream& stream, BlinkM::Color::Rgb& rgb) {
  rgb.read(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const BlinkM::Color::Rgb&
    rgb) {
  rgb.write(stream);
  return stream;
}
