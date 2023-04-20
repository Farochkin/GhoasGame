// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <time.h>


// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;


int main()
{
	// Create a video mode object and view to get the current desktop mode
	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;
	sf::View view(sf::FloatRect(0.f, 0.f, width, height));
	VideoMode vm(width, height);

	// Create and open a window for the game, selected default for screen size
	RenderWindow window(vm, "Chaos Game!", Style::Default);

	//Create a vector that will hold the vertices for the triangle
	//Create a vector that will store the points for the algorithm
	vector<Vector2f> vertices;
	vector<Vector2f> points;


	//Creating our text and font's

	Font font;

	Text instructions;
	font.loadFromFile("./fonts/Roboto-Black.ttf");
	instructions.setFont(font);
	instructions.setCharacterSize(50);
	instructions.setString("Click 3 points to create a Triangle, then a fourth to start the Algorithm");

	Text messageText;
	messageText.setFont(font);
	messageText.setCharacterSize(30);

	//To get random number from 1-3 later down
	srand(time(0));

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			//If click window close button, program closes
			if (event.type == sf::Event::Closed)
				window.close();
			//Handling all of the mouseclicks
			if (event.type == sf::Event::MouseButtonPressed)
			{
				//First 3 clicks are the vertices for the triangle
				if (event.mouseButton.button == sf::Mouse::Left && vertices.size() < 3)
				{
					Vector2i pixelPos = { event.mouseButton.x, event.mouseButton.y };
					Vector2f worldPos = window.mapPixelToCoords(pixelPos, view);
					vertices.push_back(worldPos);
				}
				//4th click is the start of the algorithm
				else if (event.mouseButton.button == sf::Mouse::Left && vertices.size() == 3)
				{
					Vector2i pixelPos = { event.mouseButton.x, event.mouseButton.y };
					Vector2f worldPos = window.mapPixelToCoords(pixelPos, view);
					points.push_back(worldPos);
				}
			}

		}
		//This creates all of the points
		if (points.size() > 0)
		{
			for (size_t i = 1; i < 1000; i++)
			{
				int random = rand() % 3;
				Vector2f newPoint;
				newPoint.x = ((vertices.at(random).x + points.at(i - 1).x) / 2);
				newPoint.y = ((vertices.at(random).y + points.at(i - 1).y) / 2);
				points.push_back(newPoint);
			}
		}
		//if click esc then program closes
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/

		//Setting up the text
		std::stringstream ss;
		ss << "Vertex count = " << vertices.size();
		messageText.setString(ss.str());
		FloatRect textRect = messageText.getLocalBounds();
		messageText.setOrigin(textRect.left +
			textRect.width / 2.0f,
			textRect.top +
			textRect.height / 2.0f);
		messageText.setPosition(width / 2.0f, 100);

		FloatRect textRectinstruct = instructions.getLocalBounds();
		instructions.setOrigin(textRect.left +
			textRectinstruct.width / 2.0f,
			textRectinstruct.top +
			textRectinstruct.height / 2.0f);
		instructions.setPosition(width / 2.0f, 50);

		/*
		****************************************
		Draw the scene
		****************************************
		*/
		window.setView(view);
		// Clear everything from the last run frame
		window.clear();
		// Draw our game scene here

		RectangleShape shape{ Vector2f{4,4} };
		shape.setFillColor(Color::Cyan);
		for (size_t i = 0; i < vertices.size(); i++)
		{
			shape.setPosition(vertices.at(i));
			window.draw(shape);
		}

		RectangleShape shape2{ Vector2f{4,4} };
		shape2.setFillColor(Color::Red);
		for (size_t i = 1; i < points.size(); i++)
		{
			shape2.setPosition(points.at(i));
			window.draw(shape2);
		}
		window.draw(messageText);
		window.draw(instructions);
		// Show everything we just drew
		window.display();
	}

	return 0;
}