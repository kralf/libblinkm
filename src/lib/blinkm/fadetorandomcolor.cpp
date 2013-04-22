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

#include "fadetorandomcolor.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::FadeToRandomColor::FadeToRandomColor(const Color::Rgb& range) :
  Request('C', 3, 0) {
  setRange(range);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

BlinkM::Color::Rgb BlinkM::FadeToRandomColor::getRange() const {
  return Color::Rgb(outputData[1], outputData[2], outputData[3]);
}

void BlinkM::FadeToRandomColor::setRange(const Color::Rgb& range) {
  outputData[1] = range.getRed();
  outputData[2] = range.getGreen();
  outputData[3] = range.getBlue();
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::FadeToRandomColor* BlinkM::FadeToRandomColor::clone() const {
  return new FadeToRandomColor(*this);
}

void BlinkM::FadeToRandomColor::read(std::istream& stream) {
  Color::Rgb range;

  stream >> range;
  setRange(range);
}
