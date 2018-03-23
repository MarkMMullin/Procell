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

//! macro to allocate a new buffer, copy string argument to it, and return a pointer to the new buffer
#define STRSAVE(x) strcpy(new char[strlen(x) + 1],x)
//! macro to delete and zero a pointer
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
//! macro to delete and zero an array pointer
#define SAFE_DELETE_ARRAY(p) { if(p) {delete[] (p); (p) = NULL; }}
//! macro to release and zero a handle
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
