package game;
import java.awt.Color;
import java.awt.Graphics;

public class PlayerPaddle implements Paddle
{
//Attributes of Paddle In Position and Speed
  double GRAVITY = 0.97;
  int width = 20; int height = 80;
  int x, player;
  double y, yVel;
  boolean upAccel, downAccel;
//Constructor:   
   public PlayerPaddle(int num)
   {
     player = num;
      if (num == 1)
      {
        x = 25;
        y = 195;
        yVel = 0;
      }
      
   }//End Constructor 
 @Override
  	 public void draw(Graphics g) 
 	 {
 	   g.setColor(Color.green.darker());
       g.fillRect(x, (int)y, width, height);				
	 }
 @Override
	public void move() 
	{
	  if (upAccel == true)
	  {
	 	yVel -= 2;  	 
	  } else if (downAccel == true)
	   {
		yVel += 2; 
	   } else if (!downAccel && !upAccel)
	    {
		yVel *= GRAVITY;    
		   
	    }
//Movement "Vector"   
      y += yVel;
//Stops from exponentiating speed & component off the screen	
	  if (yVel > 2)
	   {
	    yVel = 2;
	   } else if (yVel < -2)
	     {
	       yVel = -2;   
	     }	
//Bounds Collision:  
	  if (y < 5) {y = 5;} 
	  if (y > 365) {y = 365;}
	}//End Move Function
	 
 //Setters For Key Presses On This Component	
  public void setUpAccel(boolean input)
  {
   upAccel = input;	
  }
  public void setDownAccel(boolean input)
  {
    downAccel = input;
  }	
//Getter For Player's Y POS 
public int getY() {return (int)y;}

}//End Class
