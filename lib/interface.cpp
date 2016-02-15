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

string setStringSize( string txt, int size ){
	txt = txt.substr(0, size);
	int toAdd = size - txt.length(); 
	if( toAdd > 0 ){
		for(int i = 0; i <= toAdd; i++)
			txt += " ";
	}

	return txt;
}

void hasError(){
	if( cin.fail() ){
		cout << "    Erro, caractere inválido!!!\n";
		return;
	}
}

void installApps(){
	if( appsToInstall.length > 0 ){
		app theApp = FILAremoveOf( &appsToInstall );
		if( LLDEhasApp( theApp, installedApps ) == -1 ){
			sleep(500);
			LLDEinsertIn( theApp, &installedApps);	
			if( LLSEcountApps( homeApps ) < 10 )
				LLSEinsertIn( theApp, &homeApps);

			cout << "   " << theApp.name << " Instalado com sucesso. \n";
			sleep(1000);
			installApps();
		}
	}
}

void runApp( app theApp ){
	cout << "   " << theApp.name << " rodando.\n";
	LLDEinsertIn( theApp, &runningApps);
	PIinsertIn( theApp, &history );
	sleep(1000);
}

void initStore(){

	setInterfaceTitle("   STORE  ", "Selecione um para instalar");

	int length = LLVcountApps(storeApps),
		homeAppsLength = LLSEcountApps(homeApps);

	for(int i = 1, from = storeApps.il; from <= storeApps.fl; from++, i++ )
		setItemList(i, storeApps.list[from].name);

	cout << "\n";
	setItemList(0, "Voltar\n");

	int input;
	cin >> input;

	hasError();

	if( input == 0 ){	
		initHome();
	} else if( input < 0 || input > length ){
		initStore();
	} else {
		input += storeApps.il - 1;

		if( FILAhasApp( storeApps.list[input], appsToInstall ) > -1 ){
			cout << "   " << storeApps.list[input].name << " já na fila de instalação.\n";
			sleep(1000);
			initStore();
		} else if( LLDEhasApp(storeApps.list[input], installedApps) > -1 ){
			cout << "   " << storeApps.list[input].name << " já instalado.\n";
			sleep(1000);
			initStore();
		} else {
			cout << "   Preparando para instalar " << storeApps.list[input].name << "\n";
			FILAinsertIn( storeApps.list[input], &appsToInstall );
			sleep(1000);
			initStore();
		}
	}
}

void initHistory(){
	
	setInterfaceTitle("HISTÓRICO", "Ultimos app rodados");

	if( history.length == 0 ){
		cout << "    Histórico vazio\n";
		sleep(1000);
		initHome();
	} else {
		
		for(int i = 0; i < history.length; i++){
			setItemList(i + 1, PIgetApp(i, history).name );
		}
		cout << "\n\n\n";
		setItemList(0, "Voltar");
		setItemList(-1, "Apagar histórico");

		int input;

		cin >> input;

		hasError();

		if( input == 0 ){
			initHome();
		} else if( input == -1 ){
			while( history.length > 0 ){
				PIremoveOf(&history);
			}
			cout << "    Histórico apagado com sucesso.\n";
			sleep(1000);
			initHome();
		} else initHistory();
		

	}
}

// Show screen
void initHome(){
	
	setInterfaceTitle("  INÍCIO  ", "Selecione um item do menu");

	setItemList(1, "Store");
	setItemList(2, "Meus Apps");
	setItemList(3, "Executando");
	setItemList(4, "Histórico");
	
	cout << "\n";
	setItemList(0, "Voltar\n");
	cout << "-------------------------------\n    Área de Trabalho\n-------------------------------\n";

	int homeLength = LLSEcountApps(homeApps);
	
	if( homeLength > 0 ){
		
		for(int i = homeApps.init, counter = 0; i != -1; i = homeApps.list[i].next){
			cout << "|" << setw(3) << counter + 5 << " | ";
			cout << setw(10) << homeApps.list[i].content.name << " ";
			counter++;
			if( counter % 3 == 0 ){
				cout << "\n";
			}
		}

		cout << "\n\n";
	}

	installApps();

	int input;

	cin >> input;

	hasError();

	if( input == 0 )
		closeApp();
	else if( input == 1 )
		initStore();
	else if( input == 2 )
		initMyApps();
	else if( input == 3 )
		initRunning();
	else if( input == 4 )
		initHistory();
	else if( input < 0 && input > homeLength )
		initHome();
	else {
		input = LLSEgetTheIndex(input - 4, homeApps);

		if( LLDEhasApp(homeApps.list[ input ].content, runningApps) > -1 ){
			cout << "   " << (homeApps.list[input].content.name) << " já está sendo executado.\n";
			sleep(1000);
			initHome();
		} else {
			runApp( homeApps.list[ input ].content );
			initHome();
		}
	}
	
}

