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

#ifndef MQTT_TRACER_H
#define MQTT_TRACER_H

#include "Tracer.h"

class MQTTWrapper;

/**
 * \class MQTT_Tracer
 *
 * \ingroup
 *
 * \brief Handler for event logging messages sent over MQTT to follow system operation
 *
 * \note 
 *
 */

class MQTT_Tracer : public Tracer {
public:
    MQTT_Tracer(MQTTWrapper *publisher);
    /// write formatted message to log/trace/{sys}/{lvl}
    virtual void Log(ELogSystem sys, ELogLevel lvl, const std::string &msgFormat, ...);

protected:
    MQTTWrapper *m_mqtt;
};

#endif
