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

#include "protocol.h"

#include "getfirmwareversion.h"
#include "setaddress.h"
#include "getaddress.h"
#include "setcolor.h"
#include "getcolor.h"
#include "fadetocolor.h"
#include "fadetorandomcolor.h"
#include "playscript.h"
#include "stopscript.h"
#include "readscriptline.h"
#include "writescriptline.h"
#include "setfadespeed.h"
#include "settimeadjust.h"
#include "setstartupparameters.h"
#include "user.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::Protocol::RequestError::RequestError(const std::string& typeName) :
  Exception("Invalid request: %s", typeName.c_str()) {
}

BlinkM::Protocol::Protocol() {
  requests["GetFirmwareVersion"] = new GetFirmwareVersion();
  requests["SetAddress"] = new SetAddress();
  requests["GetAddress"] = new GetAddress();
  requests["SetColor"] = new SetColor();
  requests["GetColor"] = new GetColor();
  requests["FadeToColor"] = new FadeToColor();
  requests["FadeToRandomColor"] = new FadeToRandomColor();
  requests["PlayScript"] = new PlayScript();
  requests["StopScript"] = new StopScript();
  requests["ReadScriptLine"] = new ReadScriptLine();
  requests["WriteScriptLine"] = new WriteScriptLine();
  requests["SetFadeSpeed"] = new SetFadeSpeed();
  requests["SetTimeAdjust"] = new SetTimeAdjust();
  requests["SetStartupParameters"] = new SetStartupParameters();
  requests["User"] = new User();
}

BlinkM::Protocol::Protocol(const Protocol& src) {
  operator=(src);
}

BlinkM::Protocol::~Protocol() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

std::string BlinkM::Protocol::getTypeName(unsigned char command) const {
  for (std::map<std::string, Pointer<Request> >::const_iterator
      it = requests.begin(); it != requests.end(); ++it)
    if (it->second->getCommand() == command)
      return it->first;

  return "User";
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::Protocol& BlinkM::Protocol::operator=(const Protocol& src) {
  requests.clear();

  for (std::map<std::string, Pointer<Request> >::const_iterator
      it = src.requests.begin(); it != src.requests.end(); ++it)
    requests.insert(std::make_pair(it->first, it->second->clone()));

  return *this;
}

BlinkM::Request* BlinkM::Protocol::createRequest(const std::string&
    typeName) const {
  std::map<std::string, Pointer<BlinkM::Request> >::const_iterator
    it = requests.find(typeName);

  if (it != requests.end())
    return it->second->clone();
  else
    throw RequestError(typeName);
}

bool BlinkM::Protocol::hasRequest(const std::string& typeName) const {
  return requests.find(typeName) != requests.end();
}

void BlinkM::Protocol::write(std::ostream& stream) const {
  for (std::map<std::string, Pointer<Request> >::const_iterator
      it = requests.begin(); it != requests.end(); ++it)
    stream << std::endl << it->first;
}

std::ostream& operator<<(std::ostream& stream, const BlinkM::Protocol&
    protocol) {
  protocol.write(stream);
  return stream;
}
