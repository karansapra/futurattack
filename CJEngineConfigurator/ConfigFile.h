/*
 * ConfigFile.h
 *
 *  Created on: 25 oct. 2009
 *      Author: clement
 */

#ifndef CONFIGFILE_H_
#define CONFIGFILE_H_

class ConfigFile {
	ConfigFile();

	char _filename[512];

public:

	ConfigFile * OpenConfigFile(const char * filename);


	virtual ~ConfigFile();
};

#endif /* CONFIGFILE_H_ */
