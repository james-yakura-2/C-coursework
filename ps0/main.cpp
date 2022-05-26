#include <SFML/Graphics.hpp>

int main()
{
    int windowWidth=500;
    int windowHeight=500;
    int imageWidth=50;
    int imageHeight=50;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML works!");
    sf::Texture texture;
    sf::IntRect drawRectangle(0,0,imageWidth,imageHeight);
    if (!texture.loadFromFile("sprite.png", drawRectangle))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    int xpos=0;
    int ypos=0;
    int dx=3;
    int dy=7;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        xpos+=dx;
        ypos+=dy;
        sprite.setPosition(xpos,ypos);
        
        //Bounce off sides of window
        if((xpos<0 && dx<0) || (xpos+imageWidth>windowWidth && dx>0))
        {
          dx*=-1;
        }
        if((ypos<0 && dy<0) || (ypos+imageHeight>windowHeight && dy>0))
        {
          dy*=-1;
        }
        
        //Respond to keystrokes
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
          dx-=1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
          dx+=1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
          dy-=1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
          dy+=1;
        }
        
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}