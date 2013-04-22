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

#include "playscript.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::PlayScript::PlayScript(unsigned char scriptId, unsigned char
    scriptLine, unsigned char numRepetitions) :
  Request('p', 3, 0) {
  outputData[1] = scriptId;
  outputData[2] = numRepetitions;
  outputData[3] = scriptLine;
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

unsigned char BlinkM::PlayScript::getScriptId() const {
  return outputData[1];
}

void BlinkM::PlayScript::setScriptId(unsigned char scriptId) {
  outputData[1] = scriptId;
}

unsigned char BlinkM::PlayScript::getScriptLine() const {
  return outputData[3];
}

void BlinkM::PlayScript::setScriptLine(unsigned char scriptLine) {
  outputData[3] = scriptLine;
}

unsigned char BlinkM::PlayScript::getNumRepetitions() const {
  return outputData[2];
}

void BlinkM::PlayScript::setNumRepetitions(unsigned char numRepetitions) {
  outputData[2] = numRepetitions;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::PlayScript* BlinkM::PlayScript::clone() const {
  return new PlayScript(*this);
}

void BlinkM::PlayScript::read(std::istream& stream) {
  Serializable<unsigned char> scriptId, scriptLine, numRepetitions;

  setScriptId(scriptId.read(stream));
  setScriptLine(scriptLine.read(stream));
  setNumRepetitions(numRepetitions.read(stream));
}
