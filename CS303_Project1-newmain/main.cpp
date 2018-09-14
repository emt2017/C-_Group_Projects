#include "UserInterface.h"
#include "Controller.h"

int main() {
	Controller control;
	UserInterface ui(control);
	bool running = true;

	// Continue providing menu and getting input
	// until user selects exit option
	while (running) {
		ui.outputMenu();
		running = ui.getMenuInput();
	}

	cin.get();
	return 0;
}