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

#ifndef BLINKM_BITS_H
#define BLINKM_BITS_H

/** \brief BlinkM bits operations
  */

#include <iostream>

namespace BlinkM {
  template <typename T> class Bits {
  public:
    /** Construct a BlinkM bits object
      */
    Bits(const T& value = T());
    Bits(const Bits<T>& src);

    /** Destroy a BlinkM bits object
      */
    virtual ~Bits();

    /** BlinkM bits assignments
      */
    Bits<T>& operator=(const Bits<T>& src);
    Bits<T>& operator=(const T& value);

    /** BlinkM bits operations
      */
    Bits<T>& reverse();

    /** Read the bits from the given stream
      */
    void read(std::istream& stream);
    /** Write the bits to the given stream
      */
    void write(std::ostream& stream) const;

    /** BlinkM bits conversions
      */
    operator T&();
    operator const T&() const;
  protected:
    T value;
  };
};

template <typename T> std::istream& operator>>(std::istream& stream,
  BlinkM::Bits<T>& bits);
template <typename T> std::ostream& operator<<(std::ostream& stream,
  const BlinkM::Bits<T>& bits);

#include "base/bits.tpp"

#endif
