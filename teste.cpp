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

void showTest(){
	debug(storeApps);
	cout << "\n";
}

int main(){

	string names[] = {"Google Keep", "Netshoes", "Ovo", "Facebook", "Solid Explorer", "Whatsapp", "Instagram", "Twitter"};
	int sizes[] = {2, 6, 1, 8, 10, 9, 7, 5};

	app test;

	for(int i = 0; i < 8; i++){
		test.name = names[i];
		test.size = sizes[i];

		insertIn( test, &storeApps );
	}

	showTest();
	
	removeOf( 50, &storeApps );

	showTest();

	removeOf( 52, &storeApps );

	showTest();

	return 0;
}