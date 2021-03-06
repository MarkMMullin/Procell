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
#include "MQTTExecutive.h"
#include "MQTT_Tracer.h"

#include "LoadReport.h"
#include <sstream>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>
#include <limits.h>

extern void LoadExecutiveStereoConfiguration(bool enabled, int *blockSize, int *disp12MaxDiff, int *minDisparity,
                                             int *numDisparities, int *preFilterCap, int *preFilterSize, int *preFilterType,
                                             int *smallerBlockSize, int *speckleRange, int *speckleWindowSize,
                                             int *textureThreshold, int *uniquenessRatio, int *valuelist);


MQTTExecutive::MQTTExecutive(std::string mqttId,std::string url,int port) {
    char hostname[256];
    m_clientName = mqttId;
    m_publisher = nullptr;
    gethostname(hostname, 256);
    std::cout << hostname << std::endl;
    m_publisher = new MQTTWrapper(this, m_clientName.c_str(), url.c_str(), port);
    new MQTT_Tracer(nullptr);
    Tracer::Self()->Log(Tracer::ELogSystem::MQTT, Tracer::ELogLevel::INFO, "MQTT Client %s online",std::string(hostname));
}
void MQTTExecutive::Dispatch(const struct mosquitto_message *message)
{
    std::istringstream f(message->topic);

    // break down the topic string
    std::string topicStr = message->topic;


    // bail if you don't have a handler
    std::map<std::string,MQTTDispatchFunction>::iterator it = m_messageHandlers.begin();
    while (it != m_messageHandlers.end())
    {
        // match on the starting part of the topic ?
        if (topicStr.compare(0, it->first.length(), it->first) == 0)
            break;
        it++;
    }
    if(it == m_messageHandlers.end())
    {
        std::cout << "Ignoring topic: "<< message->topic << std::endl;
        return;
    }
    it->second(message);

}
void MQTTExecutive::Subscribe(std::string trigger,MQTTDispatchFunction handler,bool subscribeChildren)
{
    bool doSubscribe = m_messageHandlers.find(trigger) == m_messageHandlers.end();
    m_messageHandlers[trigger] = handler;
    if(doSubscribe)
    {
        std::string tp = subscribeChildren ? trigger + "/#" : trigger;
        m_publisher->subscribe(nullptr,tp.c_str());
    }
}
void MQTTExecutive::Transmit(const std::string &topic,uint8_t* buffer,uint32_t bufSize)
{
    m_publisher->send_message(topic.c_str(), buffer,bufSize);
}
void MQTTExecutive::broadcast_image(unsigned char *jpg, uint32_t jpgsize, const std::string &topicName,
                                    const std::string &uuid, int camid)
{
    char topic[128];
    sprintf(topic, "image/%s/%d/%s",topicName.c_str(),camid,uuid.c_str());
    //std::cout << "topic: " << topic << std::endl;
    m_publisher->send_message(topic, jpg,jpgsize);
}
void MQTTExecutive::broadcast_waterfall_image(unsigned char* jpg,uint32_t jpgsize,const std::string& imageTopic,const std::string& uuid)
{
    char topic[256];
    sprintf(topic, "wtf/%s/%s",imageTopic.c_str(),uuid.c_str());
    m_publisher->send_message(topic, jpg,jpgsize);
    //std::cout << "Raw image ship:" << topic << std::endl;
 }

/**
 * @name createJSON - Converts a dictionary of KV pairs to an equivalent JSON representation
 * @param kvl -  map<String,String> of the key value pairs
 * @return std::string
 */

std::string MQTTExecutive::CreateJSON(const std::map<std::string, std::string> &kvl, bool quoteValues)
{
    char sb[2048];
    char wb[256];
    strcpy(sb,"{\n");
    for(std::map<std::string,std::string>::const_iterator iter = kvl.begin();iter != kvl.end();iter++)
    {
        if(strlen(sb) > 3)
            strcat(sb,",\n");
        std::string format(quoteValues ? "\t\"%s\" : \"%s\"" : "\t\"%s\" : %s");
        sprintf(wb,format.c_str(),iter->first.c_str(),iter->second.c_str());
        strcat(sb,wb);
    }
    strcat(sb,"\n}\n");
    return sb;
}



