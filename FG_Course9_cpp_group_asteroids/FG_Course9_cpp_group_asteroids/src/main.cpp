#include "Application.h"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	Window* myWindow = Window::getInstance();

	if (myWindow->wasSetUpSuccessfully())
	{
		srand((unsigned int)time(NULL));
		Application* myApp = Application::getInstace(myWindow);
		myApp->run();
		delete myApp;
	}

	delete myWindow;

	return 0;
}