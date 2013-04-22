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

#ifndef BLINKM_I2C_REQUEST_H
#define BLINKM_I2C_REQUEST_H

/** \file request.h
  * \brief BlinkM IC2 request
  */

#include <vector>

#include "base/object.h"

namespace BlinkM {
  namespace I2c {
    class Request :
      public BlinkM::Object {
    friend class Adapter;
    public:
      /** Construct a BlinkM I2C request
        */
      Request(unsigned char deviceAddress = 0, size_t outputDataSize = 0,
        size_t inputDataSize = 0);
      Request(const Request& src);

      /** Destroy a BlinkM I2C request
        */
      virtual ~Request();

      /** Access the I2C request's device address
        */
      void setDeviceAddress(unsigned char deviceAddress);
      unsigned char getDeviceAddress() const;
      /** Access the I2C request's output data
        */
      void setOutputData(const std::vector<unsigned char>& outputData);
      const std::vector<unsigned char>& getOutputData() const;
      /** Access the I2C request's input data
        */
      const std::vector<unsigned char>& getInputData() const;

      /** BlinkM I2C request assignments
        */
      Request& operator=(const Request& src);
    protected:
      unsigned char deviceAddress;

      std::vector<unsigned char> outputData;
      std::vector<unsigned char> inputData;
    };
  };
};

#endif
