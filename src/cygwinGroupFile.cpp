// Copyright 2007 Matthew A. Kucenski
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "cygwinGroupFile.h"

string cygwinGroupFile::getSID(long gid) { 
	return groupFile::getPassword(gid);
}

string cygwinGroupFile::getSID(string name) { 
	return groupFile::getPassword(name);
}

long cygwinGroupFile::getGIDBySID(string SID) {
	long rv = -1;
	
	for (vector<delimTextRow*>::iterator it = passwdFile::allRows.begin(); it != passwdFile::allRows.end(); it++) {
		if (SID == (*it)->getField(1)) {
			rv = (*it)->getFieldAsLong(2);
			break;
		}
	}
	
	return rv;
}
