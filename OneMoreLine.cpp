#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
//function to size and place player and wall
void Setup(sf::CircleShape& p,sf::RectangleShape& lw, sf::RectangleShape& rw, std::vector<sf::CircleShape>& obst, int wHeight, int wWidth);
void Input(sf::RectangleShape& lw, sf::RectangleShape& rw, sf::CircleShape& obst, bool& fall);
double CircleMath(sf::CircleShape obst);
    int CloseObst(std::vector<sf::CircleShape>& obst, int vsize);
    int playX(0), playY(0);
    bool clockwise = true;
      //variables for circle movement
     double angle(0), xVel(0), yVel(2);
int main()
{
    //int grav(2);
    int winHeight = 500;
    int winWidth = 250; 
    int x(0);
    int vsize(0);
    //whether the obst are falling or not
    bool falling(true);
  

    //instantiate window and player/wall objects
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "More Lines");
    sf::CircleShape player(10.f);
    sf::RectangleShape lWall;
    sf::RectangleShape rWall;

    std::vector<sf::CircleShape> obst;
   obst.push_back(sf::CircleShape()); vsize ++;
   obst[0].setRadius(10);
   obst.push_back(sf::CircleShape()); vsize ++;
   obst[1].setRadius(20);
   obst.push_back(sf::CircleShape()); vsize ++;
   obst[2].setRadius(7);
        playX = winWidth/2-player.getRadius();
    playY = (winHeight/4)*3;
//function to size and place player and wall
    Setup(player,lWall,rWall, obst,winHeight,winWidth);


    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time time1 = clock.getElapsedTime();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(time1.asSeconds() > .005){ //Lets relax a little
            //playY -=1;
            /*
            if(falling){
                obst[0].setPosition(obst[0].getPosition().x,obst[0].getPosition().y+grav);
            }
            */
         x =  CloseObst(obst, vsize);
        //std::cout << x <<"\n";
            Input(lWall,rWall, obst[x], falling);

            //move the player by the velocity all the time, the velocity starts at 2 to be a falling start
               // std::cout << angle << "\n";

        lWall.setPosition(sf::Vector2f(lWall.getPosition().x+ xVel,lWall.getPosition().y)); 
        rWall.setPosition(sf::Vector2f(rWall.getPosition().x+ xVel,rWall.getPosition().y)); 
        //make all obstacles move the same
        for (int i = 0; i < vsize; i ++){
        obst[i].setPosition(sf::Vector2f(obst[i].getPosition().x+xVel,obst[i].getPosition().y+ yVel));
        } 
            player.setPosition(sf::Vector2f(playX,playY));

        window.clear();
        window.draw(lWall);
        window.draw(rWall);

        window.draw(player);
        for (int i = 0; i < vsize; i ++){
        window.draw(obst[i]);
        }
        window.display();
        clock.restart();
        }
    }

    return 0;
}

void Setup(sf::CircleShape& p,sf::RectangleShape& lw, sf::RectangleShape& rw,std::vector<sf::CircleShape>& obst, int wHeight, int wWidth){
        //create window and player as a circle

    
    //place ball in the middle
    p.setOrigin(10,10);
    p.setFillColor(sf::Color::Red);
    p.setPosition(sf::Vector2f((wWidth/2),(wHeight/4)*3));
    //set boundaries size and position
    sf::Vector2f wallSize(10,wHeight);

    lw.setSize(wallSize);
    lw.setPosition(sf::Vector2f(25,0));
    lw.setFillColor(sf::Color::Blue);

    rw.setSize(wallSize);
    rw.setPosition(sf::Vector2f(wWidth-35,0));
    rw.setFillColor(sf::Color::Blue);
    //set up obstacles
  //  obst.push_back(sf::CircleShape());
    //obst.setRadius(10.0f);
    obst[0].setOrigin(10,10);
    obst[0].setFillColor(sf::Color::Magenta);
    obst[0].setPosition(sf::Vector2f(wWidth/2-10, 20));

    obst[1].setOrigin(20,20);
    obst[1].setFillColor(sf::Color::Green);
    obst[1].setPosition(sf::Vector2f(wWidth/2+ 40, -120));

    obst[2].setOrigin(7,7);
    obst[2].setFillColor(sf::Color::Cyan);
    obst[2].setPosition(sf::Vector2f(wWidth/2-50, -300));
}


//moves walls left and right for testing
void Input(sf::RectangleShape& lw, sf::RectangleShape& rw, sf::CircleShape& obst, bool& fall){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        lw.setPosition(sf::Vector2f(lw.getPosition().x+3,lw.getPosition().y)); 
        rw.setPosition(sf::Vector2f(rw.getPosition().x+3,rw.getPosition().y)); 
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        lw.setPosition(sf::Vector2f(lw.getPosition().x-3,lw.getPosition().y)); 
        rw.setPosition(sf::Vector2f(rw.getPosition().x-3,rw.getPosition().y)); 
        

    }

bool reset(true);
    //walls move according to the x velocity
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
           fall = false;
           reset = true;
        }
        //cases for which direction the player spins
        else{
            fall = true;
            if ((obst.getPosition().x > playX) && yVel > 0){
                clockwise = true;
            }
            else if ((obst.getPosition().x > playX) && yVel < 0){
                clockwise = false;
            }
            else if ((obst.getPosition().x < playX) && yVel > 0){
                clockwise = false;
            }
            else if ((obst.getPosition().x < playX) && yVel < 0){
                clockwise = true;
            }
        }
        
        if(fall == false){
           //for some reason set angle to 0 if its above 2 pi both directions, even though Im adding like 80 to it every frame? it works though
          if(angle > 2*3.14159265359 || angle < -2*3.1415926535){
          angle = 0;
        }
        
        //if the obst is to the right, go clockwise, left, counterclockwise, since it will always check, use boolean to tell it to change or not

        //this part is not working- yes it is now
        if(clockwise){
        angle += (CircleMath(obst));
        }
        
        else{
            angle -= CircleMath(obst);
        }
        
        xVel = cos(angle);
        yVel = sin(angle);
        
        //why the hell does this work
        
        /* size of angle change determines radius of circle
        this will eventually be a function of the distance to whatever obstacle is closest

        the angle cant change by the distance between, it would be too big
         
         it could be .00125 times the distance for the correct radius? but why
         its not :(
        */
        } 

        
} 
        

double CircleMath( sf::CircleShape obst){
    int xdist(0), ydist(0);
    double distance(0);
    xdist = (obst.getPosition().x-playX);
    ydist = (obst.getPosition().y - playY);
    distance = sqrt(xdist*xdist+ydist*ydist);
    //std::cout << distance << std::endl;
    return distance;
}

 int CloseObst(std::vector<sf::CircleShape>& obst, int vsize){
        //receive vector of obstacles and find the closest one
        int closest(10000);
        int index(0);
    for (int i = 0; i < vsize; i ++){
            if (CircleMath(obst[i]) < closest){
                closest = CircleMath(obst[i]); 
                index = i;
            }
    }

    //until I finish the math, return 0 for my one obstacle, I just realized I will still need to move every obstacle the same way, just the
    // amount the angle changes by is determined by the closest obstacle
    return index;
    }
