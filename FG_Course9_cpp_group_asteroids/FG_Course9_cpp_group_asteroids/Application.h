#ifndef APPLICATION_H
#define APPLICATION_H

class Application
{
public:
	// public vars here
private:
	bool keepGameLoopAlive = false;
	Application();
public:
	static Application* getInstace();
	void run();
private:
	void runGameLoop();
};

#endif // !APPLICATION_H