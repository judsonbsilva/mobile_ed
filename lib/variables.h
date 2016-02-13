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
	int next, previous;
};

struct llde {
	node list[APP_AMOUNT];
	int init = -1, finish = -1, avaible = 0;
};

struct pilha {
	llde list;
};

llde storeApps, installedApps, homeApps, runningApps;

// Moviments length
int moveLength = 0;
