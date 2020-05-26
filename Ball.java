package game;
import java.awt.Color;
import java.awt.Graphics;

//Change x and y to int? 
public class Ball 
{
  int x, y;
  double xVel, yVel;
  int width = 20; int height = 20;

//Constructor  
  public Ball(int num)
 {
   if (num == 1)
   { 
     x = 205;
     y = 195;
     yVel = 1;
     xVel = -1;  
   } 
   else if (num == 2) 
   {
     x = 210;
     y = 190;
     xVel = 1;
     yVel = -1;
   }

 }//End Constructor 
public void move() 
 {
//Default Movement Vector  
   x += xVel;
   y += yVel;
//Bounds Collision For Ball (only the walls - paddle collision is separate) 
  if (y < 5) {yVel = -yVel;} 
  if (y > 435) {yVel = -yVel;}
  
//Wall Collision
  if (x > 445) {xVel = -xVel;}  
 } 
 //Paddle Collision W/ Ball
public void checkPaddleCollision(Paddle p1, Paddle p2) 
 { 
//If Ball is Horizontally In Proximity To Player Paddle, Check Y POS too 
   if (x <= 50) 
   {
     if (y >= p1.getY() && y <= p1.getY() + 80)
       {
         xVel = -xVel;
       }
//Enemy Paddle Collision
     else if (x >= 350)
       {
          if (y >= p2.getY() && y <= p2.getY() + 80)
          {
            xVel = -xVel; 
          }
       }
   }
 }//End Collision Function 

//Graphics Duty For Ball Component
public void draw(Graphics g)
    {
      g.setColor(Color.BLUE.brighter());
      g.fillOval(x, y, width, height);
    }
//Getters For Ball's Pos At Any Given Time   
public int getBallY() {return y;}
public int getBallX() {return x;}
    
}//End Class Ball
