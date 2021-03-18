#include <SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>

using namespace std;
using namespace sf;

string toUpperStr(string x) {
	string y = x;
	for (unsigned i = 0; i < x.size(); i++) y[i] = toupper(x[i]);
	return y;
}

int main()
{
	Texture x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16;
	x1.loadFromFile("image/Background.png");
	x2.loadFromFile("image/login.png");
	x3.loadFromFile("image/loginbotton1.png");
	x4.loadFromFile("image/depositbutton.png");
	x5.loadFromFile("image/withdrawbutton.png");
	x6.loadFromFile("image/checkbutton.png");
	x7.loadFromFile("image/transferbutton.png");
	x8.loadFromFile("image/viewbutton.png");
	x9.loadFromFile("image/exitbutton.png");
	x10.loadFromFile("image/transaction.png");
	x11.loadFromFile("image/depositbg.png");
	x12.loadFromFile("image/withdrawbg.png");
	x13.loadFromFile("image/tranferbg.png");
	x14.loadFromFile("image/checkbg.png");
	x15.loadFromFile("image/viewbg.png");


	sf::RenderWindow window(sf::VideoMode(1000, 802), "SFML works!");

	Sprite Background(x1), login(x2), loginbotton1(x3), transaction(x10), exitbutton(x9), viewbutton(x8), tranferbutton(x7), checkbutton(x6), withdrawbutton(x5), depositbutton(x4);


	enum States { swelcome, slogin, stransaction, depositbg, withdrawbg, tranferbg, checkbg, viewbg };
	short unsigned currentState = swelcome;
	Text username, password, moneynow, inputmoney, * textPtr = &username;
	Font font;
	font.loadFromFile("font/roboto/Roboto-Black.ttf");
	username.setFont(font);
	username.setCharacterSize(55);
	password.setFont(font);
	password.setCharacterSize(55);
	moneynow.setFont(font);
	moneynow.setCharacterSize(55);
	inputmoney.setFont(font);
	inputmoney.setCharacterSize(55);
	string username1 = "";
	username.setPosition(526, 410);
	//string moneynow = ดึงไฟล์เงินมาใส่
	vector<string> names;
	vector<int> spass;
	vector<double> moneys;
	vector<string> stats;
	vector<double> balances;

	string text = {}, c = {}, key = {};
	int m = 0;
	char name[100], stat[10];
	double balance = 0;
	fstream list("List.txt", ios::in);
	while (getline(list, text)) {
		int pass = 0;
		double money = 0;
		char ctext[100] = {};
		char format[] = "%[^,],%d,%f,%[^,],%f";
		strcpy_s(ctext, text.c_str());
		sscanf_s(ctext, format, name, &pass, &money, stat, &balance);
		names.push_back(name);
		spass.push_back(pass);
		moneys.push_back(money);
		stats.push_back(stat);
		balances.push_back(balance);
	}
	list.close();

	string inputmoney1 = "";
	string password1 = "";
	string star = "";
	string* textbox1 = &username1;
	password.setPosition(526, 580);
	moneynow.setPosition(705, 420);
	inputmoney.setPosition(705, 530);
	inputmoney.setFillColor(Color(0, 92, 168, 255));

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
						currentState = depositbg;

					}
				}
				if (withdrawbutton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						currentState = withdrawbg;
					}
				}
				if (tranferbutton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						currentState = tranferbg;
					}
				}
				if (checkbutton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						currentState = checkbg;
					}
				}
				if (viewbutton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						currentState = viewbg;
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
					key = toUpperStr(*textbox1);
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
			if (currentState == depositbg) {
				textPtr = &inputmoney;
				textbox1 = &inputmoney1;

				if (FloatRect(705.f, 420.f, 256.f, 116.f).contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						textbox1 = &inputmoney1;
						textPtr = &inputmoney;
					}
				}

				if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode >= 48 && event.text.unicode <= 57 && event.text.unicode != 8) {
						if (textPtr == &inputmoney && textbox1->size() < 7)
						{
							*textbox1 += event.text.unicode;
							textPtr->setString(*textbox1);
						}
					}
				}
				if (event.key.code == sf::Keyboard::BackSpace && event.type == event.KeyPressed) {
					if (!textbox1->empty()) {
						textbox1->erase(textbox1->end() - 1);
						textPtr->setString(*textbox1);
					}
				}
				//รวมเงินเก่ากับใหม่
				if (event.key.code == sf::Keyboard::Return && event.type == event.KeyPressed) {
					int N = sizeof(names);
					double a = 0;
					for (int i = 0; i < N; i++) {
						if (key == toUpperStr(names[i])) {
							m = i;
						}
						a = balances[m];
						balances[m] += atof(textbox1->c_str());
					}

				}

			}

			cout << star << endl;
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
				loginbotton1.setPosition(760, 670);
				window.draw(loginbotton1);
				window.draw(username);
				window.draw(password);

				break;

			case stransaction:
				Background.setTexture(x10);
				window.draw(Background);
				exitbutton.setPosition(625, 450);
				viewbutton.setPosition(465, 650);
				checkbutton.setPosition(625, 250);
				tranferbutton.setPosition(0, 650);
				withdrawbutton.setPosition(0, 450);
				depositbutton.setPosition(0, 250);
				window.draw(exitbutton);
				window.draw(viewbutton);
				window.draw(checkbutton);
				window.draw(tranferbutton);
				window.draw(withdrawbutton);
				window.draw(depositbutton);

				break;

			case depositbg:
				Background.setTexture(x11);
				window.draw(Background);
				window.draw(moneynow);
				window.draw(inputmoney);
				break;

			case withdrawbg:
				Background.setTexture(x12);
				window.draw(Background);
				break;

			case tranferbg:
				Background.setTexture(x13);
				window.draw(Background);
				break;

			case checkbg:
				Background.setTexture(x14);
				window.draw(Background);
				break;
			}
			Text mouseText;
			mouseText.setPosition(window.mapPixelToCoords(Mouse::getPosition(window)));
			mouseText.setFont(font);
			mouseText.setCharacterSize(20);
			stringstream ss;
			ss << window.mapPixelToCoords(Mouse::getPosition(window)).x << " " << window.mapPixelToCoords(Mouse::getPosition(window)).y;
			mouseText.setString(ss.str());
			window.draw(mouseText);

			window.display();
		}
	}
}
