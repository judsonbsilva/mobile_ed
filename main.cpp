#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Variables and constants
#include "lib/variables.h"

// List functions
#include "lib/llv.h"

// Interface functions
#include "lib/interface.cpp"

int main () {
	
	homeApps.fa = 10;

	// Files do read
	ifstream installedAppsFile;
	ifstream storeAppsFile;
	
	// Load instaled apps in lists
	installedAppsFile.open( INSTALLED_APPS_FILE  );
		LLVgetApps( installedAppsFile, &installedApps);
	installedAppsFile.close();
	
	// Pass installed apps to home
	for(int i = installedApps.il; (i <= installedApps.fl && ((i - installedApps.il) < 10)); i++)
		LLVinsertIn( installedApps.list[i], &homeApps);
	
	// Load app store
	storeAppsFile.open( STORE_FILE );
		LLVgetApps( storeAppsFile, &storeApps);
	storeAppsFile.close();

	// Call interface here
	initHome();
	
	return 0;
}