#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Variables and constants
#include "lib/variables.h"
#include "lib/functions.cpp"

// Global vars
app storeApps[APP_AMOUNT];
app installedApps[APP_AMOUNT];
app runningApps[APP_AMOUNT];

// Show apps
void showInterface(){
	
}

int main () {
	// Files do read
	fstream installedAppsFile;
	fstream storeAppsFile;
	fstream contextFile;

	// Load instaled apps in lists
	installedAppsFile.open( INSTALLED_APPS_FILE  );
	getApps( installedAppsFile, installedApps);
	// Load app store
	storeAppsFile.open( STORE_FILE );
	getApps( storeAppsFile, storeApps);

	//cout << "APPS INSTALADOS";
	//debug( installedApps );

	//cout << "STORE APPS";
	//debug( storeApps );

	installedAppsFile.close();
	storeAppsFile.close();

	//sleep(3000);
	//clearScreen;
	//cout << "\n\nTESTE!\n\n";

	return 0;
}