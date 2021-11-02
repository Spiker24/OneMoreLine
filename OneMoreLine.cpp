#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <time.h>

/* still to add:

More obstacles
Game over functionality-oustide wall and hitting circle ----DONE
start screen
best score
super need to speed it up somehow ----Kinda done but with more bugs
*/
//function to size and place player and wall
void Setup(sf::CircleShape& p,sf::RectangleShape& lw, sf::RectangleShape& rw, std::vector<sf::CircleShape>& obst, int wHeight, int wWidth);
void Input(sf::RectangleShape& lw, sf::RectangleShape& rw, sf::CircleShape& obst, bool& fall,sf::CircleShape& player);
void GameOver();
double CircleMath(sf::CircleShape obst);
    int CloseObst(std::vector<sf::CircleShape>& obst, int vsize);
    int randX(sf::RectangleShape lWall);
    int playX(0), playY(0);
    bool clockwise = true, quit = false;
      //variables for circle movement
     double angle(0), xVel(0), yVel(2);
       int winHeight = 600;
    int winWidth = 300; 
int main()
{
    srand (time(NULL));
    //int grav(2);
  
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
   obst.push_back(sf::CircleShape()); vsize ++;
   obst[3].setRadius(12);
   obst.push_back(sf::CircleShape()); vsize ++;
   obst[4].setRadius(15);
   obst.push_back(sf::CircleShape()); vsize ++;
   obst[5].setRadius(9);
   obst.push_back(sf::CircleShape()); vsize ++;
   obst[6].setRadius(14);
   obst.push_back(sf::CircleShape()); vsize ++;
   obst[7].setRadius(23);

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

        if(time1.asSeconds() > .003){ //Lets relax a little
         
           if(falling){
         x =  CloseObst(obst, vsize);
         
            if ((playX+10 >=rWall.getPosition().x || playX-10 <=lWall.getPosition().x) || CircleMath(obst[x]) <= 10+obst[x].getRadius()){ //check for game over conditions
                xVel = 0;
                yVel = 0;
                GameOver();
                if(quit){
                    window.close();
                }
                Setup(player,lWall,rWall, obst,winHeight,winWidth);

            }
            
           }
        //std::cout << x <<"\n";
            Input(lWall,rWall, obst[x], falling,player);

            //move the player by the velocity all the time, the velocity starts at 2 to be a falling start
               // std::cout << angle << "\n";

        lWall.setPosition(sf::Vector2f(lWall.getPosition().x+ xVel,lWall.getPosition().y)); 
        rWall.setPosition(sf::Vector2f(rWall.getPosition().x+ xVel,rWall.getPosition().y)); 
        //make all obstacles move the same
        for (int i = 0; i < vsize; i ++){
        obst[i].setPosition(sf::Vector2f(obst[i].getPosition().x+xVel,obst[i].getPosition().y+ yVel));
        if (obst[i].getPosition().y > 2*winHeight){
            obst[i].setPosition(randX(lWall),-100);
        }
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
    yVel = 2;
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
    obst[0].setPosition(sf::Vector2f(randX(lw), 20));

    obst[1].setOrigin(20,20);
    obst[1].setFillColor(sf::Color::Green);
    obst[1].setPosition(sf::Vector2f(randX(lw), -120));

    obst[2].setOrigin(7,7);
    obst[2].setFillColor(sf::Color::Cyan);
    obst[2].setPosition(sf::Vector2f(randX(lw), -300));

    obst[3].setOrigin(12,12);
    obst[3].setFillColor(sf::Color::Red);
    obst[3].setPosition(sf::Vector2f(randX(lw), -450));

    obst[4].setOrigin(15,15);
    obst[4].setFillColor(sf::Color::Blue);
    obst[4].setPosition(sf::Vector2f(randX(lw), -570));

    obst[5].setOrigin(9,9);
    obst[5].setFillColor(sf::Color::Cyan);
    obst[5].setPosition(sf::Vector2f(randX(lw), -700));

    obst[6].setOrigin(14,14);
    obst[6].setFillColor(sf::Color::Green);
    obst[6].setPosition(sf::Vector2f(randX(lw), -840));

     obst[7].setOrigin(23,23);
    obst[7].setFillColor(sf::Color::Red);
    obst[7].setPosition(sf::Vector2f(randX(lw), -1000));

}


//moves walls left and right for testing
void Input(sf::RectangleShape& lw, sf::RectangleShape& rw, sf::CircleShape& obst, bool& fall,sf::CircleShape& player){

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

            //change color to match closest circle
            player.setFillColor(obst.getFillColor());
            lw.setFillColor(sf::Color::Blue);
            rw.setFillColor(sf::Color::Blue);

           //for some reason set angle to 0 if its above 2 pi both directions, even though Im adding like 80 to it every frame? it works though
          //if(angle > 1000 || angle < 1000){
          angle = 0;
        //}
        
        //if the obst is to the right, go clockwise, left, counterclockwise, since it will always check, use boolean to tell it to change or not

        //this part is not working- yes it is now
        if(clockwise){
        angle += .5*(CircleMath(obst)); //the  bigger this .1 value, the less it glitches out but the more the radius grows
        }
        
        else{
            angle -= .5*CircleMath(obst);
        }
        
        xVel = 3*cos(angle); //This breaks if you multipy it by an odd number ----- NOT TRUE any number over 4 breaks it
        yVel = 3*sin(angle);
        //std::cout << xVel << "   " << yVel << "\n";
        
        
        /* size of angle change determines radius of circle
        this will eventually be a function of the distance to whatever obstacle is closest

        the angle cant change by the distance between, it would be too big
         
         it could be .00125 times the distance for the correct radius? but why
         its not :(
        */
        } 
        else{
            lw.setFillColor(sf::Color::Red);
            rw.setFillColor(sf::Color::Red);
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


void GameOver(){
    std::cout << "Game Over\n";
bool restart = false;
std::cout << "Press Enter to Restart or q to quit\n";
    while(!restart){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            restart = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            quit = true;
            restart = true;
        }
    }
    
    
}

int randX(sf::RectangleShape lWall){
    return rand() %(winWidth -90) + (lWall.getPosition().x +10 ); 
}