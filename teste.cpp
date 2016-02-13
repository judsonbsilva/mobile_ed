#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Variables and constants
#include "lib/variables.h"
// List functions
#include "lib/llde.h"

// Interface functions
// #include "lib/interface.cpp"

void showTest( llde storeApps ){
	LLDEdebug(storeApps);
	cout << "\n";
}

int main(){

	llde storeApps = LLDEcreate();

	string names[] = {"Google Keep", "Netshoes", "Ovo", "Facebook", "Solid Explorer", "Whatsapp", "Instagram", "Twitter"};
	int sizes[] = {2, 3, 5, 1, 4, 0, 7, 5};

	showTest( storeApps );

	app example;

	for(int i = 0; i < 5; i++){
		example.name = names[i];
		example.size = sizes[i];

		LLDEinsertIn( example, &storeApps );
	}

	showTest( storeApps );
	LLDEremoveOf( storeApps.init, &storeApps );
	showTest( storeApps );
	LLDEremoveOf( storeApps.finish, &storeApps );
	showTest( storeApps );
	LLDEremoveOf( 2, &storeApps );
	showTest( storeApps );
	LLDEremoveOf( storeApps.finish, &storeApps );
	showTest( storeApps );
	LLDEremoveOf( storeApps.init, &storeApps );
	showTest( storeApps );
	// showTest();

	// removeOf( 52, &storeApps );

	// showTest();

	return 0;
}