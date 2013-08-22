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

#include <linux/i2c-dev.h>

#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "smbus/smbus.h"

#include "adapter.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::I2c::Adapter::OperationError::OperationError() :
  Exception("Invalid operation on closed adapter") {
}

BlinkM::I2c::Adapter::OpenError::OpenError(const std::string& address) :
  Exception("Error opening I2C adapter: %s", address.c_str()) {
}

BlinkM::I2c::Adapter::SetupError::SetupError(const std::string&
    address) :
  Exception("Error setting I2C adapter attributes: %s", address.c_str()) {
}

BlinkM::I2c::Adapter::SendError::SendError(const std::string& address,
    int error) :
  Exception("Send failed on I2C adapter %s: %s", address.c_str(),
    strerror(error)) {
}

BlinkM::I2c::Adapter::ReceiveTimeout::ReceiveTimeout(const std::string&
    address) :
  Exception("Receive timeout on I2C adapter %s", address.c_str()) {
}

BlinkM::I2c::Adapter::ReceiveError::ReceiveError(const std::string&
    address, int error) :
  Exception("Receive failed on I2C adapter %s: %s", address.c_str(),
    strerror(error)) {
}

BlinkM::I2c::Adapter::Adapter(const std::string& address, double timeout) :
  address(address),
  timeout(timeout),
  handle(0),
  slave(0) {
  if (!this->address.empty())
    open();
}

BlinkM::I2c::Adapter::Adapter(const Adapter& src) :
  address(src.address),
  timeout(src.timeout),
  handle(0),
  slave(0) {
}

BlinkM::I2c::Adapter::~Adapter() {
  if (handle)
    close();
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

void BlinkM::I2c::Adapter::setAddress(const std::string& address) {
  if (handle) {
    close();
    this->address = address;
    open();
  }
  else
    this->address = address;
}

const std::string& BlinkM::I2c::Adapter::getAddress() const {
  return address;
}

void BlinkM::I2c::Adapter::setTimeout(double timeout) {
  this->timeout = timeout;
}

double BlinkM::I2c::Adapter::getTimeout() const {
  return timeout;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::I2c::Adapter& BlinkM::I2c::Adapter::operator=(const Adapter&
    src) {
  if (handle)
    close();

  address = src.address;
  timeout = src.timeout;

  if (src.handle)
    open();

  return *this;
}

void BlinkM::I2c::Adapter::open() {
  if (!handle) {
    handle = ::open(address.c_str(), O_RDWR | O_NDELAY);

    if (handle > 0)
      setup(slave);
    else
      throw OpenError(address);
  }
}

void BlinkM::I2c::Adapter::close() {
  if (handle) {
    fsync(handle);
    ::close(handle);

    handle = 0;
  }
}

void BlinkM::I2c::Adapter::transfer(Request& request) {
  if (request.deviceAddress != slave)
    setup(request.deviceAddress);

  if (!request.outputData.empty())
    send(request.outputData);

  if (!request.inputData.empty())
    receive(request.inputData);
}

bool BlinkM::I2c::Adapter::isOpen() const {
  return handle;
}

void BlinkM::I2c::Adapter::send(const std::vector<unsigned char>& data) {
  if (handle) {
    for (int i = 0; i < data.size(); ++i) {
      result = i2c_smbus_write_byte(handle, data[i]);
      
      if (result < 0)
        break;
    }

    if (result < 0)
      throw SendError(address, errno);
  }
  else
    throw OperationError();
}

void BlinkM::I2c::Adapter::receive(std::vector<unsigned char>& data) {
  if (handle) {
    size_t i = 0;
    struct timeval time;
    fd_set set;
    int error;

    while (i < data.size()) {
      time.tv_sec = 0;
      time.tv_usec = timeout*1e6;

      FD_ZERO(&set);
      FD_SET(handle, &set);

      error = select(handle+1, &set, NULL, NULL, &time);
      if (error == 0)
        throw ReceiveTimeout(address);
      else if (error < 0)
        throw ReceiveError(address, errno);
      
      ssize_t result = 0;
      for (int i = 0; i < data.size(); ++i) {
        result = i2c_smbus_read_byte(handle);
        
        if (result >= 0)
          data[i] = result;
        else
          break;
      }
      
      if (result < 0)
        throw ReceiveError(address, errno);
    }
  }
  else
    throw OperationError();
}

void BlinkM::I2c::Adapter::setup(unsigned char slave) {
  if (ioctl(handle, I2C_SLAVE_FORCE, slave) >= 0)
    this->slave = slave;
  else
    throw SetupError(address);
}
