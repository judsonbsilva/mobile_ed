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
	storeApps = createLLDE();
	installedApps = createLLDE();
	homeApps = createLLDE();
	runningApps = createLLDE();

	// Files do read
	ifstream installedAppsFile;
	ifstream storeAppsFile;
	
	// Load instaled apps in lists
	installedAppsFile.open( INSTALLED_APPS_FILE  );
	getApps( installedAppsFile, &installedApps);
	installedAppsFile.close();
	
	// Pass installed apps to home
	for(int i = installedApps.init; (i <= installedApps.fl && ((i - installedApps.il) < 10)); i++)
		insertIn( installedApps.list[i], &homeApps);
	
	// Load app store
	storeAppsFile.open( STORE_FILE );
	getApps( storeAppsFile, &storeApps);
	storeAppsFile.close();

	// Call interface here
	// initHome();
	
	return 0;
}