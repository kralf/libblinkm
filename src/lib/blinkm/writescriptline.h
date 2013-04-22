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

#ifndef BLINKM_WRITESCRIPTLINE_H
#define BLINKM_WRITESCRIPTLINE_H

/** \file writescriptline.h
  * \brief BlinkM write script line request
  */

#include "blinkm/scriptline.h"

#include "request.h"

namespace BlinkM {
  class WriteScriptLine :
    public Request {
  public:
    /** Construct a BlinkM write script line request
      */
    WriteScriptLine(unsigned char lineNumber = 0, const ScriptLine&
      line = ScriptLine());

    /** Access the request's line number
      */
    unsigned char getLineNumber() const;
    void setLineNumber(unsigned char lineNumber);
    /** Access the request's line
      */
    ScriptLine getLine() const;
    void setLine(const ScriptLine& line);

    WriteScriptLine* clone() const;

    void read(std::istream& stream);
  };
};

#endif
