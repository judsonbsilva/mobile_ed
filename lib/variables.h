// Files
#define STORE_FILE "data/store.txt"
#define INSTALLED_APPS_FILE "data/installed.txt"
#define CONTEXT_FILE "data/context.txt"

// Max amount apps
#define APP_AMOUNT 100

// If is linux
#ifdef __linux__
	
	#define clearScreen cout << "\033c"
	#include <chrono>
	#include <thread>
	
	void sleep( int milliseconds ){
		std::this_thread::sleep_for(
			std::chrono::milliseconds( milliseconds )
		);
	}

// If is Windows
#elif _WIN32
	#include <conio.h>
	#define clearScreen system("cls")
#endif

// Define app struct
struct app {
	string name;
	int size;
};
