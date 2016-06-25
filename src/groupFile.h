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

#ifndef GROUPFILE_H_
#define GROUPFILE_H_

#include "passwdFile.h"

#include <string>
#include <map>
#include <vector>
using namespace std;

class groupFile : protected passwdFile {
	public:
		groupFile() : passwdFile() {};
		groupFile(string strFilename) : passwdFile(strFilename) {};
		~groupFile() {};
		
		bool open(string strFilename) { return passwdFile::open(strFilename); };
		bool close() { return passwdFile::close(); };

		string getName(long gid) { return passwdFile::get(gid, 0); };
		long getGID(string name) { return passwdFile::getAsLong(name, 2); };

		string getPassword(long uid) { return passwdFile::get(uid, 1); };
		string getPassword(string name) { return passwdFile::get(name, 1); };

		string getMembers(long gid) { return passwdFile::get(gid, 3); };
		string getMembers(string name) { return passwdFile::get(name, 3); };
};

#endif /*GROUPFILE_H_*/
