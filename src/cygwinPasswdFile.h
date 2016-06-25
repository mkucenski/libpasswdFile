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

#ifndef CYGWINPASSWDFILE_H_
#define CYGWINPASSWDFILE_H_

#include "passwdFile.h"

#include <map>
#include <string>
using namespace std;

class cygwinPasswdFile : public passwdFile {
	//Cygwin stores the user's SID value as the last of several comma delimited values in the Info field of a standard 
	//passwd file.  
	
	public:
		cygwinPasswdFile() : passwdFile() {};
		cygwinPasswdFile(string strFilename) : passwdFile(strFilename) {};

		string getSID(long uid);
		string getSID(string username);

		long getUIDBySID(string SID);
		string getUsernameBySID(string SID);
	
	private:
		map<string, long> SIDtoUIDMap;
};

#endif /*CYGWINPASSWDFILE_H_*/
