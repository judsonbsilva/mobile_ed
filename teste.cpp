#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Variables and constants
#include "lib/variables.h"

// List functions
#include "lib/llv.h"

// Interface functions
// #include "lib/interface.cpp"

void showTest(){
	LLVdebug(storeApps);
	cout << "\n";
}

int main(){

	string names[] = {"Google Keep", "Netshoes", "Ovo", "Facebook", "Solid Explorer", "Whatsapp", "Instagram", "Twitter"};
	int sizes[] = {2, 6, 1, 8, 10, 9, 7, 5};

	app test;

	for(int i = 0; i < 8; i++){
		test.name = names[i];
		test.size = sizes[i];

		LLVinsertIn( test, &storeApps );
	}

	showTest();
	
	LLVremoveOf( 50, &storeApps );

	showTest();

	LLVremoveOf( 52, &storeApps );

	showTest();

	return 0;
}