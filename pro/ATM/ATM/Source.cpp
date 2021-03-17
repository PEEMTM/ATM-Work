#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;
using namespace sf;
int main()
{
    Texture x1, x2,x3;
    x1.loadFromFile("image/Background.png");
    x2.loadFromFile("image/login.png");
    x3.loadFromFile("image/loginbotton.png");

    sf::RenderWindow window(sf::VideoMode(1000, 802), "SFML works!");

    Sprite Background(x1), login(x2),loginbotton(x3);

    while (window.isOpen())
    {
        window.draw(Background);
        window.display();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Background.setTexture(x2);
            loginbotton.setPosition(600,500);
        }
    }

    return 0;
}