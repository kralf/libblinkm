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

#ifndef BLINKM_I2C_ADAPTER_H
#define BLINKM_I2C_ADAPTER_H

/** \brief BlinkM I2C bus adapter
  */

#include <string>
#include <vector>

#include "base/object.h"
#include "base/exception.h"

#include "i2c/request.h"

namespace BlinkM {
  namespace I2c {
    class Adapter :
      public BlinkM::Object {
    public:
      /** Types and non-static subclasses
        */
      class OperationError :
        public Exception {
      public:
        /** Construct an I2C adapter operation error
          */
        OperationError();
      };

      class OpenError :
        public Exception {
      public:
        /** Construct an I2C adapter open error
          */
        OpenError(const std::string& address);
      };

      class SetupError :
        public Exception {
      public:
        /** Construct an I2C adapter setup error
          */
        SetupError(const std::string& address);
      };

      class SendError :
        public Exception {
      public:
        /** Construct an I2C adapter send error
          */
        SendError(const std::string& address, int error);
      };

      class ReceiveTimeout :
        public Exception {
      public:
        /** Construct an I2C adapter receive timeout
          */
        ReceiveTimeout(const std::string& address);
      };

      class ReceiveError :
        public Exception {
      public:
        /** Construct an I2C adapter receive error
          */
        ReceiveError(const std::string& address, int error);
      };

      /** Construct a BlinkM I2C adapter
        */
      Adapter(const std::string& address = "", double timeout = 1e-2);
      Adapter(const Adapter& src);

      /** Destroy a BlinkM I2C adapter
        */
      virtual ~Adapter();

      /** Access the address of the I2C adapter
        */
      void setAddress(const std::string& address);
      const std::string& getAddress() const;
      /** Access the timeout of the I2C adapter
        */
      void setTimeout(double timeout);
      double getTimeout() const;

      /** BlinkM I2C adapter assignments
        */
      Adapter& operator=(const Adapter& src);

      /** BlinkM I2C adapter operations
        */
      void open();
      void close();
      void transfer(Request& request);

      /** BlinkM I2C adapter queries
        */
      bool isOpen() const;

      /** Send data over the I2C adapter
        */
      void send(const std::vector<unsigned char>& data);
      /** Receive data over the I2C adapter
        */
      void receive(std::vector<unsigned char>& data);
    protected:
      std::string address;
      double timeout;

      int handle;
      unsigned char slave;

      /** BlinkM I2C adapter operations
        */
      void setup(unsigned char slave);
    };
  };
};

#endif
