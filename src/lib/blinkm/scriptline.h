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

#ifndef BLINKM_SCRIPTLINE_H
#define BLINKM_SCRIPTLINE_H

/** \brief BlinkM script line
  */

#include "base/object.h"
#include "base/pointer.h"

#include "blinkm/request.h"

namespace BlinkM {
  class ScriptLine :
    public Object {
  public:
    /** Construct a BlinkM script line
      */
    ScriptLine();
    ScriptLine(unsigned char durationTicks, const Request& request);
    ScriptLine(const ScriptLine& src);

    /** Destroy a BlinkM script line
      */
    virtual ~ScriptLine();

    /** Access the request's duration in ticks
      */
    unsigned char getDurationTicks() const;
    void setDurationTicks(unsigned char durationTicks);
    /** Access the script line's request
      */
    void setRequest(const Request& request);
    const Request& getRequest() const;

    /** BlinkM script line assignments
      */
    ScriptLine& operator=(const ScriptLine& src);

    /** Read the script line from the given stream
      */
    virtual void read(std::istream& stream);
    /** Write the script line to the given stream
      */
    virtual void write(std::ostream& stream) const;
  protected:
    unsigned char durationTicks;
    Pointer<Request> request;
  };
};

std::istream& operator>>(std::istream& stream, BlinkM::ScriptLine&
  scriptLine);
std::ostream& operator<<(std::ostream& stream, const BlinkM::ScriptLine&
  scriptLine);

#endif
