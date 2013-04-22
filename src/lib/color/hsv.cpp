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
#include <limits>

#include "base/bits.h"

#include "color/rgb.h"

#include "hsv.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::Color::Hsv::RangeError::RangeError() :
  Exception("HSV channel exceeds range limits") {
}

BlinkM::Color::Hsv::Hsv(unsigned char hue, unsigned char saturation,
    unsigned char value) :
  hue(hue),
  saturation(saturation),
  value(value) {
}

BlinkM::Color::Hsv::Hsv(double hue, double saturation, double value) :
  hue(0),
  saturation(0),
  value(0) {
  setChannels(hue, saturation, value);
}

BlinkM::Color::Hsv::Hsv(const Rgb& rgb) :
  hue(0),
  saturation(0),
  value(0) {
  operator=(rgb);
}

BlinkM::Color::Hsv::Hsv(const Hsv& src) :
  hue(src.hue),
  saturation(src.saturation),
  value(src.value) {
}

BlinkM::Color::Hsv::~Hsv() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

void BlinkM::Color::Hsv::setChannels(unsigned char hue, unsigned char
    saturation, unsigned char value) {
  this->hue = hue;
  this->saturation = saturation;
  this->value = value;
}

void BlinkM::Color::Hsv::setChannels(double hue, double saturation, double
    value) {
  setHue(hue);
  setSaturation(saturation);
  setValue(value);
}

void BlinkM::Color::Hsv::setHue(unsigned char hue) {
  this->hue = hue;
}

void BlinkM::Color::Hsv::setHue(double hue) {
  if (hue >= 0.0)
    while (hue > M_PI) hue -= 2.0*M_PI;
  else
    while (hue < -M_PI) hue += 2.0*M_PI;

  this->hue = round((M_PI+hue)/(2.0*M_PI)*255.0);
}

unsigned char BlinkM::Color::Hsv::getHue() const {
  return hue;
}

void BlinkM::Color::Hsv::setSaturation(unsigned char saturation) {
  this->saturation = saturation;
}

void BlinkM::Color::Hsv::setSaturation(double saturation) {
  if ((saturation >= 0.0) && (saturation <= 1.0))
    this->saturation = round(saturation*255.0);
  else
    throw RangeError();
}

unsigned char BlinkM::Color::Hsv::getSaturation() const {
  return saturation;
}

void BlinkM::Color::Hsv::setValue(unsigned char value) {
  this->value = value;
}

void BlinkM::Color::Hsv::setValue(double value) {
  if ((value >= 0.0) && (value <= 1.0))
    this->value = round(value*255.0);
  else
    throw RangeError();
}

unsigned char BlinkM::Color::Hsv::getValue() const {
  return value;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::Color::Hsv& BlinkM::Color::Hsv::operator=(const Rgb& rgb) {
  double red = rgb.red/255.0;
  double green = rgb.green/255.0;
  double blue = rgb.blue/255.0;

  double min = fmin(red, fmin(green, blue));
  double max = fmax(red, fmax(green, blue));
  double delta = max-min;

  if (max != 0.0) {
    setSaturation(delta/max);

    double hue = 0.0;
    if(red == max)
      hue = (green-blue)/delta;
    else if(green == max)
      hue = 2.0+(blue-red)/delta;
    else
      hue = 4.0+(red-green)/delta;

    hue *= 60.0*M_PI/180.0;
    if (hue < 0.0)
      hue += 2.0*M_PI;

    setHue(hue);
  }
  else {
    setHue(-M_PI);
    setSaturation(0.0);
  }
  setValue(max);
}

BlinkM::Color::Hsv& BlinkM::Color::Hsv::operator=(size_t id) {
  Bits<size_t> bits(id);

  setHue((double)bits.reverse()/
    (double)std::numeric_limits<size_t>::max()*2.0*M_PI);
}

BlinkM::Color::Hsv& BlinkM::Color::Hsv::operator=(const Hsv& src) {
  hue = src.hue;
  saturation = src.saturation;
  value = src.value;

  return *this;
}

BlinkM::Color::Hsv BlinkM::Color::Hsv::interpolate(const Hsv& to, double value)
    const {
  double hue = this->hue/255.0;
  double sat = this->saturation/255.0;
  double val = this->value/255.0;

  hue += (to.hue/255.0-hue)*value;
  sat += (to.saturation/255.0-sat)*value;
  val += (to.value/255.0-val)*value;

  return Hsv(hue, sat, val);
}

void BlinkM::Color::Hsv::read(std::istream& stream) {
  stream >> hue >> saturation >> value;
}

void BlinkM::Color::Hsv::write(std::ostream& stream) const {
  stream << hue << " " << saturation << " " << value;
}

std::istream& operator>>(std::istream& stream, BlinkM::Color::Hsv& hsv) {
  hsv.read(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const BlinkM::Color::Hsv&
    hsv) {
  hsv.write(stream);
  return stream;
}
