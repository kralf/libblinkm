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

#include <cstdarg>
#include <cstdio>

#include "exception.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::Exception::Exception() {
}

BlinkM::Exception::Exception(const std::string& format, ...) {
  char description[1024];
  va_list arguments;

  va_start(arguments, format);
  vsprintf(description, format.c_str(), arguments);
  va_end(arguments);

  this->description = description;
}

BlinkM::Exception::Exception(const Exception& src) :
  description(src.description) {
}

BlinkM::Exception::~Exception() throw() {
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::Exception& BlinkM::Exception::operator=(const Exception& src) {
  description = src.description;
  return *this;
}

const char* BlinkM::Exception::what() const throw() {
  if (!description.empty())
    return description.c_str();
  else
    return "Unknown error";
}
