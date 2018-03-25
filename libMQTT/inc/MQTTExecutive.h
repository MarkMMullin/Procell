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

#ifndef MQTTEXECUTIVE_H_
#define MQTTEXECUTIVE_H_
#include <iostream>
#include <unordered_map>
#include <cstdio>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <opencv2/core/mat.hpp>

#include "configuru.hpp"


#include "MQTTWrapper.h"
/**
 * \class MQTTExecutive
 *
 * \ingroup MQTT
 *
 * \brief Handles incoming MQTT requests and scheduled outgoing messages
 *
 * 
 *
 * \note 
 *
 */

class MQTTExecutive
{
 public:
    typedef std::function<void(const struct mosquitto_message *message,std::vector<std::string> strings)> MQTTDispatchFunction;
    MQTTExecutive(std::string mqttId,std::string url,int port);
    void Subscribe(std::string trigger,MQTTDispatchFunction handler);
    void Dispatch(const struct mosquitto_message *message);
    void broadcast_raw_image(unsigned char* jpg,uint32_t jpgsize,const std::string& topicName,const std::string& uuid,int camid);
    static std::string CreateJSON(const std::map<std::string, std::string> &kvl, bool quoteValues);
    static MQTTWrapper* sm_publisher;
    static std::string LibraryVersion();
 private:
    std::map<std::string,MQTTDispatchFunction> m_messageHandlers;
    std::string m_clientName;
};

#endif
