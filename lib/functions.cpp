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

llde createLLDE(){
	llde newList;

	for(int i = 0; i < APP_AMOUNT; i++){
		newList.list[ i ].next = i+1;
		newList.list[ i ].previous = i-1;
		newList.list[ i ].content.size = -1;
	}
	
	return newList;
}

// Count amout of apps in array
int countApps( llde apps ){
	int counter = 0;

	for( int i = apps.init; i != -1; i = apps.list[i].next )
		if( apps.list[i].content.size != -1 )
			counter++;
		
	return counter;
};

// This list has this app?
int hasApp( app theApp, llde apps ){

	for(int i = apps.init; i != -1; i = apps.list[i].next )
		if( apps.list[i].content.name == theApp.name )
			return i;

	return -1;
}

// Debug function to print app list
void debug( llde apps ){
	
	cout << "Init: " << apps.init << "    Finish: " << apps.finish << "\n";
	cout << "Avaible: " << apps.avaible << "\n";
	cout << "[\n";

	if( apps.init == -1 ){
		cout << "]\n";
		return;
	}
	
	for(int i = apps.init; i != -1; i = apps.list[i].next){
		cout << "\n\t\tindx: " << i << "\n";
		cout << "\t\tnext: " << apps.list[i].next << "\n";
		cout << "\t\tprev: " << apps.list[i].previous << "\n";
		cout << "\t{\n";
		cout << "\t\tname: " << apps.list[i].content.name << "\n";
		cout << "\t\tsize: " << apps.list[i].content.size << "\n";
		cout << "\t\n\t}\n";
	}

	cout << "]\n";
}

// Get the index of list to insert an app
int getIndexToInsert( app thisApp, llde apps ){
	
	// If is empty
	if( countApps(apps) == 0 )
		return apps.list[ apps.avaible ].next;
	
	int lastIndex = 0;
	
	// In init
	if( thisApp.size <= apps.list[ apps.init ].content.size )
		return -1;
	
	// In finish
	if( thisApp.size >= apps.list[ apps.finish ].content.size )
		return apps.finish;
	
	for(int i = apps.init; i != -1; i = apps.list[i].next)
		if( apps.list[i].next != -1 )
			if( thisApp.size <= apps.list[ apps.list[i].next ].content.size )
				return i;
	

}

int getAndUpdateAvaible( llde *apps ){
	int index = apps->list[ apps->avaible ].next;
	apps->list[ apps->avaible ].next = apps->list[ index ].next;
	apps->list[ index ].previous = apps->avaible;
	return index;
}

// Insert an app in a index on the list
void insertIn( app currentApp, llde *apps ){
	
	int length = countApps(*apps),
		avaible = getAndUpdateAvaible( &(*apps) );

	// If list is empty
	if( length == 0 ){
		
		apps->list[ avaible ].next = -1;
		apps->list[ avaible ].previous = -1;
		apps->list[ avaible ].content = currentApp;
		
		apps->finish = avaible;
		apps->init = avaible;

		return;
	}

	int index   = getIndexToInsert( currentApp, *apps);

	// In init
	if( index == -1 ){

		apps->list[ avaible ].content  = currentApp;
		apps->list[ avaible ].next     = apps->init;
		apps->list[ avaible ].previous = -1;
		
		if( length > 1 )
			apps->list[ apps->init ].previous = avaible;
		
		apps->init = avaible;
		
	// In finish		
	} else if( index == apps->finish ){

		apps->list[ avaible ].content  = currentApp;
		apps->list[ avaible ].next     = -1;
		apps->list[ avaible ].previous = apps->finish; 
		apps->list[ apps->finish ].next = avaible;
		apps->finish = avaible;

	// Between
	} else {
		apps->list[ avaible ].content = currentApp;
		apps->list[ avaible ].next = apps->list[index].next;
		apps->list[ avaible ].previous = index;
		apps->list[ apps->list[ index ].next ].previous = avaible;
		apps->list[ index ].next = avaible;
	}
	
}

void removeOf( int index, llde *apps ){
	
	int length = countApps( *apps );
	
	if( length == 1 ){

		apps->list[ index ].next = apps->avaible;
		apps->avaible = index;

		apps->init = -1;
		apps->finish = -1;

		return;
	}
	
	// In init
	if( index == apps->init ){
		apps->init = apps->list[index].next;
		apps->list[ apps->init ].previous = -1;
		apps->list[index].next = apps->avaible;
		apps->avaible = index;
	// In finish
	} else if( index == apps->finish ){
		apps->finish = apps->list[ index ].previous;
		apps->list[ apps->finish ].next = -1;
		apps->list[ index ].next = apps->avaible;
		apps->avaible = index;
	// Between
	} else {
		apps->list[ apps->list[index].previous ].next = apps->list[ index ].next;
		apps->list[ apps->list[ index ].next ].previous = apps->list[ index ].previous; 
		apps->list[ index ].next = apps->avaible;
		apps->avaible = index;
	}

}

// get apps in a file
void getApps( ifstream & file, llde *apps ){
	
	string content;
	app current;
	int index;

	while( !file.eof() ){
	
		getline( file, content, '\n' );

		if( content == "" ) continue;

		index = content.find('|');

		current.name = content.substr(0, index);
		current.size = stoi( content.substr(index + 1, content.length()) );
		
		insertIn(current, apps);
	}
}