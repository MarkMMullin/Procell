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

#ifndef MQTTWRAPPER_H
#define MQTTWRAPPER_H
#include <mosquittopp.h>
#include <string>
#include <stdint.h>
#include <functional>
#include <vector>

class MQTTExecutive;

/**
 * \class $classname
 *
 * \ingroup Arducam
 *
 * \brief 
 *
 * 
 *
 * \note 
 *
 */

class MQTTWrapper : public mosqpp::mosquittopp
{
 public:
    typedef std::function<void(const std::string& cmd,int camNo, const std::vector<std::string>* args,
                               const void* payload,const int payloadlen)> TDispatchCameraCommand;
  MQTTWrapper(MQTTExecutive* controller,const char *id, const char *host, int port);
  ~MQTTWrapper();

  inline bool send_message(const  char *topic,const  char * message) {  return send_message(topic,message,false); }
  inline bool send_message(const  char *topic,std::string& message) {  return send_message(topic,message,false);}
  inline bool send_message(const  char *topic,std::string& message,bool retained) {  return send_message(topic,message.c_str(),retained);}
  bool send_message(const  char *topic,uint8_t* copyBuffer,uint32_t& bufferSize);
  bool send_message(const  char *topic,const  char * _message,bool retained);

  
  virtual void on_connect(int rc);
  virtual void on_disconnect(int rc);
  virtual void on_message(const struct mosquitto_message *message);
  virtual void on_subcribe(int mid, int qos_count, const int *granted_qos);
  virtual void on_publish(int mid);

 private:
  // cannot promise constness because wrapper does command dispatches!!!!
  MQTTExecutive* m_controller;
  const char* host;
  const char* id;
  int port;
  int keepalive;
    TDispatchCameraCommand m_cameraCommandProcessor;
};
#endif
