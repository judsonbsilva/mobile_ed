#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Variables and constants
#include "lib/variables.h"
// Libs
#include "lib/llde.h"
#include "lib/llse.h"
#include "lib/llv.h"
#include "lib/pilha.h"
#include "lib/fila.h"

llv storeApps;
llde installedApps, runningApps;
llse homeApps;
fila appsToInstall;

// Interface functions
#include "lib/interface.cpp"

int main () {
	
	installedApps = LLDEcreate();
	runningApps = LLDEcreate();
	homeApps = LLSEcreate();
	
	// Files do read
	ifstream installedAppsFile;
	ifstream storeAppsFile;
	
	// Load instaled apps in lists
	installedAppsFile.open( INSTALLED_APPS_FILE  );
	LLDEgetApps( installedAppsFile, &installedApps);
	installedAppsFile.close();
	
	// Pass installed apps to home
	int counter = 1;
	for(int i = installedApps.init; i != -1; i = installedApps.list[i].next, counter++)
		if( counter < 10 )
			LLSEinsertIn( installedApps.list[i].content, &homeApps);
	
	// Load app store
	storeAppsFile.open( STORE_FILE );
	LLVgetApps( storeAppsFile, &storeApps);
	storeAppsFile.close();

	// Call interface here
	initHome();
	
	return 0;
}