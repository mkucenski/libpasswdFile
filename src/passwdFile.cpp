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

#include "passwdFile.h"

passwdFile::passwdFile() {
}

passwdFile::passwdFile(string strFilename) {
	open(strFilename);
}

passwdFile::~passwdFile() {
	close();
}

bool passwdFile::open(string strFilename) {
	bool rv = true;
	
	if (delimTextFile::open(strFilename, ':')) {
		while (true) {
			delimTextRow* pDelimRowObj = new delimTextRow;
			if (pDelimRowObj) {
				allRows.push_back(pDelimRowObj);

				if (delimTextFile::getNextRow(pDelimRowObj)) {
					long UID = 0;
					string strUsername;
					if (pDelimRowObj->getFieldAsLong(2, &UID)) {
						uidToRowMap.insert(pair<long, delimTextRow*>(UID, pDelimRowObj));
					}
					if (pDelimRowObj->getField(0, &strUsername)) {
						usernameToRowMap.insert(pair<string, delimTextRow*>(strUsername, pDelimRowObj));
					}
				} else {
					break;
				}
			} else {
				rv = false; 
				break;
			}
		}
	} else {
		rv = false;
	}

	return rv;
}

bool passwdFile::close() {
	if (allRows.size() > 0) {
		for (vector<delimTextRow*>::iterator it = allRows.begin(); it != allRows.end(); it++) {
			delete *it;
		}
		allRows.clear();
	}
	
	return delimTextFile::close();
}

string passwdFile::get(long uid, unsigned int field) {
	string rv;

	if (uidToRowMap[uid])
		rv = uidToRowMap[uid]->getField(field);

	return rv;
}

string passwdFile::get(string username, unsigned int field) {
	string rv;
	
	if (usernameToRowMap[username])
		rv = usernameToRowMap[username]->getField(field);

	return rv;
}

long passwdFile::getAsLong(long uid, unsigned int field) {
	long rv = -1;

	if (uidToRowMap[uid])
		rv = uidToRowMap[uid]->getFieldAsLong(field);

	return rv;
}

long passwdFile::getAsLong(string username, unsigned int field) {
	long rv = -1;
	
	if (usernameToRowMap[username])
		rv = usernameToRowMap[username]->getFieldAsLong(field);

	return rv;
}
