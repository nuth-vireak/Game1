#include "Game.h"

// Private Function
//--------------------------------------------------------------------------------------
void Game::initVariables()
{
	this->window = nullptr;

	// Game logic
	this->endGame = false;
	this->point = 0;
	this->health = 10;
	this->enemySpawnTimeMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimeMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Game 01", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (this->font.loadFromFile("Fonts/000webfont Regular.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << 'n';
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(32);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
}

// Construtors / Destructor
//--------------------------------------------------------------------------------------
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

// Accessor
//--------------------------------------------------------------------------------------
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

// Public function
//--------------------------------------------------------------------------------------

void Game::spawnEnemy()
{
	/*
		@ return void

		Spawns enemies and set their type and color. Spawn them at random postion
		-Set random type (diff);
		-Set a random positions;
		-Set a random colors;
		-Add enemy to vector.
		-Remove enemies at the end of the screen //TODO
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	// Randomize enemy type
	int type = rand() % 5;
	switch (type)
	{
	case 0:
		this->enemy.setSize(sf::Vector2f(10.f, 10.f));
		this->enemy.setFillColor(sf::Color::Magenta);
		break;
	case 1:
		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
		this->enemy.setFillColor(sf::Color::Blue);
		break;
	case 2:
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::Cyan);
		break;
	case 3:
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		this->enemy.setFillColor(sf::Color::Red);
		break;
	case 4:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Green);
		break;
	default:
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Yellow);
		break;
	}

	//Spawn the enemy
	this->enemies.push_back(enemy);
}

void Game::pollEvent()
{
	// Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed():
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePosition()
{
	/**
		@ return void

		Update the mouse position:
		- Mouse position relative to window (Vector2i)
	*/
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Point: " << this->point << '\n'
		<< "Health: " << this->health << '\n';

	this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
	/*
		@ return void

		Update the enemy spawn timer and spawn enemies
		when the total amount of enemies is smaller than maximum.
		Move the enemies downwards.
		Remove the enemies at the edge of the screen.
	*/

	// Update the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimeMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	// Moving and updating enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 2.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << health << '\n';
		}
	}

	// Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					// Gain point
					if (this->enemies[i].getFillColor() == sf::Color::Magenta)
					{
						this->point += 10;
						this->health += 20;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->point += 7;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->point += 5;
					else if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->point += 3;
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->point += 1;
					std::cout << "Point: " << point << '\n';

					// Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::update()
{
	this->pollEvent();

	if (this->endGame == false)
	{
		this->updateMousePosition();
		this->updateText();
		this->updateEnemies();
	}

	// End game condition
	if (this->health <= 0)
	{
		this->endGame = true;
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::render()
{
	this->window->clear();

	// Draw game objects
	this->renderEnemies(*this->window);
	this->renderText(*this->window);
	this->window->display();
}