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
	
	homeApps.fa = 10;

	// Files do read
	ifstream installedAppsFile;
	ifstream storeAppsFile;
	
	// Load instaled apps in lists
	installedAppsFile.open( INSTALLED_APPS_FILE  );
		getApps( installedAppsFile, &installedApps);
	installedAppsFile.close();
	
	// Pass instaled apps to home
	for(int i = installedApps.il; i <= installedApps.fl || i < 10; i++)
		insertIn( installedApps.list[i], &homeApps);
	
	// Load app store
	storeAppsFile.open( STORE_FILE );
		getApps( storeAppsFile, &storeApps);
	storeAppsFile.close();

	// Call interface here
	
	//debug( storeApps );
	
	removeOf( 50, &storeApps);

	//debug( storeApps );
	//initHome();
	
	return 0;
}