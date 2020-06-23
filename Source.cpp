#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
void dumphex(const vector<char>& v);

int main() 
{ 
    //<README> change "below" to name of file (preferrably in current path) 
    ifstream file("", ios::binary | ios::ate);  
    int size = file.tellg();
    file.seekg(0, ios::beg);
    vector<char> buffer;
    buffer.resize(size); // << resize not reserve
    file.read(buffer.data(), size);

    dumphex(buffer);

  return 0; 
}

void dumphex(const vector<char>& hexVector)
{
    const int bits = 16;
    const char hex[] = "0123456789ABCDEF";
    char buf[bits * 4 + 5 + 2];
    for (int i = 0; i < hexVector.size(); ++i)
    {
        int n = i % bits;
        if (n == 0)
        {
            if (i)
                puts(buf);
            memset(buf, 0x20, sizeof(buf));
            buf[sizeof(buf) - 2] = '\n';
            buf[sizeof(buf) - 1] = '\0';
        }
        unsigned char c = (unsigned char)hexVector[i];
        buf[n * 3 + 0] = hex[c / 16];
        buf[n * 3 + 1] = hex[c % 16];
        buf[3 * bits + 5 + n] = (c >= ' ' && c <= '~') ? c : '.';
    }
    puts(buf);
}