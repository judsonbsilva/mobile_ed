#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Variables and constants
#include "lib/variables.h"
// List functions
#include "lib/llse.h"
// Interface functions
#include "lib/interface.cpp"



int main () {
	
	// Global vars
	storeApps = LLSEcreate();
	installedApps = LLSEcreate();
	homeApps = LLSEcreate();
	runningApps = LLSEcreate();

	// Files do read
	ifstream installedAppsFile;
	ifstream storeAppsFile;
	
	// Load instaled apps in lists
	installedAppsFile.open( INSTALLED_APPS_FILE  );
	LLSEgetApps( installedAppsFile, &installedApps);
	installedAppsFile.close();
	
	// Pass installed apps to home
	int counter = 1;
	for(int i = installedApps.init; i != -1; i = installedApps.list[i].next, counter++)
		if( counter <= 10 )
			LLSEinsertIn( installedApps.list[i].content, &homeApps);
	

	// Load app store
	storeAppsFile.open( STORE_FILE );
	LLSEgetApps( storeAppsFile, &storeApps);
	storeAppsFile.close();

	// Call interface here
	initHome();
	
	return 0;
}