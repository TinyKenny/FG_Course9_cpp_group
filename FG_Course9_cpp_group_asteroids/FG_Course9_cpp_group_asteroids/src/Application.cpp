#include "Application.h"

#include "InputHandler.h"
#include "PhysicsSystem.h"

#include <chrono>
#include <iostream>
#include <string>

//#include<SDL_ttf.h>



Application::Application(Window* window)
	: player(this),
	dt(1.0 / 60.0),
	highScore(0)
{
	myWindow = window;
	renderer = window->getRenderer();
	font = window->getFont();

	// TODO load highscore from file
	// TODO refactor and possibly improve
	currentScoreSrcRect = { 0, 0, 0, 0 };
	currentScoreDstRect = { 0, 0, 0, 0 };
	resetCurrentScore();
	
	SDL_Surface* firstLineSurf = TTF_RenderText_Blended(font, "You got hit by an asteroid, game over!", { 255, 255, 255 });
	SDL_Surface* secondLineSurf = TTF_RenderText_Blended(font, "Press enter to play again or press escape to exit", { 255, 255, 255 });

	int width = firstLineSurf->w;
	if (width < secondLineSurf->w)
	{
		width = secondLineSurf->w;
	}
	int height = firstLineSurf->h + secondLineSurf->h;

	SDL_Surface* textSurf = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

	{
		SDL_Rect firstLineSrcRect;
		firstLineSrcRect.w = firstLineSurf->w;
		firstLineSrcRect.h = firstLineSurf->h;
		firstLineSrcRect.x = 0;
		firstLineSrcRect.y = 0;

		SDL_Rect firstLineDstRect;
		firstLineDstRect.w = firstLineSurf->w;
		firstLineDstRect.h = firstLineSurf->h;
		firstLineDstRect.x = (width - firstLineSurf->w) / 2;
		firstLineDstRect.y = 0;

		SDL_BlitSurface(firstLineSurf, &firstLineSrcRect, textSurf, &firstLineDstRect);
	}

	{
		SDL_Rect secondLineSrcRect;
		secondLineSrcRect.w = secondLineSurf->w;
		secondLineSrcRect.h = secondLineSurf->h;
		secondLineSrcRect.x = 0;
		secondLineSrcRect.y = 0;

		SDL_Rect secondLineDstRect;
		secondLineDstRect.w = secondLineSurf->w;
		secondLineDstRect.h = secondLineSurf->h;
		secondLineDstRect.x = (width - secondLineSurf->w) / 2;
		secondLineDstRect.y = firstLineSurf->h;

		SDL_BlitSurface(secondLineSurf, &secondLineSrcRect, textSurf, &secondLineDstRect);
	}

	gameOverMessageTexture = SDL_CreateTextureFromSurface(renderer, textSurf);

	gameOverMessageSrcRect.w = textSurf->w;
	gameOverMessageSrcRect.h = textSurf->h;
	gameOverMessageSrcRect.x = 0;
	gameOverMessageSrcRect.y = 0;

	gameOverMessageDstRect.w = gameOverMessageSrcRect.w;
	gameOverMessageDstRect.h = gameOverMessageSrcRect.h;
	gameOverMessageDstRect.x = (WINDOW_WIDTH - gameOverMessageDstRect.w) / 2;
	gameOverMessageDstRect.y = (WINDOW_HEIGHT - gameOverMessageDstRect.h) / 2;

	int fontHeight = TTF_FontHeight(font);
	paddingBetweenGameOverMessageAndScore = fontHeight * 0.5;

	gameOverMessageDstRect.y -= fontHeight + paddingBetweenGameOverMessageAndScore; // offset one line + padding
	
	
	SDL_FreeSurface(textSurf);
	SDL_FreeSurface(secondLineSurf);
	SDL_FreeSurface(firstLineSurf);
}

Application::~Application()
{
	SDL_DestroyTexture(gameOverMessageTexture);
}

Application* Application::getInstace(Window* window)
{
	if (window == nullptr)
	{
		std::cout << "instantiation of application with nullptr window attempted, returning nullptr" << std::endl;
		return nullptr;
	}
	return new Application(window);
}

void Application::run()
{
	if (!keepApplicationAlive)
	{
		keepApplicationAlive = true;

		while (keepApplicationAlive)
		{
			// cyclical statemachine
			gameplayState();

			gameOverState(); // can set keepApplicationAlive to false, depending on player input
		}
	}
}

void Application::quit()
{
	keepApplicationAlive = false;
	keepGameLoopAlive = false;
}

void Application::gameOver()
{
	keepGameLoopAlive = false;
}

void Application::spawnBullet(Vector2 direction, Vector2 startPosition)
{
	PlayerBullet bullet(direction, startPosition);
	playerBullets.push_back(bullet);
}

void Application::DestroyAsteroid(Asteroid* asteroid)
{
	for (size_t i = 0; i < asteroids.size(); i++)
	{
		if (&asteroids[i] == asteroid)
		{
			increaseCurrentScore();
			asteroids.erase(asteroids.begin() + i);
		}
	}

	if (asteroids.size() == 0)
	{
		spawnAsteroids();
	}
}

