#include "Engine/Engine.h"

int main(int argcount, char** args) {	
	lucy::Engine engine;
	
	engine.Init();
	engine.Mainloop();

	return 0;
}