package game;
import java.awt.Color;
import java.awt.Graphics;

public class EnemyPaddle implements Paddle
{
  double GRAVITY = 0.97;
  int width = 20; int height = 80;
  int x;
  double y, yVel;
  Ball ball;
//Constructor:  
  public EnemyPaddle(Ball b1)
  {
    x = 400;
    y = 195;
    yVel = 0;
    ball = b1;
  }
  //Componenet's Draw Duty For ea. Thread Update 
	@Override
	public void draw(Graphics g) 
	{
	  g.setColor(Color.RED.darker());
	  g.fillRect(x, (int)y, width, height);
	}
//AI Paddle Logic Will Adjust Its Y POS In Accordance To Ball w/ -40 buffer	
	@Override
	public void move() 
	{
      y = ball.getBallY() - 40;	  
      if (y < 5) {y = 5;}
      if (y > 365) {y = 365;}
	}
	@Override
	public int getY() {	return (int)y;}

}//End Class
