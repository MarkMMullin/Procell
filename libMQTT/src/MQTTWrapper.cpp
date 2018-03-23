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
#include "MQTTWrapper.h"
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <sstream>
#include "MQTTExecutive.h"

MQTTWrapper::MQTTWrapper(MQTTExecutive *controller, const char *id, const char *host, int port) : mosquittopp(id) {
    mosqpp::lib_init();        // Mandatory initialization for mosquitto library
    this->id = id;
    this->keepalive = 60;    // Basic configuration setup for myMosq class
    this->m_controller = controller;
    this->port = port;
    this->host = host;
    connect_async(host,     // non blocking connection to broker request
                  port,
                  keepalive);
    loop_start();            // Start thread managing connection / publish / subscribe
}

MQTTWrapper::~MQTTWrapper() {
    loop_stop();            // Kill the thread
    mosqpp::lib_cleanup();    // Mosquitto library cleanup
}

/*
  struct mosquitto_message{
  int mid;
  char *topic;
  void *payload;
  int payloadlen;
  int qos;
  bool retain;
  };
*/
void MQTTWrapper::on_message(const struct mosquitto_message *message) {
    try {
        this->m_controller->Dispatch(message);
//        this->m_controller->Dispatch(strings[0], message->payload, message->payloadlen);
//        if (strings[0] == "camctl") {
//            int camno = std::stoi(strings[1]);
//            std::string cmd = strings[2];
//            if (strings.size() > 3) {
//                std::vector<std::string>::const_iterator first = strings.begin() + 3;
//                std::vector<std::string>::const_iterator last = strings.end();
//                std::vector<std::string> newVec(first, last);
//                this->m_controller->Dispatch(cmd, camno, &newVec, message->payload, message->payloadlen);
//            } else
//                this->m_controller->DispatchCameraCommand(cmd, camno, NULL, message->payload, message->payloadlen);
//        }
    }
    catch (...) {
        //todo - no silently swallowing all exceptions
    }
}


bool MQTTWrapper::send_message(const char *topic, const char *_message, bool retained) {
    // Send message - depending on QoS, mosquitto lib managed re-submission this the thread
    //
    // * NULL : Message Id (int *) this allow to latter get status of each message
    // * topic : topic to be used
    // * lenght of the message
    // * message
    // * qos (0,1,2)
    // * retain (boolean) - indicates if message is retained on broker or not
    // Should return MOSQ_ERR_SUCCESS
    int ret = publish(NULL, topic, strlen(_message), _message, 1, retained);
    return (ret == MOSQ_ERR_SUCCESS);
}

bool MQTTWrapper::send_message(const char *topic, uint8_t *copyBuffer, uint32_t &bufferSize) {
    char *cb1 = (char *) copyBuffer;
    int ret = publish(NULL, topic, bufferSize, cb1, 0, false);
    return (ret == MOSQ_ERR_SUCCESS);
}


void MQTTWrapper::on_disconnect(int rc) {
    std::cout << ">> MQTTWrapper - disconnection(" << rc << ")" << std::endl;
}


void MQTTWrapper::on_connect(int rc) {
    if (rc == 0) {
        std::cout << ">> myMosq - connected with server" << std::endl;
    } else {
        std::cout << ">> myMosq - Impossible to connect with server(" << rc << ")" << std::endl;
    }
}

void MQTTWrapper::on_publish(int mid) {
    // std::cout << ">> myMosq - Message (" << mid << ") succeed to be published " << std::endl;
}

void MQTTWrapper::on_subcribe(int mid, int qos_count, const int *granted_qos) {
}
