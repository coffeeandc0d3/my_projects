//reverse int 
#include <iostream>
#include <string>

int reverse(int num) 
{ 
  string str = to_string(num); 
  string output = "";
   for (int i = str.find_last_of("0123456789"); i >= 0; --i)
   { 
      output += str.at(i); 
      if (i == 0) 
      {	 
         if (stoi(output) >= 2147483648 == false) 
         { 
            return stoi(output);
         }
       }
    }        
 return 0; 
}