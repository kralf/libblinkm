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

#include "base/singleton.h"
#include "base/serializable.h"

#include "device.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::Device::FirmwareVersion::FirmwareVersion(unsigned char major,
    unsigned char minor) :
  major(major),
  minor(minor) {
}

BlinkM::Device::FirmwareVersion::FirmwareVersion(const FirmwareVersion& src) :
  major(src.major),
  minor(src.minor) {
}

BlinkM::Device::FirmwareVersion::~FirmwareVersion() {
}

BlinkM::Device::Device(unsigned char address) :
  address(address) {
}

BlinkM::Device::Device(const Device& src) :
  address(src.address),
  adapter(src.adapter) {
}

BlinkM::Device::~Device() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

unsigned char BlinkM::Device::FirmwareVersion::getMajor() const {
  return major;
}

unsigned char BlinkM::Device::FirmwareVersion::getMinor() const {
  return minor;
}

void BlinkM::Device::setAddress(unsigned char address) {
  this->address = address;
}

unsigned char BlinkM::Device::getAddress() const {
  return address;
}

BlinkM::I2c::Adapter& BlinkM::Device::getAdapter() {
  return adapter;
}

const BlinkM::I2c::Adapter& BlinkM::Device::getAdapter() const {
  return adapter;
}

const BlinkM::Protocol& BlinkM::Device::getProtocol() const {
  return Singleton<Protocol>::getInstance();
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::Device::FirmwareVersion& BlinkM::Device::FirmwareVersion::operator=(
    const FirmwareVersion& src) {
  major = src.major;
  minor = src.minor;

  return *this;
}

void BlinkM::Device::FirmwareVersion::write(std::ostream& stream) const {
  stream << Serializable<unsigned char>(major) << "." <<
    Serializable<unsigned char>(minor);
}

BlinkM::Device& BlinkM::Device::operator=(const BlinkM::Device& src) {
  address = src.address;
  adapter = src.adapter;

  return *this;
}

void BlinkM::Device::connect() {
  adapter.open();
}

void BlinkM::Device::disconnect() {
  adapter.close();
}

void BlinkM::Device::send(Request& request) {
  request.setDeviceAddress(address);
  adapter.transfer(request);
}

bool BlinkM::Device::isConnected() {
  return adapter.isOpen();
}

std::ostream& operator<<(std::ostream& stream, const
    BlinkM::Device::FirmwareVersion& version) {
  version.write(stream);
  return stream;
}
