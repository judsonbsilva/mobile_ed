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

// Global vars
app storeApps[APP_AMOUNT];
app installedApps[APP_AMOUNT];
app runningApps[APP_AMOUNT];

// Moviments length
int moveLength = 0;