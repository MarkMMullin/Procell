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
#ifndef TRACER_H
#define TRACER_H

#include<stdarg.h>
#include <string>

/**
 * \class Tracer
 *
 * \ingroup MMMUtil
 *
 * \brief Generic definition of trace message output
 *
 * 
 *
 * \note 
 *
 */

class Tracer {
public:
    /// identifies the subsystem this log message applies to
    enum ELogSystem {
        CAMERA = 1, MQTT = 2, REST = 4, EXECUTIVE = 8, VISION = 16
    };
    /// identifies the significance of this log message
    enum ELogLevel {
        CRITICAL = 1, ERROR = 2, WARN = 3, INFO = 4, DEBUG = 5, TRACE = 6
    };
    /// reference to the globally shared trace singleton
    static Tracer *Self();
    /// log a formatted trace message for a subsystem at a specific significance
    virtual void Log(ELogSystem sys, ELogLevel lvl, const std::string &msgFormat, ...) = 0;
    /// set level above which trace messages will be discarded
    static void SetTraceThreshold(ELogLevel traceLevel, ELogSystem traceSystem);
    /// returns true if the trace message should be reported given the current trace threshold
    inline bool ShowTrace(ELogSystem sys, ELogLevel lvl) {
        return ((((int) sys) & ((int) sm_traceSystem)) && lvl <= sm_traceThreshold);
    }

protected:
    /// initializing the base sets the global trace singleton pointer
    Tracer();
    /// maximum level for transmitting trace messages
    static ELogLevel sm_traceThreshold;
    static ELogSystem sm_traceSystem;
    /// singleton instance of the tracer
    static Tracer *sm_singleton;


};

#endif
