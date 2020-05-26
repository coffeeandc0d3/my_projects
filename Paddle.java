package game;
import java.awt.Graphics;

//What Does A Paddle Need In reference to the screen? 

 public interface Paddle 
 {
    public void draw(Graphics g);   
    public void move();
    public int getY();

 }
