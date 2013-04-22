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

BlinkM::I2c::Request::Request(unsigned char deviceAddress, size_t
    outputDataSize, size_t inputDataSize) :
  deviceAddress(deviceAddress),
  outputData(outputDataSize),
  inputData(inputDataSize) {
}

BlinkM::I2c::Request::Request(const Request& src) :
  deviceAddress(src.deviceAddress),
  outputData(src.outputData),
  inputData(src.inputData) {
}

BlinkM::I2c::Request::~Request() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

void BlinkM::I2c::Request::setDeviceAddress(unsigned char deviceAddress) {
  this->deviceAddress = deviceAddress;
}

unsigned char BlinkM::I2c::Request::getDeviceAddress() const {
  return deviceAddress;
}

void BlinkM::I2c::Request::setOutputData(const std::vector<unsigned char>&
    outputData) {
  this->outputData = outputData;
}

const std::vector<unsigned char>& BlinkM::I2c::Request::getOutputData() const {
  return outputData;
}

const std::vector<unsigned char>& BlinkM::I2c::Request::getInputData() const {
  return inputData;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::I2c::Request& BlinkM::I2c::Request::operator=(const Request& src) {
  deviceAddress = src.deviceAddress;

  outputData = src.outputData;
  inputData = src.inputData;

  return *this;
}
