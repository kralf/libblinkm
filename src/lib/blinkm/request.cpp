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

#include "request.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::Request::Request(unsigned char command, size_t numArguments,
    size_t numReturnValues) :
  BlinkM::I2c::Request(0, numArguments+1, numReturnValues) {
  outputData[0] = command;
}

BlinkM::Request::Request(const Request& src) :
  BlinkM::I2c::Request(src) {
}

BlinkM::Request::~Request() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

void BlinkM::Request::setCommand(unsigned char command) {
  outputData[0] = command;
}

unsigned char BlinkM::Request::getCommand() const {
  return outputData[0];
}

size_t BlinkM::Request::getNumArguments() const {
  if (!outputData.empty())
    return outputData.size()-1;
  else
    return 0;
}

void BlinkM::Request::setArguments(const std::vector<unsigned char>&
    arguments) {
  outputData.resize(arguments.size()+1);
  std::copy(arguments.begin(), arguments.end(), outputData.begin()+1);
}

std::vector<unsigned char> BlinkM::Request::getArguments() const {
  std::vector<unsigned char> arguments(outputData.size()-1);
  std::copy(outputData.begin()+1, outputData.end(), arguments.begin());

  return arguments;
}

size_t BlinkM::Request::getNumReturnValues() const {
  return inputData.size();
}

const std::vector<unsigned char>& BlinkM::Request::getReturnValues() const {
  return inputData;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::Request& BlinkM::Request::operator=(const Request& src) {
  BlinkM::I2c::Request::operator=(src);
  return *this;
}

BlinkM::Request* BlinkM::Request::clone() const {
  return new Request(*this);
}

void BlinkM::Request::read(std::istream& stream) {
}

void BlinkM::Request::write(std::ostream& stream) const {
}

std::istream& operator>>(std::istream& stream, BlinkM::Request& request) {
  request.read(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const BlinkM::Request& request) {
  request.write(stream);
  return stream;
}
