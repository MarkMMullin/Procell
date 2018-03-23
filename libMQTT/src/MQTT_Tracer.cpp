/*
  This file is part of Dantalion.

  Dantalion is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Dantalion is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Dantalion.  If not, see <http://www.gnu.org/licenses/>.

  This code is an extreme fork of original code at https://github.com/ArduCAM
  and all changes are Copyright 2016 Mark M. Mullin (dantalion@falken-labs.com)
*/
#include "MQTT_Tracer.h"
#include "MQTTWrapper.h"

MQTT_Tracer::MQTT_Tracer(MQTTWrapper *publisher) {
    m_mqtt = publisher;
}

void MQTT_Tracer::Log(ELogSystem sys, ELogLevel lvl, const std::string &format, ...) {
    //if(!ShowTrace(sys,lvl)) return;
    char message[256];
    va_list args;
    va_start(args, format);
    vsprintf(message, format.c_str(), args);
    va_end(args);
    // create the topic string
    char topic[32];
    sprintf(topic, "log/trace/%d/%d", (int) sys, (int) lvl);
    // send it off
    m_mqtt->send_message(topic, message);
}
