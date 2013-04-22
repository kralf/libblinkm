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

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

template <typename T>
BlinkM::Bits<T>::Bits(const T& value) :
  value(value) {
}

template <typename T>
BlinkM::Bits<T>::Bits(const Bits<T>& src) :
  value(src.value) {
}

template <typename T>
BlinkM::Bits<T>::~Bits() {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

template <typename T>
BlinkM::Bits<T>& BlinkM::Bits<T>::operator=(const Bits<T>& src) {
  value = src.value;
  return *this;
}

template <typename T>
BlinkM::Bits<T>& BlinkM::Bits<T>::operator=(const T& value) {
  this->value = value;
  return *this;
}

template <typename T>
BlinkM::Bits<T>& BlinkM::Bits<T>::reverse() {
  T reversed = value;
  T shift = sizeof(T)*7;

  for (value >>= 1; value; value >>= 1) {
    reversed <<= 1;
    reversed |= value & 1;
    --shift;
  }
  reversed <<= shift;

  value = reversed;
  return *this;
}

template <typename T>
void BlinkM::Bits<T>::read(std::istream& stream) {
  T mask = T(1);
  value = T();

  for (size_t i = 0; i < sizeof(T)*8; ++i, mask <<= 1) {
    char bit;
    stream >> bit;

    if (bit != '0')
      value |= mask; 
  }
}

template <typename T>
void BlinkM::Bits<T>::write(std::ostream& stream) const {
  T mask = T(1);

  for (size_t i = 0; i < sizeof(T)*8; ++i, mask <<= 1)
    stream << (value & mask) ? '1' : '0';
}

template <typename T>
BlinkM::Bits<T>::operator T&() {
  return value;
}

template <typename T>
BlinkM::Bits<T>::operator const T&() const {
  return value;
}

template <typename T> std::istream& operator>>(std::istream& stream,
    BlinkM::Bits<T>& bits) {
  bits.read(stream);
  return stream;
}

template <typename T> std::ostream& operator<<(std::ostream& stream,
    const BlinkM::Bits<T>& bits) {
  bits.write(stream);
  return stream;
}
