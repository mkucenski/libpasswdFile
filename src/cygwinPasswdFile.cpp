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

#include "cygwinPasswdFile.h"

string cygwinPasswdFile::getSID(long uid) {
	delimTextRow infoRowObj(passwdFile::getInfo(uid), ',');
	return infoRowObj.getField(infoRowObj.getFieldCount()-1);
}

string cygwinPasswdFile::getSID(string username) {
	delimTextRow infoRowObj(passwdFile::getInfo(username), ',');
	return infoRowObj.getField(infoRowObj.getFieldCount()-1);
}

long cygwinPasswdFile::getUIDBySID(string SID) {
	long rv = -1;
	
	long cachedUID = SIDtoUIDMap[SID];
	if ( cachedUID == 0) {
		for (vector<delimTextRow*>::iterator it = passwdFile::allRows.begin(); it != passwdFile::allRows.end(); it++) {
			long uid = (*it)->getFieldAsLong(2);
			if (SID == getSID(uid)) {
				rv = uid;
				break;
			}
		}
		SIDtoUIDMap[SID] = rv;
	} else {
		rv = cachedUID;
	}
	
	return rv;
}

string cygwinPasswdFile::getUsernameBySID(string SID) {
	string rv;
	
	long UID = getUIDBySID(SID);
	if (UID != -1) {
		rv = passwdFile::getUsername(UID);
	}
	
	return rv;	
}
