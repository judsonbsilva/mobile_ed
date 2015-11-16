#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Define app struct
struct app {
	string name;
	int size;
};

#define APP_AMOUNT 100

// Global vars
app storeApps[APP_AMOUNT];


int countApps( app appList[] ){
	int counter = 0;
	
	for(int i = 0; i < APP_AMOUNT; i++){
		if( appList[i].name != "" )
			counter++;
	}
	
	return counter;
}



void debug( app appList[] ){
	cout << "[\n";
	
	for(int i = 0, length = countApps(appList); i < length; i++){
		cout << "\t{\n";
		cout << "\t\tname: " << appList[i].name << "\n";
		cout << "\t\tsize: " << appList[i].size << "\n";
		cout << "\t\n\t}\n";
	}

	cout << "]\n";
}

void moveLeft(int index, int length, app appList[]){
	app voidApp;

	for(int i = index; i < length; i++ )
		appList[i] = appList[i + 1];
	
	appList[length - 1] = voidApp; 
}

void removeOf( int index, app appList[] ){
	
	int length = countApps( appList );
	app	appVoid; 

	if( index >= 0 && index < length ){
		if( index == length - 1 )
			appList[index] = appVoid;
		else 
			moveLeft(index, length, appList);
	}
}


int main(){

	app test;
	
	test.name = "AAAAA";
	test.size = 0;
	storeApps[0] = test;
	test.name = "BBBB";
	test.size = 1;
	storeApps[1] = test;
	test.name = "CCCC";
	test.size = 2;
	storeApps[2] = test;
	test.name = "DDDDD";
	test.size = 3;
	storeApps[3] = test;
	test.name = "EEEEE";
	test.size = 4;
	storeApps[4] = test;

	debug(storeApps);
	removeOf( 1, storeApps );
	debug(storeApps);


	return 0;
}