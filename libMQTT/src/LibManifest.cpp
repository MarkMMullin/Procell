//
// Created by Mark Mullin on 3/10/18.
//
#include "MQTTExecutive.h"
//+ "." + std::string(BUILDVER) + "." + std::string(BUILDTYPE)
std::string MQTTExecutive::LibraryVersion() {
    return std::to_string(MAJORVER) + "." + std::to_string(MINORVER) + "." + std::to_string(PATCHVER) + "." + std::string(BUILDTYPE);
}
