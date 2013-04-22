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

#include <iostream>

#include "blinkm.h"

#include "command/application.h"

using namespace BlinkM;

int main(int argc, char **argv) {
  Command::Application application(
    "Send protocol request to BlinkM device");
  application[0] = Command::Argument(
    "I2C adapter special file device", "DEVICE", "/dev/i2c-0");
  application[1] = Command::Argument(
    "Identifier of request to be sent", "REQUEST", "GetFirmwareVersion");
  application[2] = Command::Argument(
    "Arguments of request or '-' (stdin)", "ARG", "-");
  application[2].setGreedy(true);
  application["address"] = Command::Argument(
    "I2C address of connected device", "ADDRESS", "0");
  application["timeout"] = Command::Argument(
    "Request timeout in ms", "TIMEOUT", "10");
  application["list-requests"] = Command::Argument(
    "List protocol requests and exit", "", false);

  if (application.parseArguments(argc, argv)) {
    Device device(application["address"].getValue<unsigned char>());

    device.getAdapter().setAddress(application[0].getValue());
    device.getAdapter().setTimeout(
      application["timeout"].getValue<size_t>()*1e-3);

    if (application["list-requests"].getValue<bool>()) {
      std::cout << device.getProtocol() << std::endl;
      return 0;
    }

//     device.connect();

    Pointer<Request> request = device.getProtocol().createRequest(
      application[1].getValue());
    if (application[2].getValue() != "-") {
      std::istringstream stream(application[2].getValue());
      stream >> *request;
    }
    else
      std::cin >> *request;

    return 0;

    device.send(*request);

    std::ostringstream stream;
    stream << *request;

    if (!stream.str().empty())
      std::cout << "Response: " << stream.str() << std::endl;
    else
      std::cout << "No response." << std::endl;

    device.disconnect();
  }

  return 0;
}
