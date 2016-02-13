#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Variables and constants
#include "lib/variables.h"
// List functions
#include "lib/llse.h"

// Interface functions
// #include "lib/interface.cpp"

void showTest( llse storeApps ){
	LLSEdebug(storeApps);
	cout << "\n";
}

int main(){

	llse storeApps = LLSEcreate();

	string names[] = {"Google Keep", "Netshoes", "Ovo", "Facebook", "Solid Explorer", "Whatsapp", "Instagram", "Twitter"};
	int sizes[] = {2, 3, 5, 1, 4, 0, 7, 5};

	showTest( storeApps );

	app example;

	for(int i = 0; i < 8; i++){
		example.name = names[i];
		example.size = sizes[i];

		LLSEinsertIn( example, &storeApps );
	}

	showTest( storeApps );
	LLSEremoveOf( storeApps.init, &storeApps );
	showTest( storeApps );
	LLSEremoveOf( storeApps.finish, &storeApps );
	showTest( storeApps );
	LLSEremoveOf( 3, &storeApps );
	showTest( storeApps );

	// showTest();

	// removeOf( 52, &storeApps );

	// showTest();

	return 0;
}