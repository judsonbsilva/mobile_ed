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

void initStore(){

	setInterfaceTitle("   STORE  ", "Selecione um para instalar");

	int length = countApps(storeApps),
		homeAppsLength = countApps(homeApps);

	int i = 1;
	for(int from = storeApps.il; from <= storeApps.fl; from++, i++ )
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

		//cout << "\nIL: " <<  storeApps.il << " I: "<< input << "\n"; 
		//cout << storeApps.list[input].name << "\n";
		
		if( hasApp(storeApps.list[input], installedApps) > -1 ){
			cout << "   " << storeApps.list[input].name << " já instalado.\n";
			sleep(1000);
			initStore();
		} else {
			cout << "   " << storeApps.list[input].name << " instalado com sucesso.\n";
			insertIn(storeApps.list[input], &installedApps);
				
			if( homeAppsLength < 10 )
				insertIn(storeApps.list[input], &homeApps);
			
			sleep(1000);
			initHome();
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
	cout << "-------------------------------\n    Área de Trabalho\n-------------------------------\n";

	int homeLength = countApps(homeApps);

	if( homeLength > 0 ){
		
		int counter = 0;
		for(int i = homeApps.il; i <= homeApps.fl; i++){
			if( homeApps.list[i].name != "" ){
				cout << setStringSize( homeApps.list[i].name,15) << "   ";
				counter++;
				if( counter == 3 ){
					cout << "\n";
					counter = 0;
				}
			}
		}

		cout << "\n";
	}

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
	else if( input < 3 && input > homeLength )
		initHome();
	else {

		input += homeApps.il + 3;	
		
		if( hasApp(homeApps.list[ input ], runningApps) > -1 ){
			cout << "   " << (homeApps.list[input].name) << " já está sendo executado.\n";
			sleep(1000);
			initHome();
		} else {
			cout << "   " << (homeApps.list[input].name) << " rodando.\n";
			insertIn(homeApps.list[input], &runningApps);
			sleep(1000);
			initHome();
		}

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

	setInterfaceTitle(" MEUS APPS", "Selecione um app para rodar (para apagar '-' + número do app)");

	for(int i = 1, from = installedApps.il; from <= installedApps.fl; from++, i++ )
		setItemList(i, installedApps.list[from].name);

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
		
		input += installedApps.il - 1;
		
		if( !uninstall && hasApp(installedApps.list[input], runningApps) > -1 ){
			cout << "   " << (installedApps.list[input].name) << " já está sendo executado.\n";
			sleep(1000);
			initMyApps();
		} else if( !uninstall ){
			cout << "   " << (installedApps.list[input].name) << " rodando.\n";
			insertIn(installedApps.list[input], &runningApps);
			sleep(1000);
			initHome();
		}
		
		if( uninstall ){
			
			int appRunning = hasApp(installedApps.list[input], runningApps),
				homeApp = hasApp(installedApps.list[input], homeApps);
			
			char response;
		
			if( appRunning > -1 ){
				cout << "   " << installedApps.list[input].name << " Está executando. Desenha mesmo excluir? (S/N)";
				cin >> response;
			}

			if( appRunning == -1 || response == 's' || response == 'S' ){

				cout << "   " << (installedApps.list[input].name) << " apagado.\n";
				
				removeOf(input, &installedApps);
				
				if( appRunning > -1 ){
					cout << "HEEEEREE!222222222";
					removeOf(appRunning, &runningApps);
				}
				
				if( homeApp > -1 ){
					cout << "HEEEEREE!";
					removeOf(homeApp, &homeApps);
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
	
	for(int i = 1, from = runningApps.il; from <= runningApps.fl; from++, i++ )
		setItemList(i, runningApps.list[from].name);

	cout << "\n   0. Voltar\n";
	
	int input;
	cin >> input;

	hasError();

	if( input == 0 ){
		initHome();
	} else if( input < 0 || input > length ){
		initRunning();
	} else {

		input += runningApps.il - 1;

		cout << runningApps.list[input].name << " fechado.\n";
		
		sleep(1000);
		removeOf( input, &runningApps );
		initHome();
	}
}

void closeApp(){
	
	clearScreen;
	cout << "\n\n\n\n\t\tFeito por: Judson Silva.\n\n\n\n";
	cout << "Quantidade de movimentações feitas: " << moveLength;

	int length = countApps( installedApps );

	if( length == 0 ) return;
	
	ofstream installedAppsFile(INSTALLED_APPS_FILE, ofstream::out | ofstream::trunc);

	for(int i = installedApps.il; i <= installedApps.fl; i++){
		installedAppsFile << installedApps.list[i].name << "|";
		installedAppsFile << installedApps.list[i].size;
		installedAppsFile << "\n";
	}
	
}