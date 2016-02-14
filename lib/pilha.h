struct pilha {
	llse list;
	int length;
};

void PIinsertIn( app theApp, pilha * apps ){
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

void PIremoveOf( pilha * apps ){
	if( apps->length > 0 ){
		LLSEremoveOf( apps->list.init, &(apps->list) );
		apps->length--;
	}
}

app PIgetApp( int index, pilha apps){
	if( index >= 0 && index < apps.length ){
		for(int i = apps.list.init,counter = 0;
			i != -1;
			i = apps.list.list[i].next, counter++)
			if( counter == index )
				return apps.list.list[i].content;
	}
}