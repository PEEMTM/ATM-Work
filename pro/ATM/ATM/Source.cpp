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

            window.display();
        }
    }

    return 0;
}