void Application::gameplayState()
{
	if (keepGameLoopAlive)
	{
		return;
	}

	keepGameLoopAlive = true;

	using namespace std::chrono;

	double t = 0.0; // time since start
	//dt = 1.0 / 60.0; // desired update rate
	double accumulator = 0.0;
	steady_clock::time_point currentTime = steady_clock::now();
	
	resetCurrentScore();
	player.reset();
	spawnAsteroids();

	while (keepGameLoopAlive)
	{
		steady_clock::time_point newTime = steady_clock::now();
		double frameTime = (duration_cast<duration<double>>(newTime - currentTime)).count();
		currentTime = newTime;
		accumulator += frameTime;


		while (accumulator >= dt)
		{
			InputHandler::updateInputs(this);

			player.update(dt);
			updateBullets();

			PhysicsSystem::physicsUpdate(this, dt, asteroids, playerBullets, player);

			accumulator -= dt;
			t += dt;
		}

		renderScene();
	}

	asteroids.clear();
	playerBullets.clear();
}

const void Application::renderScene()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (Asteroid& asteroid : asteroids)
	{
		asteroid.draw(renderer);
	}

	for (PlayerBullet& bullet : playerBullets)
	{
		bullet.draw(renderer);
	}
	
	player.draw(renderer);

	SDL_RenderCopy(renderer, currentScoreTexture, &currentScoreSrcRect, &currentScoreDstRect);

	SDL_RenderPresent(renderer);
}

void Application::spawnAsteroids()
{
	asteroids.push_back(Asteroid());
	asteroids.push_back(Asteroid());
	asteroids.push_back(Asteroid());
	asteroids.push_back(Asteroid());
}

void Application::updateBullets()
{
	for (size_t i = 0; i < playerBullets.size(); i++)
	{
		bool isAlive = playerBullets[i].updateLifetime(dt);

		if (!isAlive)
		{
			playerBullets.erase(playerBullets.begin()+i);
			i--;
		}
	}
}

void Application::increaseCurrentScore()
{
	currentScore++;
	rasterizeCurrentScoreText();
}

void Application::resetCurrentScore()
{
	currentScore = 0;
	rasterizeCurrentScoreText();
}

void Application::rasterizeCurrentScoreText()
{
	if (currentScoreTexture != nullptr)
	{
		SDL_DestroyTexture(currentScoreTexture);
	}

	std::string tempString = "Your score: ";
	tempString += std::to_string(currentScore);

	SDL_Surface* currentScoreSurf = TTF_RenderText_Blended(font, tempString.c_str(), { 255, 255, 255 });
	currentScoreTexture = SDL_CreateTextureFromSurface(renderer, currentScoreSurf);
	currentScoreSrcRect.w = currentScoreSurf->w;
	currentScoreSrcRect.h = currentScoreSurf->h;

	currentScoreDstRect.w = currentScoreSrcRect.w;
	currentScoreDstRect.h = currentScoreSrcRect.h;

	SDL_FreeSurface(currentScoreSurf);
}

void Application::gameOverState()
{
	if (!keepApplicationAlive)
	{
		return;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, gameOverMessageTexture, &gameOverMessageSrcRect, &gameOverMessageDstRect);


	SDL_Rect currentScoreGameOverDstRect = {
		(WINDOW_WIDTH - currentScoreDstRect.w) / 2,
		gameOverMessageDstRect.y + gameOverMessageDstRect.h + paddingBetweenGameOverMessageAndScore,
		currentScoreDstRect.w,
		currentScoreDstRect.h
	};
	
	SDL_RenderCopy(renderer, currentScoreTexture, &currentScoreSrcRect, &currentScoreGameOverDstRect);


	// TODO save highscore to file, refactor
	std::string highScoreString;
	if (currentScore > highScore)
	{
		highScoreString += "Previous highscore: ";
	}
	else
	{
		highScoreString += "Highscore: ";
	}
	highScoreString += std::to_string(highScore);

	SDL_Surface* highScoreSurf = TTF_RenderText_Blended(font, highScoreString.c_str(), { 255, 255, 255 });
	SDL_Texture* highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurf);

	SDL_Rect highScoreSrcRect;
	highScoreSrcRect.w = highScoreSurf->w;
	highScoreSrcRect.h = highScoreSurf->h;
	highScoreSrcRect.x = 0;
	highScoreSrcRect.y = 0;

	SDL_Rect highScoreDstRect;
	highScoreDstRect.w = highScoreSurf->w;
	highScoreDstRect.h = highScoreSurf->h;
	highScoreDstRect.x = (WINDOW_WIDTH - highScoreDstRect.w) / 2;
	highScoreDstRect.y = currentScoreGameOverDstRect.y + currentScoreGameOverDstRect.h;

	SDL_RenderCopy(renderer, highScoreTexture, &highScoreSrcRect, &highScoreDstRect);

	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(highScoreTexture);
	SDL_FreeSurface(highScoreSurf);

	highScore = std::max(currentScore, highScore);

	while (keepApplicationAlive)
	{
		InputHandler::updateInputs(this);

		if (InputHandler::getKeyDown(SDLK_RETURN) || InputHandler::getKeyDown(SDLK_KP_ENTER))
		{
			return;
		}
		else if (InputHandler::getKeyDown(SDLK_ESCAPE))
		{
			keepApplicationAlive = false;
		}
	}
}