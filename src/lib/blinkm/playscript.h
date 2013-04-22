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

#ifndef BLINKM_PLAYSCRIPT_H
#define BLINKM_PLAYSCRIPT_H

/** \file playscript.h
  * \brief BlinkM play script request
  */

#include "request.h"

namespace BlinkM {
  class PlayScript :
    public Request {
  public:
    /** Construct a BlinkM play script request
      */
    PlayScript(unsigned char scriptId = 0, unsigned char scriptLine = 0,
      unsigned char numRepetitions = 0);

    /** Access the request's script ID
      */
    unsigned char getScriptId() const;
    void setScriptId(unsigned char scriptId);
    /** Access the request's script line
      */
    unsigned char getScriptLine() const;
    void setScriptLine(unsigned char scriptLine);
    /** Access the request's number of repetitions
      */
    unsigned char getNumRepetitions() const;
    void setNumRepetitions(unsigned char numRepetitions);

    PlayScript* clone() const;

    void read(std::istream& stream);
  };
};

#endif
