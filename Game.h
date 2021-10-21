#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>

//------------------------------------------------------------------------------------------
// Class act like game engine
//------------------------------------------------------------------------------------------
class Game
{
private:
	// Variable Window
	//------------------------------------------------------------------------------------------
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	// Mouse position
	//------------------------------------------------------------------------------------------
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resource
	//------------------------------------------------------------------------------------------
	sf::Font font;

	// Text
	//------------------------------------------------------------------------------------------
	sf::Text uiText;

	// Game logic
	//------------------------------------------------------------------------------------------
	bool endGame;
	unsigned point;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimeMax;
	int maxEnemies;
	bool mouseHeld;

	// Game objects
	//------------------------------------------------------------------------------------------
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

	// Private function
	//--------------------------------------------------------------------------------------
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();

public:
	// Construtors / Destructor
	//--------------------------------------------------------------------------------------
	Game();
	virtual	~Game();

	// Accessor
	//--------------------------------------------------------------------------------------
	const bool running() const;
	const bool getEndGame() const;

	// Function
	//--------------------------------------------------------------------------------------
	void spawnEnemy();
	void pollEvent();
	void updateMousePosition();
	void updateText();
	void updateEnemies();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};