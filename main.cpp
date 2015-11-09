#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Variables and constants
#include "lib/variables.h"

// List functions
#include "lib/functions.cpp"

// Interface functions
#include "lib/interface.cpp"

int main () {
	
	// Files do read
	fstream installedAppsFile;
	fstream storeAppsFile;
	
	//fstream contextFile;

	// Load instaled apps in lists
	installedAppsFile.open( INSTALLED_APPS_FILE  );
	getApps( installedAppsFile, installedApps);
	installedAppsFile.close();
	
	// Load app store
	storeAppsFile.open( STORE_FILE );
	getApps( storeAppsFile, storeApps);
	storeAppsFile.close();

	// Call interface here
	initHome();
	
	return 0;
}