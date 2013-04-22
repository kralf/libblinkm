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

#ifndef BLINKM_SINGLETON_H
#define BLINKM_SINGLETON_H

/** \file singleton.h
  * \brief Templated BlinkM singleton
  */

#include "base/exception.h"

namespace BlinkM {
  template <class C> class Singleton {
  public:
    /** Access the singleton instance
      */
    static C& getInstance();

    /** BlinkM singleton queries
      */
    static bool exists();
  private:
    static C*& instance();

    /** Construct a BlinkM singleton
      */
    Singleton();

    /** Destroy a BlinkM singleton
      */
    virtual ~Singleton();
  };
};

#include "base/singleton.tpp"

#endif