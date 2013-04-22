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

#include "base/serializable.h"
#include "base/singleton.h"

#include "blinkm/protocol.h"

#include "scriptline.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::ScriptLine::ScriptLine() :
  durationTicks(0),
  request(new Request()) {
}

BlinkM::ScriptLine::ScriptLine(unsigned char durationTicks, const Request&
    request) :
  durationTicks(durationTicks),
  request(request.clone()) {
}

BlinkM::ScriptLine::ScriptLine(const ScriptLine& src) :
  durationTicks(src.durationTicks),
  request(src.request->clone()) {
}

BlinkM::ScriptLine::~ScriptLine() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

unsigned char BlinkM::ScriptLine::getDurationTicks() const {
  return durationTicks;
}

void BlinkM::ScriptLine::setDurationTicks(unsigned char durationTicks) {
  this->durationTicks = durationTicks;
}

void BlinkM::ScriptLine::setRequest(const Request& request) {
  this->request = request.clone();
}

const BlinkM::Request& BlinkM::ScriptLine::getRequest() const {
  return *request;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::ScriptLine& BlinkM::ScriptLine::operator=(const ScriptLine& src) {
  durationTicks = src.durationTicks;
  request = src.request->clone();

  return *this;
}

void BlinkM::ScriptLine::read(std::istream& stream) {
  Serializable<unsigned char> durationTicks;
  Serializable<std::string> typeName;

  this->durationTicks = durationTicks.read(stream);
  typeName.read(stream);

  request = Singleton<Protocol>::getInstance().createRequest(
    typeName.read(stream));
  request->read(stream);
}

void BlinkM::ScriptLine::write(std::ostream& stream) const {
  stream << (size_t)durationTicks << " " <<
    Singleton<Protocol>::getInstance().getTypeName(
    request->getCommand()) << *request;
}

std::istream& operator>>(std::istream& stream, BlinkM::ScriptLine&
    scriptLine) {
  scriptLine.read(stream);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const BlinkM::ScriptLine&
    scriptLine) {
  scriptLine.write(stream);
  return stream;
}
