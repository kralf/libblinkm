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

#ifndef BLINKM_DEVICE_H
#define BLINKM_DEVICE_H

/** \file device.h
  * \brief BlinkM device
  */

#include <iostream>

#include "protocol.h"

#include "i2c/adapter.h"

namespace BlinkM {
  class Device :
    public Object {
  public:
    /** Types and non-static subclasses
      */
    class FirmwareVersion :
      public Object {
    public:
      /** Construct a BlinkM device firmware version
        */
      FirmwareVersion(unsigned char major = 0, unsigned char minor = 0);
      FirmwareVersion(const FirmwareVersion& src);

      /** Destroy a BlinkM device firmware version
        */
      virtual ~FirmwareVersion();

      /** Access the major version of the device firmware
        */
      unsigned char getMajor() const;
      void setMajor(unsigned char major);
      /** Access the minor version of the device firmware
        */
      unsigned char getMinor() const;
      void setMinor(unsigned char major);

      /** BlinkM device firmware version assignments
        */
      FirmwareVersion& operator=(const FirmwareVersion& src);

      /** Write the firmware version to the given stream
        */
      void write(std::ostream& stream) const;
    protected:
      unsigned char major;
      unsigned char minor;
    };

    /** Construct a BlinkM device
      */
    Device(unsigned char address = 0);
    Device(const Device& src);

    /** Destroy a BlinkM device
      */
    virtual ~Device();

    /** Access the address of the BlinkM device
      */
    void setAddress(unsigned char address);
    unsigned char getAddress() const;
    /** Access the I2C adapter of the BlinkM device
      */
    BlinkM::I2c::Adapter& getAdapter();
    const BlinkM::I2c::Adapter& getAdapter() const;
    /** Access the protocol of the BlinkM device
      */
    const Protocol& getProtocol() const;

    /** BlinkM device assignments
      */
    Device& operator=(const Device& src);

    /** Connect the BlinkM device
      */
    void connect();
    /** Disconnect the BlinkM device
      */
    void disconnect();

    /** Send the specified request to the BlinkM device
      */
    void send(Request& request);

    /** BlinkM device queries
      */
    bool isConnected();
  protected:
    unsigned char address;
    BlinkM::I2c::Adapter adapter;
  };
};

std::ostream& operator<<(std::ostream& stream, const
  BlinkM::Device::FirmwareVersion& version);

#endif
