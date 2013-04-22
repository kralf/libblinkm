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

#include "writescriptline.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::WriteScriptLine::WriteScriptLine(unsigned char lineNumber,
    const ScriptLine& line) :
  Request('W', 7, 0) {
  setLineNumber(lineNumber);
  setLine(line);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

unsigned char BlinkM::WriteScriptLine::getLineNumber() const {
  return outputData[2];
}

void BlinkM::WriteScriptLine::setLineNumber(unsigned char lineNumber) {
  ArgumentRangeError::assert((size_t)lineNumber, 0, 49);
  outputData[2] = lineNumber;
}

BlinkM::ScriptLine BlinkM::WriteScriptLine::getLine() const {
  std::string typeName = Singleton<Protocol>::getInstance().getTypeName(
    outputData[4]);
  Pointer<Request> request = Singleton<Protocol>::getInstance().createRequest(
    typeName);

  std::vector<unsigned char> arguments(request->getNumArguments());
  std::copy(outputData.begin()+1, outputData.begin()+arguments.size()+1,
    arguments.begin());
  request->setArguments(arguments);

  return ScriptLine(outputData[3], *request);
}

void BlinkM::WriteScriptLine::setLine(const ScriptLine& line) {
  const std::vector<unsigned char>& outputData =
    line.getRequest().getOutputData();

  std::copy(outputData.begin(), outputData.end(),
    this->outputData.begin()+4);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::WriteScriptLine* BlinkM::WriteScriptLine::clone() const {
  return new WriteScriptLine(*this);
}

void BlinkM::WriteScriptLine::read(std::istream& stream) {
  Serializable<unsigned char> lineNumber;
  ScriptLine line;

  setLineNumber(lineNumber.read(stream));
  line.read(stream);
  setLine(line);
}
