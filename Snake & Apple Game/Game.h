#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
using namespace sf;

class Game
{
private:
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;

	Vertex** lines;				//grid
	CircleShape apple;			//apple
	RectangleShape snake[100];	//snake
	RectangleShape obj;			//to type words
	int snakelen;				//length of snake
	int keyPressed;				// 1: Up, 2: Down, 3: Left, 4: Right
	int killFlag;				//flag to indicate game ended
	int AppleEatFlag;			//indicates whether apple is eaten or not
	int highScore;				//stores the highest score
	int score;					//counts the score of the player; eating each apple earns 10 pts

	Font font;
	Text Start, LMAO_Noob, Score, HighScore, ScoreNum, HighScoreNum;

	void initVariables();
	void initWindow();
	void createApple();
	void createGrid();
	void createSnake();
	void updateSnake();
	void updateKeyPressed();
	void RandomAppleGenerator();
	void createTexts();
	void renderTexts();
	sf::String intToString(int num);

public:
	Game();
	virtual ~Game();

	const bool running();
	void pollEvent();

	void update();
	void render();
};
