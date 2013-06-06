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

#include "setstartupparameters.h"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

BlinkM::SetStartupParameters::Actions::Actions() {
  (*this)[none] = "None";
  (*this)[playScript] = "PlayScript";
}

BlinkM::SetStartupParameters::SetStartupParameters(Action startupAction,
    unsigned char scriptId, unsigned char numScriptRepetitions, unsigned char
    fadeSpeed, char timeAdjustment) :
  Request('B', 5, 0) {
  outputData[1] = startupAction;
  outputData[2] = scriptId;
  outputData[3] = numScriptRepetitions;
  outputData[4] = fadeSpeed;
  outputData[5] = timeAdjustment;
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

BlinkM::SetStartupParameters::Action
    BlinkM::SetStartupParameters::getStartupAction() const {
  return (Action)outputData[1];
}

void BlinkM::SetStartupParameters::setStartupAction(Action action) {
  outputData[1] = action;
}

unsigned char BlinkM::SetStartupParameters::getScriptId() const {
  return outputData[2];
}

void BlinkM::SetStartupParameters::setScriptId(unsigned char scriptId) {
  outputData[2] = scriptId;
}

unsigned char BlinkM::SetStartupParameters::getNumScriptRepetitions() const {
  return outputData[3];
}

void BlinkM::SetStartupParameters::setNumScriptRepetitions(unsigned char
    numRepetitions) {
  outputData[3] = numRepetitions;
}

unsigned char BlinkM::SetStartupParameters::getFadeSpeed() const {
  return outputData[4];
}

void BlinkM::SetStartupParameters::setFadeSpeed(unsigned char speed) {
  ArgumentRangeError::assert((size_t)speed, 1, 255);
  outputData[4] = speed;
}

char BlinkM::SetStartupParameters::getTimeAdjust() const {
  return outputData[5];
}

void BlinkM::SetStartupParameters::setTimeAdjust(char adjustment) {
  outputData[5] = adjustment;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

BlinkM::SetStartupParameters* BlinkM::SetStartupParameters::clone() const {
  return new SetStartupParameters(*this);
}

void BlinkM::SetStartupParameters::read(std::istream& stream) {
  Serializable<Action> action;
  Serializable<unsigned char> scriptId, numRepetitions, speed;
  Serializable<int> adjustment;

  setStartupAction(action.read(stream, Singleton<Actions>::getInstance()));
  setScriptId(scriptId.read(stream));
  setNumScriptRepetitions(numRepetitions.read(stream));
  setFadeSpeed(speed.read(stream));
  ArgumentRangeError::assert(adjustment.read(stream), -127, 127);
  setTimeAdjust(adjustment);
}
