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

	app test;

	showTest();
	test.name = "AAAAA";
	test.size = 1;

	insertIn( test, &storeApps );
	showTest();

	test.name = "BBBB";
	test.size = 3;

	insertIn( test, &storeApps );
	showTest();
	
	test.name = "CCCC";
	test.size = 0;
	
	insertIn( test, &storeApps );
	showTest();

	test.name = "DDDD";
	test.size = 55;
	
	insertIn( test, &storeApps );
	showTest();
	
	test.name = "EEEE";
	test.size = 2;

	insertIn( test, &storeApps );
	showTest();
	
	test.name = "FFFFF";
	test.size = 45;

	insertIn( test, &storeApps );
	showTest();
	
	test.name = "GGGG";
	test.size = 16;

	insertIn( test, &storeApps );
	showTest();

	test.name = "HHHH";
	test.size = 55;

	insertIn( test, &storeApps );
	showTest();

	return 0;
}