// Count amout of apps in array
int LLVcountApps( llv appList ){
	return ( appList.il == -1 ) && (appList.fl == -1) ? 0: appList.fl - appList.il + 1;
};

// This list has this app?
int LLVhasApp( app theApp, llv apps ){

	for(int i = apps.il, length = apps.fl; i < length; i++ )
		if( apps.list[i].name == theApp.name )
			return i;

	return -1;
}

// Debug function to print app list
void LLVdebug( llv apps ){
	
	cout << "IA: " << apps.ia << "    FA: " << apps.fa << "\n";
	cout << "IL: " << apps.il << "    FL: " << apps.fl << "\n\n";

	cout << "[\n";

	if( apps.il == -1 || apps.fl == -1 ){
		cout << "]\n";
		return;
	}
	
	for(int i = apps.il, length = apps.fl; i <= length; i++){
		cout << "\t{\n";
		cout << "\t\tname: " << apps.list[i].name << "\n";
		cout << "\t\tsize: " << apps.list[i].size << "\n";
		cout << "\t\n\t}\n";
	}

	cout << "]\n";
}

// Get the index of list to insert an app
int LLVgetIndexToInsert( app thisApp, llv *apps ){
	
	// If is empty
	if( LLVcountApps(*apps) == 0 ) return APP_AMOUNT/2;

	for(int i = apps->il; i <= apps->fl; i++)
		if( thisApp.size <= apps->list[i].size )
			return i;
		
	return apps->fl + 1;
}

// Move elements to rigth
void LLVmoveRigth(int from, int to, llv * apps ){
	
	// If not space in right
	if( apps->fl + 1 == apps->fa ) return;

	for(int i = to; i >= from; i-- ){
		apps->list[i + 1] = apps->list[i];
		moveLength++;
	}

}

//Move elements to left
void LLVmoveLeft(int from, int to, llv *apps ){
	
	// If not space in left
	if( apps->il - 1 == apps->ia ) return;

	for(int i = from; i <= to; i++ ){
		apps->list[i - 1] = apps->list[i];
		moveLength++;
	}

}

// Insert an app in a index on the list
void LLVinsertIn( app currentApp, llv *apps ){
	
	int length = LLVcountApps(*apps);

	// If list is empty
	if( length == 0 ){

		apps->il = (apps->fa - apps->ia)/2;
		apps->fl = apps->il; 
		apps->list[ apps->il ] = currentApp;

		return;
	}

	int index = LLVgetIndexToInsert( currentApp, &*apps);
	
	//cout << "I: " << index << "\n" << "Size: " << currentApp.size << "\n\n"; 
	
	bool leftSpace = apps->il != apps->ia,
		 rightSpace = apps->fa != apps->fl;

	if( !leftSpace && !rightSpace ) return;

	// Finish of the list
	if( index == apps->fl ){
		// Has space on right
		if( rightSpace ){
			apps->list[ apps->fl + 1 ] = apps->list[ apps->fl ];
			apps->list[ apps->fl ] = currentApp;
			apps->fl += 1;
		} else {
			LLVmoveLeft( apps->il, apps->fl, &*apps );
			apps->il -= 1;
			apps->list[ apps->fl ] = apps->list[ apps->fl - 1 ];
			apps->list[ apps->fl - 1 ] = currentApp;
		}
		return;
	}

	// Begin of the list
	if( index == apps->il ){
		// Has space on left
		if( leftSpace ){ 
			apps->il -= 1;
			apps->list[ apps->il ] = currentApp;
		} else {
			LLVmoveRigth( apps->il, apps->fl, &*apps );
			apps->fl += 1;
			apps->list[ apps->il ] = apps->list[ apps->il + 1 ];
			apps->list[ apps->il + 1 ] = currentApp;
		} 
		return;
	}

	// After finish
	if( index > apps->fl ){
		//cout << "\n\n:OP:3:\n\n";
		if( rightSpace ){
			apps->fl += 1;
			apps->list[ apps->fl ] = currentApp;
		} else {
			LLVmoveLeft( apps->il, apps->fl, &*apps );
			apps->il -= 1;
			apps->list[ apps->fl ] = currentApp;
		}

		return;
	}

	// Between
	// If left has more elements
	if( abs( index - apps->il ) > abs( apps->fl - index ) ){
		LLVmoveRigth( index, apps->fl, &*apps);
		apps->fl += 1;
		apps->list[index] = currentApp;
	// If right has more elements
	} else {
		LLVmoveLeft( apps->il, index, &*apps);
		apps->il -= 1;
		apps->list[index - 1] = currentApp;
	}
	
}

void LLVremoveOf( int index, llv *apps ){
	
	int length = LLVcountApps( *apps );
	
	if( length == 1 ){

		apps->il = -1;
		apps->fl = -1;

		return;
	}
	// In finish of list
	if( index == apps->fl ){
		apps->fl -= 1;
		return;
	}
	// In begin of list
	if( index == apps->il ){
		apps->il += 1;
		return;
	}

	// If left has more elements
	if( abs( index - apps->il ) > abs( apps->fl - index ) ){
		LLVmoveLeft( index + 1, apps->fl, &*apps);
		apps->fl -= 1;
	// If right has more elements
	} else {
		LLVmoveRigth( apps->il, index - 1, &*apps);
		apps->il += 1;
	}
}

// get apps in a file
void LLVgetApps( ifstream & file, llv *apps ){
	
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
		
		LLVinsertIn(current, &(*apps));
	}
}