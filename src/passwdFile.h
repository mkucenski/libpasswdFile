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

#ifndef PASSWDFILE_H_
#define PASSWDFILE_H_

#include "libdelimText/src/delimTextFile.h"

#include <string>
#include <map>
#include <vector>
using namespace std;

class passwdFile : private delimTextFile {
	public:
		passwdFile();
		passwdFile(string strFilename);
		~passwdFile();
				
		bool open(string strFilename);
		bool close();
		
		string getUsername(long uid) { return get(uid, 0); };
		long getUID(string username) { return getAsLong(username, 2); };
		
		string getPassword(long uid) { return get(uid, 1); };
		string getPassword(string username) { return get(username, 1); };
		
		long getGID(long uid) { return getAsLong(uid, 3); };
		long getGID(string username) { return getAsLong(username, 3); };
		
		string getInfo(long uid) { return get(uid, 4); };
		string getInfo(string username) { return get(username, 4); };
		
		string getHome(long uid) { return get(uid, 5); };
		string getHome(string username) { return get(username, 5); };
		
		string getShell(long uid) { return get(uid, 6); };
		string getShell(string username) { return get(username, 6); };

	protected:
		string get(long uid, unsigned int field);
		string get(string username, unsigned int field);
		long getAsLong(long uid, unsigned int field);
		long getAsLong(string username, unsigned int field);
	
	private:
		map<long, delimTextRow*> uidToRowMap;
		map<string, delimTextRow*> usernameToRowMap;

	protected:
		vector<delimTextRow*> allRows;
};

#endif /*PASSWDFILE_H_*/
