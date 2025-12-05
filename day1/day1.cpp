#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
  ifstream inputFile("d1.txt");
  int ans_1 = 0;
  int ans_2 = 0;
  int lock = 50;
  if(inputFile.is_open())
  {
    string line;
    while(getline(inputFile, line))
    {
      char prefix = line[0];
      line.erase(0,1);
      int num = stoi(line);
      ans_2 += num / 100;
      int rem = num % 100;
      for(int i=0; i<rem; ++i)
      {
        if(prefix == 'L')
        {
          lock--;
          if(lock < 0) lock = 99;
        }
        else
        {
          lock++;
          if(lock >= 100) lock = 0;
        }
        if(lock == 0)
        {
          ans_2++;
        }
      }
      if(lock == 0)
      {
        ans_1++;
      }
    }
  }
  cout << ans_1 << endl;
  cout << ans_2 << endl;
  return 0;
}
