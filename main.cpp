#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <cstdio>
#include <ctime>


using namespace sf;


int main()
{

    ///Sta³e

    const int maxPlayerSpeed = 8;
    ///losowe liczy
    srand(time(NULL));

    ///Okno
    RenderWindow window(VideoMode(800,600,32),"Pong!");
    window.setFramerateLimit(60);

    ///Zmienne Okreœlaj¹ce Stany

        bool ballMoving = false;
        bool goRight = false;
        bool goLeft = false;
        int ballSpeedX = -10;
        int ballSpeedY = -10;
        bool ballFromWhere = 1;

    ///Gracz

    Vector2f playerSize(200,20);
    RectangleShape player;
    player.setSize(playerSize);
    player.setOrigin(100,10);
    player.setPosition(400,570);
    player.setFillColor(Color(0,100,200));


    ///Przeciwnik

    RectangleShape enemy;
    enemy.setSize(playerSize);
    enemy.setOrigin(100,10);
    enemy.setPosition(400,20);
    enemy.setFillColor(Color(200,100,0));

    ///Pi³ka

    CircleShape ball;
    ball.setRadius(21);
    ball.setOrigin(11,11);
    ball.setFillColor(Color::Black);



    ///Pêtla

    while(window.isOpen())
    {
        Event event;

        ///Sprawdzanie Eventów
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                window.close();
            }

            ///Sterowanie ( Jeœli Event jest przyciskiem z klawiatury )
            if(event.type == Event::KeyPressed)
            {
                if(event.key.code == Keyboard::A)
                {
                    goLeft = true;
                    break;
                }

                else if(event.key.code == Keyboard::D)
                {
                    goRight = true;
                    break;
                }
                else if(event.key.code == Keyboard::Space)
                {
                    ballMoving = true;
                    break;
                }
                if(event.key.code == Keyboard::Escape)
                {
                    ballMoving = false;
                    break;
                }
                break;
            }

            if(event.type == Event::KeyReleased)
            {
                if(event.key.code == Keyboard::A)
                {
                    goLeft = false;
                    break;
                }
                else if(event.key.code == Keyboard::D)
                {
                    goRight = false;
                    break;
                }
            }


        }


        ///Ruch gracza
        if(goLeft && player.getPosition().x > 100)
            player.move(-maxPlayerSpeed,0);

        else if(goRight && player.getPosition().x < 700)
            player.move(maxPlayerSpeed,0);

        ///Ruch przeciwnika w kierunku pi³ki

        if(ballMoving)
        {
            if(ball.getPosition().x > enemy.getPosition().x)
            {
                enemy.move(8.5,0);
            }
            if(ball.getPosition().x < enemy.getPosition().x)
            {
                enemy.move(-8.5,0);
            }
        }


        ///Zachowanie pi³ki

        if(!ballMoving)
            ball.setPosition(player.getPosition().x, 530);
        else if(ballMoving)
            ball.move(ballSpeedX,ballSpeedY);


        ///Kolizja
        if(ball.getPosition().x <= 0 || ball.getPosition().x >= 780)
            ballSpeedX = -ballSpeedX;

        else if(ball.getPosition().y <= 0 || ball.getPosition().y >= 580)
        {
            ballMoving = false;
            enemy.setPosition(400,20);
            player.setPosition(400,570);
            ballSpeedY = -10;
        }

        if(ball.getPosition().x >= enemy.getPosition().x - 100 && ball.getPosition().x <= enemy.getPosition().x +100 &&
           ball.getPosition().y == 30)
            ballSpeedY = 10;

        if(ball.getPosition().x >= player.getPosition().x - 100 && ball.getPosition().x <= player.getPosition().x +100 &&
           ball.getPosition().y == 540)
            ballSpeedY = -10;


        window.clear(Color(140,140,140));
        ///Rysowanie

        window.draw(ball);
        window.draw(player);
        window.draw(enemy);

        window.display();
    }
    return 1;
}
