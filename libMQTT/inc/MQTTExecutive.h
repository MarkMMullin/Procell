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
#include <map>
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
    typedef std::function<void(const struct mosquitto_message *message)> MQTTDispatchFunction;
    MQTTExecutive(std::string mqttId,std::string url,int port);
    void Subscribe(std::string trigger,MQTTDispatchFunction handler,bool subscribeChildren = true);
    void Dispatch(const struct mosquitto_message *message);
    void Transmit(const std::string &topicName,uint8_t* buffer,uint32_t bufSize);
    /// \brief publish on the image channel
    /// This is used to publish per camera images such as raw and rectified.
    /// \param jpg Pointer to image data buffer in JPEG format
    /// \param jpgsize  Byte size of the image data buffer
    /// \param topicName full topic name will be image/<topicname>/camid/uuid
    /// \param uuid Identifies members of a common image process step - this allows matching of source rae
    /// stereo images and subsequent byproducts
    /// \param camid Camera index for controller, where left == 0 and right == 1
    void broadcast_image(unsigned char *jpg, uint32_t jpgsize, const std::string &topicName, const std::string &uuid,
                         int camid);
    /// \brief publsih on the waterfall channel
    /// \param jpg Pointer to image data buffer in JPEG format
    /// \param jpgsize Byte size of the image data buffer
    /// \param imageTopic full topic name will be waterfall/<topicname>uuid
    /// \param uuid Identifies members of a common image process step - this allows matching of source rae
    void broadcast_waterfall_image(unsigned char* jpg,uint32_t jpgsize,const std::string& imageTopic,const std::string& uuid);

    inline MQTTWrapper* GetPublisher() { return m_publisher;}
    static std::string CreateJSON(const std::map<std::string, std::string> &kvl, bool quoteValues);
    static std::string LibraryVersion();
 private:
    MQTTWrapper* m_publisher;
    std::map<std::string,MQTTDispatchFunction> m_messageHandlers;
    std::string m_clientName;
};

#endif
