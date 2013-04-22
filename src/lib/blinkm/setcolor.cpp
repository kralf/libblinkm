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

#include "setcolor.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::SetColor::SetColor(const Color::Rgb& color) :
  Request('n', 3, 0) {
  setColor(color);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

BlinkM::Color::Rgb BlinkM::SetColor::getColor() const {
  return Color::Rgb(outputData[1], outputData[2], outputData[3]);
}

void BlinkM::SetColor::setColor(const Color::Rgb& color) {
  outputData[1] = color.getRed();
  outputData[2] = color.getGreen();
  outputData[3] = color.getBlue();
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::SetColor* BlinkM::SetColor::clone() const {
  return new SetColor(*this);
}

void BlinkM::SetColor::read(std::istream& stream) {
  Color::Rgb color;

  stream >> color;
  setColor(color);
}
