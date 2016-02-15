struct fila {
	llse list;
	int length;
};

void FILAinsertIn( app theApp, fila * apps ){
	if( apps->length == 0 ){
		apps->list = LLSEcreate();
		LLSEinsertIn( theApp, &(apps->list));
	} else {
		int avaible = LLSEgetAndUpdateAvaible( &(apps->list) );
		apps->list.list[ avaible ].content = theApp;
		apps->list.list[ avaible ].next    = apps->list.init;
		apps->list.init = avaible;
	};

	apps->length++;
}

app FILAremoveOf( fila * apps ){
	app toReturn;
	if( apps->length > 0 ){
		toReturn = apps->list.list[ apps->list.finish ].content;
		LLSEremoveOf( apps->list.finish, &(apps->list) );
		apps->length--;
	}
	return toReturn;
}

app FILAgetApp( int index, fila apps){
	if( index >= 0 && index < apps.length ){
		for(int i = apps.list.init,counter = 0;
			i != -1;
			i = apps.list.list[i].next, counter++)
			if( counter == index )
				return apps.list.list[i].content;
	}
}

int FILAhasApp( app theApp, fila apps ){
	for(int i = apps.list.init,counter = 0;
		i != -1;
		i = apps.list.list[i].next, counter++)
		if( theApp.name == apps.list.list[i].content.name )
			return counter;

	return -1;
}