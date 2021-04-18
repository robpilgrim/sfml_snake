#include </usr/include/SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>
#include <fstream>
int randomx = 0, randomy = 0;
int dir = 0, game = 2, size = 2, score = 0, scoreCheck = 0, lineCheck = 0;
std::string nPrevious_highscore;
bool bMenu = false, bGame = true, bHighscore = false;
bool bGood = true;
int nScreenWidth = 500, nScreenHeight = 550;
using namespace std::chrono_literals;

struct Snake
{
	int x = 100, y = 100;
} snakebody[100];
//Restarting the game
static void RestartGame()
{
	snakebody[0].x = 100;
	snakebody[0].y = 100;
	dir = 0, game = 1, size = 2, score = 0;
	bGood = true;
	nScreenWidth = 500, nScreenHeight = 550;
	randomx = 1 + rand() % 450;
	randomy = 1 + rand() % 450;
	for (int i = 0; i < 9; i++)
	{
		if (randomx <= (i + 1) * 50 && randomx > i * 50)
			randomx = (i + 1) * 50;
		if (randomy <= (i + 1) * 50 && randomy > i * 50)
			randomy = (i + 1) * 50;
	}
}

int main()
{
	sf::RenderWindow screen(sf::VideoMode(nScreenWidth, nScreenHeight), "Snake");

	sf::Texture Snakesprite, foodsprite, tailsprite;
	Snakesprite.loadFromFile("../content/orange.png");
	foodsprite.loadFromFile("../content/food.png");
	tailsprite.loadFromFile("../content/orangeb.png");
	sf::Sprite Snake, Food, tail;
	Snake.setTexture(Snakesprite);
	Food.setTexture(foodsprite);
	tail.setTexture(tailsprite);
	for (int i = 0; i < size; i++)
	{
		Snake.setPosition(snakebody[i].x, snakebody[i].y);
	}
	sf::Font font;
	font.loadFromFile("../content/manaspc.ttf");
	sf::Text text, gameOverScore, restart, Play, Highscore, leave;
	sf::RectangleShape bottom_line(sf::Vector2f(500, 2));
	bottom_line.setFillColor(sf::Color::White);
	bottom_line.setPosition(0, 500);
	gameOverScore.setFont(font);
	restart.setFont(font);
	gameOverScore.setFillColor(sf::Color::White);
	text.setFont(font);
	Play.setFont(font);
	Highscore.setFont(font);
	leave.setFont(font);
	text.setFillColor(sf::Color::White);

	srand(time(NULL));
	randomx = 1 + rand() % 450;
	randomy = 1 + rand() % 450;
	for (int i = 0; i < 9; i++)
	{
		if (randomx <= (i + 1) * 50 && randomx > i * 50)
			randomx = (i + 1) * 50;
		if (randomy <= (i + 1) * 50 && randomy > i * 50)
			randomy = (i + 1) * 50;
	}
	Food.setPosition(randomx, randomy);
	if (bGame)
	{
		while (screen.isOpen())
		{
			sf::Event event;
			while (screen.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					screen.close();

				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::R)
					{
						RestartGame();
					}
					if (event.key.code == sf::Keyboard::Escape)
					{
						game = 2;
					}
					if (dir != 4 && (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left))
					{
						Snakesprite.loadFromFile("../content/orangeleft.png");
						dir = 1;
					}
					else if (dir != 1 && (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right))
					{

						Snakesprite.loadFromFile("../content/orange.png");
						dir = 4;
					}
					else if (dir != 3 && (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up))
					{
						Snakesprite.loadFromFile("../content/orangeup.png");
						dir = 2;
					}
					else if (dir != 2 && (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down))
					{
						Snakesprite.loadFromFile("../content/orangedown.png");
						dir = 3;
					}
				}
			}

			if (game == 2)
			{
				screen.clear(sf::Color(26, 28, 36));
				sf::RectangleShape buttonPlay(sf::Vector2f(200, 100));
				sf::RectangleShape buttonHighscore(sf::Vector2f(300, 100));
				sf::RectangleShape buttonLeave(sf::Vector2f(200, 100));

				buttonPlay.setOutlineColor(sf::Color::White);
				buttonPlay.setOutlineThickness(4);
				Play.setPosition(sf::Vector2f(160, 100));
				buttonPlay.setPosition(140, 80);
				buttonPlay.setFillColor(sf::Color(94, 123, 15, 0));

				buttonHighscore.setOutlineColor(sf::Color::White);
				buttonHighscore.setOutlineThickness(4);
				Highscore.setPosition(sf::Vector2f(120, 260));
				buttonHighscore.setPosition(90, 240);
				buttonHighscore.setFillColor(sf::Color(94, 123, 15, 0));

				buttonLeave.setOutlineColor(sf::Color::White);
				buttonLeave.setOutlineThickness(4);
				leave.setPosition(sf::Vector2f(190, 420));
				buttonLeave.setPosition(140, 400);
				buttonLeave.setFillColor(sf::Color(94, 123, 15, 0));

				//Play
				Play.setCharacterSize(40);
				Play.setString("Start!");
				Play.setFillColor(sf::Color::White);

				//Highscore
				Highscore.setCharacterSize(40);
				Highscore.setString("Highscore");
				Highscore.setFillColor(sf::Color::White);

				//leave
				leave.setCharacterSize(40);
				leave.setString("Exit");
				leave.setFillColor(sf::Color::White);

				sf::RectangleShape bottom_line_play(sf::Vector2f(200, 2));
				bottom_line_play.setPosition(145, 162);
				sf::RectangleShape bottom_line_highscore(sf::Vector2f(300, 2));
				bottom_line_highscore.setPosition(95, 330);
				sf::RectangleShape bottom_line_leave(sf::Vector2f(200, 2));
				bottom_line_leave.setPosition(145, 482);

				float positionX = sf::Mouse::getPosition(screen).x;
				float positionY = sf::Mouse::getPosition(screen).y;

				if (positionX > buttonPlay.getPosition().x && positionX < 350 && positionY > buttonPlay.getPosition().y && positionY < 180)
				{
					screen.draw(bottom_line_play);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						game = 1;
					}
				}
				if (positionX > buttonHighscore.getPosition().x && positionX < 370 && positionY > buttonHighscore.getPosition().y && positionY < 330)
				{
					screen.draw(bottom_line_highscore);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						game = 3;
					}
				}
				if (positionX > buttonLeave.getPosition().x && positionX < 350 && positionY > buttonLeave.getPosition().y && positionY < 480)
				{
					screen.draw(bottom_line_leave);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						return 0;
					}
				}

				screen.draw(Play);
				screen.draw(leave);
				screen.draw(Highscore);

				screen.display();
			}
			if (game == 3)
			{
				screen.clear(sf::Color(26, 28, 36));
				sf::Text Text, Text1, Text2, Text3, Text4, button_back;
				std::string item, item1, item2, item3, item4;
				Text.setFillColor(sf::Color::White);
				Text.setFont(font);
				Text.setPosition(sf::Vector2f(230, 100));
				Text1.setFillColor(sf::Color::White);
				Text1.setFont(font);
				Text1.setPosition(sf::Vector2f(230, 150));
				Text2.setFillColor(sf::Color::White);
				Text2.setFont(font);
				Text2.setPosition(sf::Vector2f(230, 200));
				Text3.setFillColor(sf::Color::White);
				Text3.setFont(font);
				Text3.setPosition(sf::Vector2f(230, 250));
				Text4.setFillColor(sf::Color::White);
				Text4.setFont(font);
				Text4.setPosition(sf::Vector2f(230, 300));
				button_back.setFillColor(sf::Color::White);
				button_back.setFont(font);
				button_back.setString("Back");
				button_back.setPosition(sf::Vector2f(0, 500));
				float positionX = sf::Mouse::getPosition(screen).x;
				float positionY = sf::Mouse::getPosition(screen).y;
				sf::RectangleShape bottom_line_back(sf::Vector2f(100, 2));
				bottom_line_back.setPosition(0, 540);
				if (positionX > button_back.getPosition().x && positionX < 100 && positionY > button_back.getPosition().y && positionY < 550)
				{
					screen.draw(bottom_line_back);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						game = 2;
					}
				}
				std::string line, line1, line2, line3, line4;
				std::ifstream highscore_table_text("../highscoreTable.txt");
				while (highscore_table_text >> line >> line1 >> line2 >> line3 >> line4)
				{
					item = line;
					item1 = line1;
					item2 = line2;
					item3 = line3;
					item4 = line4;
				}
				Text.setString(item);
				Text1.setString(item1);
				Text2.setString(item2);
				Text3.setString(item3);
				Text4.setString(item4);

				screen.draw(Text);
				screen.draw(Text1);
				screen.draw(Text2);
				screen.draw(Text3);
				screen.draw(Text4);
				screen.draw(button_back);
				screen.display();
			}
			if (game == 1)
			{

				screen.clear(sf::Color(26, 28, 36));

				for (int i = size; i > 0; i--)
				{
					snakebody[i].x = snakebody[i - 1].x;
					snakebody[i].y = snakebody[i - 1].y;
				}

				if (dir == 1 && dir != 4)
				{
					snakebody[0].x -= 50;
				}
				if (dir == 4 && dir != 1)
				{
					snakebody[0].x += 50;
				}
				if (dir == 2 && dir != 3)
				{
					snakebody[0].y -= 50;
				}
				if (dir == 3 && dir != 2)
				{

					snakebody[0].y += 50;
				}

				if (((snakebody[0].x == nScreenWidth && dir == 4) || (snakebody[0].x == -50 && dir == 1)) || ((snakebody[0].y == nScreenHeight - 50 && dir == 3) || (snakebody[0].y == -50 && dir == 2)))
				{
					for (int i = 0; i < size; i++)
					{
						snakebody[i].x = snakebody[i + 1].x;
						snakebody[i].y = snakebody[i + 1].y;
					}
					game = 0;
				}

				if (snakebody[0].x == Food.getPosition().x && snakebody[0].y == Food.getPosition().y)
				{
					size++;
					score++;
					bGood = true;
					while (bGood)
					{
						randomx = 1 + rand() % 450;
						randomy = 1 + rand() % 450;

						for (int i = 0; i < 9; i++)
						{
							if (randomx <= (i + 1) * 50 && randomx > i * 50)
								randomx = (i + 1) * 50;
							if (randomy <= (i + 1) * 50 && randomy > i * 50)
								randomy = (i + 1) * 50;
						}
						for (int i = 0; i < size; i++)
						{
							if (randomx == snakebody[i].x && randomy == snakebody[i].y)
								break;
							else if ((randomx != snakebody[i].x || randomy != snakebody[i].y) && i == size - 1)
								bGood = false;
						}
					}
				}

				for (int i = 1; i < size; i++)
				{
					Snake.setPosition(snakebody[0].x, snakebody[0].y);
					tail.setPosition(snakebody[i].x, snakebody[i].y);
					tail.setTexture(tailsprite);
					screen.draw(Snake);
					screen.draw(tail);
					if (size > 2)
					{
						if (snakebody[0].x == snakebody[i].x && snakebody[0].y == snakebody[i].y)
						{
							game = 0;
						}
					}
				}

				gameOverScore.setString(" ");
				text.setString("Score: " + std::to_string(score));
				sf::Text previous_highscore;
				previous_highscore.setPosition(sf::Vector2f(nScreenWidth - 200, 525));
				previous_highscore.setFont(font);
				text.setPosition(sf::Vector2f(0, 525));
				text.setCharacterSize(24);
				previous_highscore.setCharacterSize(24);
				std::string line_prev;
				std::string nPrevious_highscore;
				std::ifstream highscore_table_text("highscore.txt");
				while (highscore_table_text >> line_prev)
				{
					nPrevious_highscore = line_prev;
				}
				previous_highscore.setString("HIGHSCORE: " + nPrevious_highscore);
				Food.setPosition(randomx, randomy);
				screen.draw(Food);
				screen.draw(bottom_line);
				std::this_thread::sleep_for(0.5s);
				if (game == 1)
				{
					screen.draw(text);

					screen.draw(previous_highscore);
					screen.display();
				}
			}
			else if (game == 0)
			{
				for (int i = 0; i < size; i++)
				{
					snakebody[i].x = snakebody[i].x;
					snakebody[i].y = snakebody[i].y;
				}

				text.setPosition(sf::Vector2f(140, 210));
				gameOverScore.setPosition(sf::Vector2f(170, 265));
				restart.setPosition(sf::Vector2f(80, 310));
				restart.setFillColor(sf::Color::White);
				text.setFillColor(sf::Color::White);
				text.setCharacterSize(40);
				text.setString("You died");
				gameOverScore.setString("SCORE: " + std::to_string(score));
				restart.setString("Press R to restart.");
				std::ifstream MyReadFile("highscore.txt");
				std::ifstream ScoresTable("highscoreTable.txt");
				std::string line0, line1, line2, line3, line4, line5;
				int nline1, nline2, nline3, nline4, nline5;

				while (ScoresTable >> line1 >> line2 >> line3 >> line4 >> line5)
				{
					nline1 = stoi(line1);
					nline2 = stoi(line2);
					nline3 = stoi(line3);
					nline4 = stoi(line4);
					nline5 = stoi(line5);
					ScoresTable.close();
				}

				if (score > nline1)
				{
					nline1 = score;
				}
				else if (score < nline1 && score > nline2)
				{
					nline2 = score;
				}
				else if (score < nline1 && score < nline2 && score > nline3)
				{
					nline3 = score;
				}
				else if (score < nline1 && score < nline2 && score < nline3 && score > nline4)
				{
					nline4 = score;
				}
				else if (score < nline1 && score < nline2 && score < nline3 && score < nline4 && score > nline5)
				{
					nline5 = score;
				}

				std::ofstream oScoresTable("highscoreTable.txt");
				oScoresTable << nline1 << "\n"
							 << nline2 << "\n"
							 << nline3 << "\n"
							 << nline4 << "\n"
							 << nline5 << "\n";

				while (MyReadFile >> line0)
				{
					scoreCheck = stoi(line0);
				}
				if (score > scoreCheck)
				{
					std::ofstream highscore("highscore.txt");
					highscore << score;
				}
				else
				{
					std::ofstream highscore("highscore.txt");
					highscore << scoreCheck;
				}

				if (game == 0)
				{
					screen.draw(text);
					screen.draw(gameOverScore);
					screen.draw(restart);

					screen.display();
				}
			}
		}
	}
	return 0;
}
