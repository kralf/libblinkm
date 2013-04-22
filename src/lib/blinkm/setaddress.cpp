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

#include "setaddress.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::SetAddress::SetAddress(unsigned char address) :
  Request('A', 4, 0) {
  outputData[2] = 0xd0;
  outputData[3] = 0x0d;

  setAddress(address);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

unsigned char BlinkM::SetAddress::getAddress() const {
  return outputData[1];
}

void BlinkM::SetAddress::setAddress(unsigned char address) {
  ArgumentRangeError::assert((size_t)address, 0, 127);

  outputData[1] = address;
  outputData[4] = address;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::SetAddress* BlinkM::SetAddress::clone() const {
  return new SetAddress(*this);
}

void BlinkM::SetAddress::read(std::istream& stream) {
  Serializable<unsigned char> address;
  setAddress(address.read(stream));
}
