// Node of llse
struct node {
	// The app
	app content;
	// Next node
	int previous;
};

struct llse {
	node list[APP_AMOUNT];
	int init = -1, finish = -1, avaible = 0;
};


llse LLSEcreate(){
	llse newList;

	for(int i = 0; i < APP_AMOUNT; i++){
		newList.list[ i ].next = i+1;
		newList.list[ i ].content.size = -1;
	}
	
	return newList;
}

// Count amout of apps in array
int LLSEcountApps( llse apps ){
	int counter = 0;

	for( int i = apps.init; i != -1; i = apps.list[i].next )
		if( apps.list[i].content.size != -1 )
			counter++;
		
	return counter;
};

// This list has this app?
int LLSEhasApp( app theApp, llse apps ){
	for(int i = apps.init; i != -1; i = apps.list[i].next )
		if( apps.list[i].content.name == theApp.name )
			return i;

	return -1;
}

int LLSEgetTheIndex( int number, llse apps ){
	for(int i = apps.init, counter = 1; i != -1; i = apps.list[i].next, counter++ )
		if( counter == number ) return i;

	return -1;
}

// Debug function to print app list
void LLSEdebug( llse apps ){
	
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
		cout << "\t{\n";
		cout << "\t\tname: " << apps.list[i].content.name << "\n";
		cout << "\t\tsize: " << apps.list[i].content.size << "\n";
		cout << "\t\n\t}\n";
	}

	cout << "]\n";
}

// Get the index of list to insert an app
int LLSEgetIndexToInsert( app thisApp, llse apps ){
	
	// If is empty
	if( LLSEcountApps(apps) == 0 )
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

int LLSEgetAndUpdateAvaible( llse *apps ){
	int index = apps->list[ apps->avaible ].next;
	apps->list[ apps->avaible ].next = apps->list[ index ].next;
	return index;
}

// Insert an app in a index on the list
void LLSEinsertIn( app currentApp, llse *apps ){
	
	int length = LLSEcountApps(*apps),
		avaible = LLSEgetAndUpdateAvaible( &(*apps) );

	// If list is empty
	if( length == 0 ){
		
		apps->list[ avaible ].next = -1;
		apps->list[ avaible ].content = currentApp;
		
		apps->finish = avaible;
		apps->init = avaible;

		return;
	}

	int index = LLSEgetIndexToInsert( currentApp, *apps);

	// In init
	if( index == -1 ){

		apps->list[ avaible ].content = currentApp;
		apps->list[ avaible ].next    = apps->init;
		apps->init = avaible;
		
	// In finish		
	} else if( index == apps->finish ){

		apps->list[ avaible ].content = currentApp;
		apps->list[ avaible ].next    = -1;
	
		apps->list[ apps->finish ].next = avaible;
		apps->finish = avaible;

	// Between
	} else {
		apps->list[ avaible ].content = currentApp;
		apps->list[ avaible ].next = apps->list[index].next;
		apps->list[ index ].next = avaible;
	}
	
}

void LLSEremoveOf( int index, llse *apps ){
	
	int length = LLSEcountApps( *apps );
	
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
		apps->list[index].next = apps->avaible;
		apps->avaible = index;
	// In finish
	} else if( index == apps->finish ){
		for(int i = apps->init; i != -1; i = apps->list[i].next){
			if( apps->list[i].next == index ){
				apps->list[i].next = -1;
				apps->finish = i;
				break;
			}
		}
		apps->list[index].next = apps->avaible;
		apps->avaible = index;
	// Between
	} else {
		for(int i = apps->init; i != -1; i = apps->list[i].next){
			if( apps->list[i].next == index ){
				apps->list[i].next = apps->list[index].next;
				break;
			}
		}
		apps->list[index].next = apps->avaible;
		apps->avaible = index;
	}

}

// get apps in a file
void LLSEgetApps( ifstream & file, llse *apps ){
	
	string content;
	app current;
	int index;

	while( !file.eof() ){
	
		getline( file, content, '\n' );

		if( content == "" ) continue;

		index = content.find('|');

		current.name = content.substr(0, index);
		current.size = stoi( content.substr(index + 1, content.length()) );
		
		LLSEinsertIn(current, apps);
	}
}