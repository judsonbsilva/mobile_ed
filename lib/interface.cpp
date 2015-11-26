// Global functions
void initStore();
void initHome();
void initMyApps();
void initRunning();
void closeApp();

// To print a title in screen
void setInterfaceTitle( string title, string subtitle ){
	clearScreen;
	cout << "\t\t|------------------|\n\t\t|    " << title << "    |\n\t\t|------------------|\n\n\n";
	cout << "   " << subtitle << "\n\n";
}
// To print a item list in screen
void setItemList( int i, string item ){
	cout << "   " << i << ". " << item << "\n"; 
}

void initStore(){

	setInterfaceTitle("   STORE  ", "Selecione um para instalar");

	int length = countApps(storeApps);

	for(int i = 0; i < length; i++ )
		setItemList(i + 1, storeApps[i].name);

	cout << "\n";
	setItemList(0, "Voltar\n");

	int input;
	cin >> input;

	// Exit
	if( input == 0 ){	
		initHome(); return;
	} else if( input < 0 || input > length ){
		initStore(); return;
	}

	for(int i = 0; i <= length; i++){
		if( (input - 1) == i ){
			if( hasApp(storeApps[i], installedApps) > -1 ){
				cout << "   " << (storeApps[i].name) << " já instalado.\n";
				sleep(1000);
				initStore();
			} else {
				cout << "   " << (storeApps[i].name) << " instalado com sucesso.\n";
				insertIn(storeApps[i], installedApps);
				sleep(1000);
				initHome();
			}
		}
	}
}

// Show screen
void initHome(){
	
	setInterfaceTitle("  INÍCIO  ", "Selecione um item do menu");

	setItemList(1, "Store");
	setItemList(2, "Meus Apps");
	setItemList(3, "Executando");
	cout << "\n";
	setItemList(0, "Voltar\n");

	int input;
	cin >> input;

	switch( input ){
		case 0: closeApp(); break;
		case 1: initStore(); break;
		case 2: initMyApps(); break;
		case 3: initRunning(); break;
		default: initHome();
	}

}

void initMyApps(){

	setInterfaceTitle(" MEUS APPS","");
	
	int length = countApps(installedApps);

	if( length == 0 ){
		cout << "  Você não possui apps instalados.\n\n";
		sleep(2000);
		initHome();
		return;
	}

	setInterfaceTitle(" MEUS APPS", "Selecione um app para rodar");

	for(int i = 0; i < length; i++ )
		setItemList(i + 1, installedApps[i].name);

	cout << "\n   0. Voltar\n";
	cout << "\n   Para apagar digite '-' e o número do app\n";

	int input;
	cin >> input;

	if( input == 0 ){
		initHome();
		return;
	} else if( input < -length || input > length ){
		initMyApps();
		return;
	}

	for( int i = 0; i < length; i++){
		if( (input - 1) == i ){
			if( hasApp(installedApps[i], runningApps) > -1 ){
				cout << "   " << (installedApps[i].name) << " já está sendo executado.\n";
				sleep(1000);
				initMyApps();
			} else {
				cout << "   " << (installedApps[i].name) << " rodando.\n";
				insertIn(installedApps[i], runningApps);
				sleep(1000);
				initHome();
			}
		} else if ( ( abs(input) - 1 ) == i ){
			
			char response;
			int appRunning = hasApp(installedApps[i], runningApps);
			
			if( appRunning > -1 ){
				cout << "   " << installedApps[i].name << " Está executando. Desenha mesmo excluir? (S/N)";
				cin >> response;
			}

			if( appRunning == -1 || response == 's' || response == 'S' ){

				cout << "   " << (installedApps[i].name) << " apagado.\n";
				removeOf(i, installedApps);
				
				if( appRunning > -1 ){
					removeOf(appRunning, runningApps);
				}

				sleep(1000);
			
			}

			initMyApps();
		}

	}

}

void initRunning(){
	setInterfaceTitle("  RODANDO ","");
	
	int length = countApps(runningApps);

	if( length == 0 ){
		cout << "  Você não possui apps rodando.\n\n";
		sleep(2000);
		initHome();
		return;
	}

	setInterfaceTitle("  RODANDO ","Selecione para fechar");
	
	for(int i = 0; i < length; i++ )
		setItemList(i + 1, runningApps[i].name);


	cout << "\n   0. Voltar\n";
	
	int input;
	cin >> input;

	if( input == 0 ){
		initHome();
		return;
	} else if( input < 0 || input > length ){
		initRunning();
		return;
	}

	cout << runningApps[input - 1].name << " fechado.\n";
	sleep(1000);
	removeOf( input - 1, runningApps );
	initHome();

}

void closeApp(){
	
	clearScreen;
	cout << "\n\n\n\n\t\tFeito por: Judson Silva.\n\n\n\n";
	
	int length = countApps( installedApps );

	if( length == 0 ) return;
	
	ofstream installedAppsFile(INSTALLED_APPS_FILE, ofstream::out | ofstream::trunc);

	for(int i = 0; i < length; i++){
		installedAppsFile << installedApps[i].name << "|";
		installedAppsFile << installedApps[i].size;
		if( i != length - 1)
			installedAppsFile << "\n";
	}
	
}