void initMyApps(){

	setInterfaceTitle(" MEUS APPS","");
	
	int length = LLDEcountApps(installedApps);

	if( length == 0 ){
		cout << "  Você não possui apps instalados.\n\n";
		sleep(2000);
		initHome();
		return;
	}

	setInterfaceTitle(" MEUS APPS", "Selecione um app para rodar (para apagar '-' + número do app)");

	for(int i = 1, from = installedApps.init; from != -1; from = installedApps.list[from].next, i++ )
		setItemList(i, installedApps.list[from].content.name);

	cout << "\n   0. Voltar\n";
	
	int input;
	cin >> input;

	hasError();

	if( input == 0 ){
		initHome();
	} else if( input < -length || input > length ){
		initMyApps();
	} else {
		
		bool uninstall = false;
		
		if( input < 0 ){
			input *= -1;
			uninstall = true;
		}
		
		input = LLDEgetTheIndex(input, installedApps);
		
		if( !uninstall && LLDEhasApp(installedApps.list[input].content, runningApps) > -1 ){
			cout << "   " << (installedApps.list[input].content.name) << " já está sendo executado.\n";
			sleep(1000);
			initMyApps();
		} else if( !uninstall ){
			runApp(installedApps.list[input].content);
			initMyApps();
		}
		
		if( uninstall ){
			
			int appRunning = LLDEhasApp(installedApps.list[input].content, runningApps),
				homeApp = LLSEhasApp(installedApps.list[input].content, homeApps);
			
			char response;
		
			if( appRunning > -1 ){
				cout << "   " << installedApps.list[input].content.name << " Está executando. Desenha mesmo excluir? (S/N)";
				cin >> response;
			}

			if( appRunning == -1 || response == 's' || response == 'S' ){

				cout << "   " << (installedApps.list[input].content.name) << " apagado.\n";
				
				LLDEremoveOf(input, &installedApps);
				
				if( appRunning > -1 )
					LLDEremoveOf(appRunning, &runningApps);
				
				if( homeApp > -1 )
					LLSEremoveOf(homeApp, &homeApps);
			
				sleep(1000);
			
			}
			initMyApps();
		}

	}

}

void initRunning(){
	
	setInterfaceTitle("  RODANDO ","");
	
	int length = LLDEcountApps(runningApps);

	if( length == 0 ){
		cout << "  Você não possui apps rodando.\n\n";
		sleep(2000);
		initHome();
		return;
	}

	setInterfaceTitle("  RODANDO ","Selecione para fechar");
	
	for(int i = 1, from = runningApps.init; from != -1; from = runningApps.list[from].next, i++ )
		setItemList(i, runningApps.list[from].content.name);

	cout << "\n   0. Voltar\n";
	
	int input;
	cin >> input;

	hasError();

	if( input == 0 ){
		initHome();
	} else if( input < 0 || input > length ){
		initRunning();
	} else {

		input = LLDEgetTheIndex(input, runningApps);

		cout << runningApps.list[input].content.name << " fechado.\n";
		
		sleep(1000);
		LLDEremoveOf( input, &runningApps );
		initRunning();
	}
}

void closeApp(){
	
	clearScreen;
	cout << "\n\n\n\n\t\tFeito por: Judson Silva.\n\n\n\n";
	
	int length = LLDEcountApps( installedApps );

	if( length == 0 ) return;
	
	ofstream installedAppsFile(INSTALLED_APPS_FILE, ofstream::out | ofstream::trunc);

	for(int i = installedApps.init; i != -1; i = installedApps.list[i].next){
		installedAppsFile << installedApps.list[i].content.name << "|";
		installedAppsFile << installedApps.list[i].content.size;
		installedAppsFile << "\n";
	}
	
}