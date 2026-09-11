#include "Game.h"

#define boxSize 40		//sets the size of the standard box the screen is split into by me

//Game constructor
Game::Game()
{
	std::srand(static_cast<unsigned int>(time(0)));			//initialises the rand()

	this->initVariables();
	this->initWindow();
	this->createApple();
	this->createGrid();
	this->createSnake();

	font.loadFromFile("Font/Times\ New\ Roman/TimesNewRoman.ttf");
	createTexts();
}

//Game destructor
Game::~Game()
{
	delete window;

	for (int i = 0; i < (videoMode.height + videoMode.width) / boxSize - 2; i++) {
		delete lines[i];
	}
	delete lines;
}

//creates the template of the apple
void Game::createApple()
{
	apple.setRadius(boxSize/2);
	apple.setFillColor(Color::Red);
	apple.setOutlineThickness(1.0f);
	apple.setOutlineColor(Color::Black);
}

//creates the grid of the boxes. only to help me create the game
void Game::createGrid()
{
	int m = videoMode.width / boxSize - 1, n = videoMode.height / boxSize - 1;

	lines = new Vertex * [m + n];
	for (int i = 0; i < m; i++) {
		lines[i] = new Vertex[2];
		lines[i][0] = Vertex(Vector2f(boxSize * (i + 1), 0), Color::Black);
		lines[i][1] = Vertex(Vector2f(boxSize * (i + 1), videoMode.height), Color::Black);
	}
	for (int i = 0; i < n; i++) {
		lines[m + i] = new Vertex[2];
		lines[m + i][0] = Vertex(Vector2f(0, boxSize * (i + 1)), Color::Black);
		lines[m + i][1] = Vertex(Vector2f(videoMode.width, boxSize * (i + 1)), Color::Black);
	}
	
}

void Game::initVariables()
{
	//initialising the window pointer
	this->window = nullptr;
	snakelen = 0;
	keyPressed = 0;
	killFlag = 0;
	AppleEatFlag = 1;
	score = 0;
	highScore = 0;
}

void Game::initWindow()
{
	// videoMode to define size of the window
	videoMode.height = 800;
	videoMode.width = 1200;

	//creating the window
	window = new RenderWindow(this->videoMode, "My Game", Style::Default);
	window->setFramerateLimit(15);
}

//checks whether window is open or not
const bool Game::running()
{
	return this->window->isOpen();
}

//pollEvent to close the window
//game closes when --- 1. Esc key is pressed	2. Close window button is pressed
void Game::pollEvent()
{
	while (this->window->pollEvent(this->ev)) {
		if (this->ev.type == Event::Closed) {
			this->window->close();
		}
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window->close();
	}

	return;
}

//updates each frame of the game
void Game::update()
{
	pollEvent();

	if (killFlag == 1) {
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			createSnake();
			killFlag = 0;
			keyPressed = 0;
		}
		else {
			return;
		}
	}


	if (AppleEatFlag == 1) {
		RandomAppleGenerator();
		AppleEatFlag = 0;
	}

	updateKeyPressed();
	updateSnake();
}

//renders each frame of the game
void Game::render()
{
	window->clear(Color::White);

	//to draw the apple
	if (AppleEatFlag == 0 && keyPressed != 0) {
		window->draw(apple);
	}

	/*
	//create grid
	for (int i = 0; i < videoMode.width / boxSize + videoMode.height / boxSize - 2; i++) {
		window->draw(lines[i], 2, Lines);
	}
	*/

	//create snake
	for (int i = 0; i < snakelen; i++) {
		window->draw(snake[i]);
	}

	//display texts
	renderTexts();

	window->display();
}

//to create the snake initially
void Game::createSnake()
{
	snakelen = 4;
	for (int i = 0; i < snakelen; i++) {
		snake[i].setSize(Vector2f(boxSize, boxSize));
		snake[i].setFillColor(Color::Blue);
		snake[i].setPosition(videoMode.width / 2 + boxSize * i, videoMode.height / 2);
	}
	snake[0].setFillColor(Color::Green);
}

