#include <SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include <stdio.h>
#include <time.h>
#include<sstream>
#include <time.h>

using namespace std;
using namespace sf;
using std::cout;

string toUpperStr(string x) {
	string y = x;
	for (unsigned i = 0; i < x.size(); i++) y[i] = toupper(x[i]);
	return y;
}

void write(string name, int pass, float money, string status, float amount) {
	fstream list("List.txt", ios::app);
	list << name << "," << pass << "," << money << "," << status << "," << amount << endl;
	list.close();
}

void importDataFromFile(string fn, vector<string>& names, vector<int>& spass, vector<float>& moneys, vector<string>& stats, vector<float>& balances) {
	fstream source(fn.c_str());
	string text, c;
	char name[100] = {}, stat[10] = {};
	float balance = 0;
	fstream check("List.txt", ios::in);
	if (getline(check, text)) {
		c = "T";
	}
	else c = "F";
	check.close();
	if (c == "F") {
		while (getline(source, text)) {
			int pass;
			float money;
			char ctext[100] = {};
			char format[] = "%[^,],%d,%f";
			strcpy_s(ctext, text.c_str());
			sscanf_s(ctext, format, name, 5, &pass, &money);
			write(name, pass, money, "add", money);
		}
	}
	source.close();
	fstream list("List.txt", ios::in);
	while (getline(list, text)) {
		cout << text << endl;
		int pass;
		float money;
		char ctext[100] = {};
		char format[] = "%[^,],%d,%f,%[^,],%f";
		strcpy_s(ctext, text.c_str());
		sscanf_s(ctext, format, name, 5, &pass, &money, stat,7, &balance);
		names.push_back(name);
		spass.push_back(pass);
		moneys.push_back(money);
		stats.push_back(stat);
		balances.push_back(balance);
	}
	list.close();
}

void waiting(unsigned int mseconds) {
	clock_t goal = mseconds + clock();
	while (goal > clock());
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
	x13.loadFromFile("image/transferbg.png");
	x14.loadFromFile("image/checkbg.png");
	x15.loadFromFile("image/viewbg.png");
	x16.loadFromFile("image/checknowbg.png");

	sf::RenderWindow window(sf::VideoMode(1000, 802), "SFML works!");

	Sprite Background(x1), login(x2), loginbotton1(x3), transaction(x10), exitbutton(x9), viewbutton(x8), tranferbutton(x7), checkbutton(x6), withdrawbutton(x5), depositbutton(x4);


	enum States { swelcome, slogin, stransaction, depositbg, withdrawbg, tranferbg, checkbg, viewbg, checknowbg };
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

	string filename = "Bank.txt";
	vector<string> names;
	vector<int> spass;
	vector<float> moneys;
	vector<string> stats;
	vector<float> balances;
	string key, stat = "False";
	int pass;
	importDataFromFile(filename, names, spass, moneys, stats, balances);
	int N = sizeof(names)/sizeof(names[0]);

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
						textPtr = &username;
						textbox1 = &username1;
						username1 = "";
						username.setString(username1);
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
			//login			
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
							pass = atoi(textbox1->c_str());
						}
						else if (textPtr == &username && textbox1->size() < 12)
						{
							*textbox1 += event.text.unicode;
							textPtr->setString(*textbox1);
							key = toUpperStr(*textbox1);
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
			//ฝาก
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
				if (event.key.code == sf::Keyboard::Enter && event.type == event.KeyPressed) {
					currentState = checknowbg;
				}

			}
			//ถอน
			if (currentState == withdrawbg) {
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
				if (event.key.code == sf::Keyboard::Enter && event.type == event.KeyPressed) {
					currentState = checknowbg;
				}

			}
			// โอน
			if (currentState == tranferbg) {

				if (FloatRect(685.f, 450.f, 283.f, 101.f).contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						textbox1 = &username1;
						textPtr = &username;
					}
				}
				if (FloatRect(685.f, 600.f, 283.f, 101.f).contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						textbox1 = &inputmoney1;
						textPtr = &inputmoney;
					}
				}

				if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode != 8) {
						if (textPtr == &inputmoney && textbox1->size() < 7 && event.text.unicode >= 48 && event.text.unicode <= 57)
						{
							*textbox1 += event.text.unicode;
							textPtr->setString(*textbox1);
						}
						else if (textPtr == &username && textbox1->size() < 8)
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
				if (event.key.code == sf::Keyboard::Enter && event.type == event.KeyPressed) {
					currentState = checknowbg;
				}

			}
			/*เช็คเงิน
						if (currentState == checkbg) {

							// moneynow = น่าจะ moneys ที่อ่านจากไฟล์
						}*/

						/*	ประวัติ
									if (currentState == viewbg) {
										ไม่รู้ว่ามึงจะแสดงไรบ้าง
									}

						*/
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
			moneynow.setPosition(720, 330);
			window.draw(inputmoney);
			break;

		case withdrawbg:
			Background.setTexture(x12);
			window.draw(Background);
			moneynow.setPosition(720, 330);
			window.draw(moneynow);
			window.draw(inputmoney);
			break;

		case tranferbg:
			Background.setTexture(x13);
			window.draw(Background);
			moneynow.setPosition(700, 315);
			username.setPosition(685, 450);
			inputmoney.setPosition(685, 600);
			window.draw(moneynow);
			window.draw(username);
			window.draw(inputmoney);
			break;

		case checkbg:
			Background.setTexture(x14);
			window.draw(Background);
			moneynow.setPosition(400, 625);
			window.draw(moneynow);
			window.display();
			waiting(5000);
			window.close();

			break;

		case viewbg:
			Background.setTexture(x15);
			window.draw(Background);
			window.display();
			waiting(5000);
			window.close();

			break;

		case checknowbg:
			Background.setTexture(x16);
			window.draw(Background);
			moneynow.setPosition(400, 625);
			window.display();
			waiting(5000);
			window.close();


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