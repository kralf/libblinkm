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

#ifndef BLINKM_SETFADESPEED_H
#define BLINKM_SETFADESPEED_H

/** \file setfadespeed.h
  * \brief BlinkM set fade speed request
  */

#include "request.h"

namespace BlinkM {
  class SetFadeSpeed :
    public Request {
  public:
    /** Construct a BlinkM set fade speed request
      */
    SetFadeSpeed(unsigned char speed = 1);

    /** Access the request's speed
      */
    unsigned char getSpeed() const;
    void setSpeed(unsigned char speed);

    SetFadeSpeed* clone() const;

    void read(std::istream& stream);
  };
};

#endif
