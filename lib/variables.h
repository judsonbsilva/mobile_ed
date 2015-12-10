// Files
#define STORE_FILE "data/store.txt"
#define INSTALLED_APPS_FILE "data/installed.txt"
#define CONTEXT_FILE "data/context.txt"

// Max amount apps
#define APP_AMOUNT 100

// Define app struct
struct app {
	string name;
	int size;
};

struct llv {
	app list[APP_AMOUNT];
	int ia = 0, fa = APP_AMOUNT - 1,
		il = -1, fl = -1;
};

// Global vars
llv storeApps;
llv installedApps;
llv homeApps;
llv runningApps;

//app storeApps[APP_AMOUNT];
//app installedApps[APP_AMOUNT];
//app homeApps[10];
//app runningApps[APP_AMOUNT];


// Moviments length
int moveLength = 0;