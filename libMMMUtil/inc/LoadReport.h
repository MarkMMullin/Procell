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

#ifndef LOADREPORT_H
#define LOADREPORT_H 1

#include "sys/types.h"
#include "sys/sysinfo.h"
#include "sys/times.h"
#include "sys/vtimes.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <map>

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
class LoadReport
{
 public:
  LoadReport();
  std::map<std::string,std::string> getPerformanceData();
 private:
  long long totalVirtualMemory();
  long long  totalVirtualMemoryUsed();
  int parseLine(char* line);
  int  processVirtualMemoryUsedInKb();
  long long totalPhysicalMemoryUsed();
  int processVirtualMemoryUsedKb();
  double totalCPUUsed();
  double processCPUUsed();
};


#endif // LOADREPORT_H
