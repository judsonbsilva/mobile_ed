#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Variables and constants
#include "lib/variables.h"
// List functions
#include "lib/llde.h"
#include "lib/llse.h"
#include "lib/llv.h"
#include "lib/pilha.h"
#include "lib/fila.h"
// Interface functions
// #include "lib/interface.cpp"

void showTest( fila tst ){
	cout << "-----------------------------------------" << "\n";
	for(int i = 0, to = tst.length; i < to; i++)
		cout << FILAgetApp(i, tst).name << "\n";
	cout << "-----------------------------------------" << "\n\n";
}

int main(){

	fila teste;

	string names[] = {"Google Keep", "Netshoes", "Ovo", "Facebook", "Solid Explorer", "Whatsapp", "Instagram", "Twitter"};
	int sizes[] = {2, 3, 5, 1, 4, 0, 7, 5};

	showTest( teste );

	app example;

	for(int i = 0; i < 5; i++){
		example.name = names[i];
		example.size = sizes[i];

		FILAinsertIn( example, &teste );
		showTest( teste );
	}

	for(int i = 4; i >= 0; i--){
		FILAremoveOf( &teste );
		showTest( teste );
	}

	// showTest();

	// removeOf( 52, &storeApps );

	// showTest();

	return 0;
}