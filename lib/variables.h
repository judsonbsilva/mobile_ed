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
// Node of llse
struct node {
	// The app
	app content;
	// Next node
	int next;
};

struct llse {
	node list[APP_AMOUNT];
	int init = -1, finish = -1, avaible = 0;
};

//app storeApps[APP_AMOUNT];
//app installedApps[APP_AMOUNT];
//app homeApps[10];
//app runningApps[APP_AMOUNT];


// Moviments length
int moveLength = 0;
