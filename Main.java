import java.net.HttpURLConnection;
import java.net.URL;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.Thread;
import java.util.Scanner;

public class Main 
   {
	public static void main(String[] args) 
	{
	Scanner input = new Scanner(System.in);	
	String link = "";
	System.out.println("Input URL: ");
	link = input.nextLine();
	File out = new File("output");
	
	new Thread(new Downloader(link, out)).start();
	
	} 
}