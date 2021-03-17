#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;
int main()
{
    Texture x1, x2,x3;
    x1.loadFromFile("image/Background.png");
    x2.loadFromFile("image/login.png");
    x3.loadFromFile("image/loginbotton1.png");

    sf::RenderWindow window(sf::VideoMode(1000, 802), "SFML works!");

    Sprite Background(x1), login(x2),loginbotton1(x3);
    
    
    enum States { swelcome,slogin };
    short unsigned currentState = swelcome;
    Text username,password;
    Font font;
    font.loadFromFile("font/roboto/Roboto-Black.ttf");
     username.setFont(font);
     username.setCharacterSize(55);
     password.setFont(font);
     password.setCharacterSize(55);
    string username1 = "";
    username.setPosition(526,410);
    string password1 = "";
    password.setPosition(526, 600);
    
    while (window.isOpen())
    {
       
        sf::Event event;

        while (window.pollEvent(event))
        {
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
 
                break;
            }
            if (loginbotton1.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    cout << "dawdwadaw";
                }
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128 && event.text.unicode != 8) {
                    username1 += event.text.unicode;
                    username.setString(username1);
                }
            }
            if (event.key.code == sf::Keyboard::BackSpace && event.type == event.KeyPressed) {
                if (username1.size() > 0) {
                    username1.erase(username1.end() - 1);
                    username.setString(username1);
                }
                /*
                if (event.text.unicode == 1310) {
                    if (event.type == sf::Event::TextEntered) {
                        if (event.text.unicode < 128 && event.text.unicode != 8) {
                            password1 += event.text.unicode;
                            password.setString(password1);
                        }

                    }*/
               }
            }

            window.draw(username);
            window.draw(password);
            window.display();
        }
    }

    return 0;
}