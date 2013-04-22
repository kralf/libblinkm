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

#include "base/singleton.h"
#include "base/serializable.h"

#include "blinkm/protocol.h"

#include "readscriptline.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::ReadScriptLine::ReadScriptLine(unsigned char scriptId,
    unsigned char lineNumber) :
  Request('R', 2, 5) {
  outputData[1] = scriptId;
  outputData[2] = lineNumber;
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

unsigned char BlinkM::ReadScriptLine::getScriptId() const {
  return outputData[1];
}

void BlinkM::ReadScriptLine::setScriptId(unsigned char scriptId) {
  outputData[1] = scriptId;
}

unsigned char BlinkM::ReadScriptLine::getLineNumber() const {
  return outputData[2];
}

void BlinkM::ReadScriptLine::setLineNumber(unsigned char lineNumber) {
  outputData[2] = lineNumber;
}

BlinkM::ScriptLine BlinkM::ReadScriptLine::getResponse() const {
  ScriptLine line;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::ReadScriptLine* BlinkM::ReadScriptLine::clone() const {
  return new ReadScriptLine(*this);
}

void BlinkM::ReadScriptLine::read(std::istream& stream) {
  Serializable<unsigned char> scriptId, lineNumber;

  setScriptId(scriptId.read(stream));
  setLineNumber(lineNumber.read(stream));
}
