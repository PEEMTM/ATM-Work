#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;

int main()
{
	Texture x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16;
	x1.loadFromFile("image/Background.png");
	x2.loadFromFile("image/login.png");
	x3.loadFromFile("image/loginbotton1.png");
	x4.loadFromFile("image/depositbutton.png");
	x5.loadFromFile("image/withdrawbutton.png");
	x6.loadFromFile("image/checkbutton.png");
	x7.loadFromFile("image/tranferbutton.png");
	x8.loadFromFile("image/viewbutton.png");
	x9.loadFromFile("image/exitbutton.png");
	x10.loadFromFile("image/transaction.png");
	x11.loadFromFile("image/depositbg.png");


	sf::RenderWindow window(sf::VideoMode(1000, 802), "SFML works!");

	Sprite Background(x1), login(x2), loginbotton1(x3), transaction(x10), exitbutton(x9), viewbutton(x8), tranferbutton(x7), checkbutton(x6), withdrawbutton(x5), depositbutton(x4);


	enum States { swelcome, slogin, stransaction, soutput };
	short unsigned currentState = swelcome;
	Text username, password, * textPtr = &username;
	Font font;
	font.loadFromFile("font/roboto/Roboto-Black.ttf");
	username.setFont(font);
	username.setCharacterSize(55);
	password.setFont(font);
	password.setCharacterSize(55);
	string username1 = "";
	username.setPosition(526, 410);
	string password1 = "";
	string star = "";
	string* textbox1 = &username1;
	password.setPosition(526, 580);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (currentState == stransaction) {
				if (depositbutton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						currentState = soutput;
					}
				}
				if (withdrawbutton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						currentState = soutput;
					}
				}
				if (tranferbutton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						currentState = soutput;
					}
				}
				if (checkbutton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						currentState = soutput;
					}
				}
				if (viewbutton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						currentState = soutput;
					}
				}
				if (exitbutton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						window.close();
					}
				}
			}
			
			if (currentState == slogin) {
				star = "";

				if (FloatRect(520.f, 415.f, 440.f, 99.f).contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						textbox1 = &username1;
						textPtr = &username;
					}
				}
				if (FloatRect(520.f, 600.f, 440.f, 99.f).contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						textbox1 = &password1;
						textPtr = &password;
					}
				}

				if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode < 128 && event.text.unicode != 8) {
						if (textPtr == &password && textbox1->size() < 15)
						{
							*textbox1 += event.text.unicode;
							textPtr->setString(star);
						}
						else if (textPtr == &username && textbox1->size() < 12)
						{
							*textbox1 += event.text.unicode;
							textPtr->setString(*textbox1);
						}
					}
				}

				for (int i = 0; i < password1.size(); i++) {
					star += "*";
				}

				password.setString(star);

				if (event.key.code == sf::Keyboard::BackSpace && event.type == event.KeyPressed) {
					if (!textbox1->empty()) {
						textbox1->erase(textbox1->end() - 1);
						textPtr->setString(*textbox1);
					}
				}

				if (loginbotton1.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (Mouse::isButtonPressed(Mouse::Left)) {
						currentState = stransaction;
					}
				}
			}
		}


		window.clear();

		switch (currentState)
		{
		case swelcome:
			window.draw(Background);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				currentState = slogin;
			}
			break;

		case slogin:
			Background.setTexture(x2);
			window.draw(Background);
			loginbotton1.setPosition(750, 630);
			window.draw(loginbotton1);
			window.draw(username);
			window.draw(password);

			break;

		case stransaction:
			Background.setTexture(x10);
			window.draw(Background);
			exitbutton.setPosition(310, 100);
			viewbutton.setPosition(240, 300);
			checkbutton.setPosition(320, -100);
			tranferbutton.setPosition(-310, 300);
			withdrawbutton.setPosition(-300, 100);
			depositbutton.setPosition(-310, -100);
			window.draw(exitbutton);
			window.draw(viewbutton);
			window.draw(checkbutton);
			window.draw(tranferbutton);
			window.draw(withdrawbutton);
			window.draw(depositbutton);

			break;

		case soutput:
			Background.setTexture(x11);
			window.draw(Background);
			break;
		}


		window.display();
	}
}