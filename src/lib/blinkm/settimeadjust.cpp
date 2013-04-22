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

#include "base/serializable.h"

#include "settimeadjust.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::SetTimeAdjust::SetTimeAdjust(char adjustment) :
  Request('t', 1, 0) {
  outputData[1] = adjustment;
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

char BlinkM::SetTimeAdjust::getAdjustment() const {
  return outputData[1];
}

void BlinkM::SetTimeAdjust::setAdjustment(char adjustment) {
  outputData[1] = adjustment;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::SetTimeAdjust* BlinkM::SetTimeAdjust::clone() const {
  return new SetTimeAdjust(*this);
}

void BlinkM::SetTimeAdjust::read(std::istream& stream) {
  Serializable<int> adjustment;

  ArgumentRangeError::assert(adjustment.read(stream), -127, 127);
  setAdjustment(adjustment);
}