//to move, grow or kill the snake
void Game::updateSnake()
{
	if (keyPressed == 0) {
		return;
	}

	//updates the position of the snake blocks except the head
	for (int i = snakelen - 1; i > 0; i--) {
		snake[i].setPosition(snake[i - 1].getPosition());
	}


	//updates the position of the head of the snake
	if (keyPressed == 1) {
		if (snake[0].getPosition().y - boxSize < 0) {
			snake[0].setPosition(snake[0].getPosition().x, videoMode.height-boxSize);
		}
		else {
			snake[0].setPosition(snake[0].getPosition().x, snake[0].getPosition().y - boxSize);
		}
	}
	else if (keyPressed == 2) {
		if (snake[0].getPosition().y + boxSize >= videoMode.height) {
			snake[0].setPosition(snake[0].getPosition().x, 0);
		}
		else {
			snake[0].setPosition(snake[0].getPosition().x, snake[0].getPosition().y + boxSize);
		}
	}
	else if (keyPressed == 3) {
		if (snake[0].getPosition().x - boxSize < 0) {
			snake[0].setPosition(videoMode.width - boxSize, snake[0].getPosition().y);
		}
		else {
			snake[0].setPosition(snake[0].getPosition().x - boxSize, snake[0].getPosition().y);
		}
	}
	else if (keyPressed == 4) {
		if (snake[0].getPosition().x + boxSize >= videoMode.width) {
			snake[0].setPosition(0, snake[0].getPosition().y);
		}
		else {
			snake[0].setPosition(snake[0].getPosition().x + boxSize, snake[0].getPosition().y);
		}
	}

	//snake grows after eating apple
	if (apple.getPosition() == snake[0].getPosition()) {
		score += 10;

		snake[snakelen].setSize(Vector2f(boxSize, boxSize));
		snake[snakelen].setFillColor(Color::Blue);
		if (snake[snakelen - 2].getPosition().x < snake[snakelen - 1].getPosition().x || snake[snakelen - 2].getPosition().x - snake[snakelen - 1].getPosition().x > 2*boxSize)
		{
			snake[snakelen].setPosition(snake[snakelen - 1].getPosition().x + boxSize, snake[snakelen - 1].getPosition().y);
		}
		else if (snake[snakelen - 2].getPosition().x > snake[snakelen - 1].getPosition().x || snake[snakelen - 1].getPosition().x - snake[snakelen - 2].getPosition().x > 2 * boxSize)
		{
			snake[snakelen].setPosition(snake[snakelen - 1].getPosition().x - boxSize, snake[snakelen - 1].getPosition().y);
		}
		else if (snake[snakelen - 2].getPosition().y > snake[snakelen - 1].getPosition().y || snake[snakelen - 1].getPosition().y - snake[snakelen - 2].getPosition().y > 2 * boxSize)
		{
			snake[snakelen].setPosition(snake[snakelen - 1].getPosition().x, snake[snakelen - 1].getPosition().y + boxSize);
		}
		else {
			snake[snakelen].setPosition(snake[snakelen - 1].getPosition().x, snake[snakelen - 1].getPosition().y - boxSize);
		}

		snakelen++;
		AppleEatFlag = 1;
	}

	//snake biting itself to end game
	for (int i = 1; i < snakelen; i++) {
		if (snake[0].getPosition() == snake[i].getPosition()) {
			killFlag = 1;
			return;
		}
	}
}

//to keep the snake moving in one direction even when no key is pressed
void Game::updateKeyPressed()
{
	if (Keyboard::isKeyPressed(Keyboard::Up) && keyPressed != 2) {
		keyPressed = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && keyPressed != 1) {
		keyPressed = 2;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && keyPressed != 4) {
		keyPressed = 3;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && keyPressed != 3) {
		keyPressed = 4;
	}
}

//to generate the apple randomly on the screen
void Game::RandomAppleGenerator()
{
	int x = 0, y = 0;
	
	while (true) {
		x = boxSize*(rand() % (videoMode.width/boxSize));
		y = boxSize*(rand() % (videoMode.height/boxSize));

		int i = 0;
		for (; i < snakelen; i++) {
			if (static_cast<Vector2i>(snake[i].getPosition()) == Vector2i(x, y)) {
				break;
			}
		}

		if (i == snakelen) {
			break;
		}
	}

	apple.setPosition(x, y);
}

//to render texts on the screen
void Game::renderTexts()
{
	if (keyPressed == 0)
		window->draw(Start);

	if (killFlag == 1) {
		window->draw(LMAO_Noob);
		window->draw(Score);
		ScoreNum.setString(intToString(score));
		window->draw(ScoreNum);
	}
}

//to create the text templates to be displayed
void Game::createTexts()
{
	//Start text
	Start.setFont(font);
	Start.setCharacterSize(80);
	Start.setPosition(videoMode.width/2 - boxSize*3, videoMode.height/2 - boxSize*4);
	Start.setFillColor(Color::Black);
	Start.setString("START");

	//LMAO_Nood text at the end
	LMAO_Noob.setFont(font);
	LMAO_Noob.setCharacterSize(100);
	LMAO_Noob.setPosition(videoMode.width / 2 - boxSize * 8, videoMode.height / 2 - boxSize * 4);
	LMAO_Noob.setFillColor(Color::Black);
	LMAO_Noob.setString("LMAO!! NOOB");

	//Score text
	Score.setFont(font);
	Score.setCharacterSize(50);
	Score.setPosition(videoMode.width / 2 - boxSize * 3, videoMode.height / 2 + boxSize * 4);
	Score.setFillColor(Color::Black);
	Score.setString("Score:");

	//Score number template
	ScoreNum.setFont(font);
	ScoreNum.setCharacterSize(50);
	ScoreNum.setPosition(videoMode.width / 2 + boxSize, videoMode.height / 2 + boxSize * 4);
	ScoreNum.setFillColor(Color::Black);
}

sf::String Game::intToString(int num){
	sf::String st = "   0";

	for (int i = 3; num != 0; i--, num = num/10) {
		st[i] = '0' + (num % 10);
	}
	return st;
}
