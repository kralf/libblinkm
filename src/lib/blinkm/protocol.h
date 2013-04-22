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

#ifndef BLINKM_PROTOCOL_H
#define BLINKM_PROTOCOL_H

/** \file protocol.h
  * \brief BlinkM communication protocol
  */

#include <iostream>
#include <map>

#include "base/object.h"
#include "base/exception.h"
#include "base/pointer.h"

#include "request.h"

namespace BlinkM {
  class Protocol :
    public Object {
  public:
    /** Types and non-static subclasses
      */
    class RequestError :
      public Exception {
    public:
      /** Construct a protocol request error
        */
      RequestError(const std::string& typeName);
    };

    /** Construct a BlinkM protocol
      */
    Protocol();
    Protocol(const Protocol& src);

    /** Destroy a BlinkM protocol
      */
    virtual ~Protocol();

    /** Access the type name of the request with the given command
      */
    std::string getTypeName(unsigned char command) const;

    /** BlinkM protocol assignments
      */
    Protocol& operator=(const Protocol& src);

    /** Create a BlinkM request with the specified type name
      */
    Request* createRequest(const std::string& typeName) const;

    /** BlinkM protocol queries
      */
    bool hasRequest(const std::string& typeName) const;

    /** Write the protocol to the given stream
      */
    void write(std::ostream& stream) const;
  protected:
    std::map<std::string, Pointer<Request> > requests;
  };
};

std::ostream& operator<<(std::ostream& stream, const
  BlinkM::Protocol& protocol);

#endif
