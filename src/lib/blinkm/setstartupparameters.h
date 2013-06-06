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

#ifndef BLINKM_SETSTARTUPPARAMETERS_H
#define BLINKM_SETSTARTUPPARAMETERS_H

/** \brief BlinkM set startup parameters request
  */

#include <map>

#include "request.h"

namespace BlinkM {
  class SetStartupParameters :
    public Request {
  public:
    /** Types and non-static subclasses
      */
    enum Action {
      none = 0,
      playScript = 1
    };

    class Actions :
      public std::map<Action, std::string> {
    public:
      /** Construct an actions object
        */
      Actions();
    };

    /** Construct a BlinkM set startup parameters request
      */
    SetStartupParameters(Action startupAction = none, unsigned char
      scriptId = 0, unsigned char numScriptRepetitions = 0, unsigned char
      fadeSpeed = 1, char timeAdjustment = 0);

    /** Access the request's startup action
      */
    Action getStartupAction() const;
    void setStartupAction(Action action);
    /** Access the request's script ID
      */
    unsigned char getScriptId() const;
    void setScriptId(unsigned char scriptId);
    /** Access the request's number of script repetitions
      */
    unsigned char getNumScriptRepetitions() const;
    void setNumScriptRepetitions(unsigned char numRepetitions);
    /** Access the request's fade speed
      */
    unsigned char getFadeSpeed() const;
    void setFadeSpeed(unsigned char speed);
    /** Access the request's time adjustment
      */
    char getTimeAdjust() const;
    void setTimeAdjust(char adjustment);

    SetStartupParameters* clone() const;

    void read(std::istream& stream);
  };
};

#endif
