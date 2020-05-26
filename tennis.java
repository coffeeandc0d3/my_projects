package game;
import java.applet.Applet;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
//Will run Pong as an applet w/ Runnable, Keylistener 
//Creates Human and AI Paddle (From paddle interface) 
//Ball is separate class
//Thread process - init, run, update, draw, paint, bools for input

@SuppressWarnings("serial")
public class tennis extends Applet implements Runnable, KeyListener 
{
//Instance Components:
 final int WIDTH = 450; final int HEIGHT = 450; 
 PlayerPaddle p1;
 EnemyPaddle p2;
 Ball ball;
 Ball ball2;
 Thread gameLoop;

//Similar To 'Start()' Method in Unity 
 public void init() 
 {
  gameLoop = new Thread(this);
  ball = new Ball(1);
  ball2 = new Ball(2);
  p1 = new PlayerPaddle(1);
  p2 = new EnemyPaddle(ball);
  this.resize(WIDTH, HEIGHT);
  this.addKeyListener(this);
  gameLoop.start();
 }
 
 public void paint(Graphics g)
 {
 //Window:
   g.setColor(Color.BLACK.brighter());
   g.fillRect(0,0,WIDTH, HEIGHT);
 //Field Components Paint Duty (called on repaint later):  
   p1.draw(g);
   p2.draw(g);
   ball.draw(g);
   ball2.draw(g);
 }  
 
 public void update(Graphics g)
 {
   paint(g);
 }
//What Happens Every Single Frame Update:  
@Override
 public void run() 
 { 
    for (;;)
    {
      p1.move();
      ball.move();
      ball2.move();
      p2.move();
//Check For Paddle Collision W/ Ball
      ball.checkPaddleCollision(p1, p2);
      ball2.checkPaddleCollision(p1, p2);
      repaint();
      try {
        
    	Thread.sleep(6);
      } catch(InterruptedException e)
        {
          e.printStackTrace();
        }
                    
    } //End For Loop		
 }
//Player Input
@Override
 public void keyPressed(KeyEvent e) 
 {
	if (e.getKeyCode() == KeyEvent.VK_UP) 
	{
	  p1.setUpAccel(true); 
	}
	else if (e.getKeyCode() == KeyEvent.VK_DOWN) 
	 {
	   p1.setDownAccel(true); 
	 }
 }
 @Override
 public void keyReleased(KeyEvent e) 
 {
	if (e.getKeyCode() == KeyEvent.VK_UP) 
	{
	  p1.setUpAccel(false); 
	}
      if (e.getKeyCode() == KeyEvent.VK_DOWN) 
	 {
	   p1.setDownAccel(false); 
	 }
 }
//Unused: 
@Override
 public void keyTyped(KeyEvent arg0) 
 {
	// TODO Auto-generated method stub
	
 }
 
 
}//End Main Class