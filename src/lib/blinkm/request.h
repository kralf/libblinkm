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

#ifndef BLINKM_REQUEST_H
#define BLINKM_REQUEST_H

/** \file request.h
  * \brief General BlinkM request
  */

#include "base/exception.h"

#include "i2c/request.h"

namespace BlinkM {
  class Request :
    public BlinkM::I2c::Request {
  public:
    /** Types and non-static subclasses
      */
    class ArgumentRangeError :
      public Exception {
    public:
      /** Construct a BlinkM request argument range error
        */
      template <typename T, typename U, typename V> ArgumentRangeError(
        const T& value, const U& minValue, const V& maxValue);

      /** BlinkM request argument range error assertion
        */
      template <typename T, typename U, typename V> static void assert(
        const T& value, const U& minValue, const V& maxValue);
    };

    /** Construct a BlinkM request
      */
    Request(unsigned char command = 0, size_t numArguments = 0,
      size_t numReturnValues = 0);
    Request(const Request& src);

    /** Destroy a BlinkM request
      */
    virtual ~Request();

    /** Access the request's command
      */
    void setCommand(unsigned char command);
    unsigned char getCommand() const;
    /** Access the request's number of arguments
      */
    size_t getNumArguments() const;
    /** Access the request's arguments
      */
    void setArguments(const std::vector<unsigned char>& arguments);
    std::vector<unsigned char> getArguments() const;
    /** Access the request's number of return values
      */
    size_t getNumReturnValues() const;
    /** Access the request's return values
      */
    const std::vector<unsigned char>& getReturnValues() const;

    /** BlinkM request assignments
      */
    Request& operator=(const Request& src);

    /** Clone the BlinkM request
      */
    virtual Request* clone() const;

    /** Read the request from the given stream
      */
    virtual void read(std::istream& stream);
    /** Write the request to the given stream
      */
    virtual void write(std::ostream& stream) const;
  };
};

std::istream& operator>>(std::istream& stream, BlinkM::Request& request);
std::ostream& operator<<(std::ostream& stream, const BlinkM::Request&
  request);

#include "request.tpp"

#endif
