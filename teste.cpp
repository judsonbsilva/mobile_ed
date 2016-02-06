#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Variables and constants
#include "lib/variables.h"
// List functions
#include "lib/functions.cpp"

// Interface functions
// #include "lib/interface.cpp"

void showTest( llse storeApps ){
	debug(storeApps);
	cout << "\n";
}

int main(){

	llse storeApps = createLLSE();

	string names[] = {"Google Keep", "Netshoes", "Ovo", "Facebook", "Solid Explorer", "Whatsapp", "Instagram", "Twitter"};
	int sizes[] = {2, 3, 5, 1, 4, 0, 7, 5};

	showTest( storeApps );

	app example;

	for(int i = 0; i < 8; i++){
		example.name = names[i];
		example.size = sizes[i];

		insertIn( example, &storeApps );
	}

	showTest( storeApps );
	removeOf( storeApps.init, &storeApps );
	showTest( storeApps );
	removeOf( storeApps.finish, &storeApps );
	showTest( storeApps );
	removeOf( 3, &storeApps );
	showTest( storeApps );

	// showTest();

	// removeOf( 52, &storeApps );

	// showTest();

	return 0;
}