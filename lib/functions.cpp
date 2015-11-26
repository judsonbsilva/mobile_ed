// If is linux
#ifdef __linux__
	
	#define clearScreen cout << "\033c"
	#include <chrono>
	#include <thread>
	
	void sleep( int milliseconds ){
		std::this_thread::sleep_for(
			std::chrono::milliseconds( milliseconds )
		);
	}

// If is Windows
#elif _WIN32
	#include <conio.h>
	#define clearScreen system("cls")
#endif

// Count amout of apps in array
int countApps( app appList[] ){
	int counter = 0;
	
	for(int i = 0; i < APP_AMOUNT; i++){
		if( appList[i].name != "" )
			counter++;
	}
	
	return counter;
}

// This list has this app?
int hasApp( app theApp, app appList[] ){
	for(int i = 0, length = countApps(appList); i < length; i++ )
		if( appList[i].name == theApp.name )
			return i;

	return -1;
}

// Debug function do print app list
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
// Get the index of list to insert an app
int getIndexToInsert( app thisApp, app appList[] ){
	int length = countApps(appList),
		index = length;
	
	// If is empty
	if( length == 0 ) return 0;

	for(int i = 0; i < length; i++){
		if( thisApp.size <= appList[i].size ){
			index = i; break;
		}
	}

	return index;
}

// Move elements to rigth
void moveRigth(int index, int length, app appList[]){
	for(int i = length; i > index; i-- ){
		appList[i] = appList[i - 1];
		moveLength++;
	}
}

//Move elements to left
void moveLeft(int index, int length, app appList[]){
	app voidApp;

	for(int i = index; i < length; i++ ){
		appList[i] = appList[i + 1];
		moveLength++;
	}
	
	appList[length - 1] = voidApp; 
}


// Insert an app in a index on the list
void insertIn( app currentApp, app appList[] ){
	
	int length = countApps(appList);

	// If list is empty
	if( length == 0 ){
		appList[0] = currentApp;
		return;
	}

	int index = getIndexToInsert( currentApp, appList);

	if( index == length ){
	// If is the last elements
		appList[index] = currentApp;
	} else {
	// If element is between two other elements
		moveRigth(index, length, appList );
		appList[index] = currentApp;
	}
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

// get apps in a file
void getApps( ifstream & file, app appList[] ){
	
	string content;
	app current;
	int index;

	while( !file.eof() ){
	
		getline( file, content, '\n' );

		if( content == "" ) continue;

		index = content.find('|');

		current.name = content.substr(0, index);
		current.size = stoi(
			content.substr(index + 1, content.length())
		);
		
		insertIn(current, appList);
	}
}