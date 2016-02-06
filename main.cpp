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
	
	// Global vars
	storeApps = createLLSE();
	installedApps = createLLSE();
	homeApps = createLLSE();
	runningApps = createLLSE();

	// Files do read
	ifstream installedAppsFile;
	ifstream storeAppsFile;
	
	// Load instaled apps in lists
	installedAppsFile.open( INSTALLED_APPS_FILE  );
	getApps( installedAppsFile, &installedApps);
	installedAppsFile.close();
	
	// Pass installed apps to home
	int counter = 1;
	for(int i = installedApps.init; i != -1; i = installedApps.list[i].next, counter++)
		if( counter <= 10 )
			insertIn( installedApps.list[i].content, &homeApps);
	

	// Load app store
	storeAppsFile.open( STORE_FILE );
	getApps( storeAppsFile, &storeApps);
	storeAppsFile.close();

	// Call interface here
	initHome();
	
	return 0;
}