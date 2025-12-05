#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

vector<string> split_string(const string& string_of_ranges, char delimeter)
{
  vector<string> tokens;
  string token;
  istringstream tokenStream(string_of_ranges);
  while(getline(tokenStream, token, delimeter))
  {
    tokens.push_back(token);
  }
  return tokens;
}

bool check(const long int& num)
{
  int count = floor(log10(num)) + 1;
  long int power = count / 2;
  long int power_of_ten = pow(10, power);
  long int left_half = num/power_of_ten;
  long int right_half = num%power_of_ten;
  if(right_half == left_half && count%2 == 0)
  {
    return true;
  }
  return false;
}

bool check_1(const long int& num)
{
  string num_string = to_string(num);
  string t = num_string + num_string;
  t = t.substr(1, t.size() - 2);
  return t.find(num_string) != string::npos;
}

int main()
{
  ifstream inputFile("d2.txt");
  long long int ans_1 = 0;
  long long int ans_2 = 0;
  if(inputFile.is_open())
  {
    string line;
    while(getline(inputFile, line))
    {
      char delimeter = ',';
      vector<string> ranges = split_string(line, delimeter);
      for(const string& range: ranges)
      {
        vector<string> interval = split_string(range, '-');
        //cout << interval[0] << endl;
        long long int a = stoll(interval[0]);
        //cout << interval[1] << endl;
        long long int b = stoll(interval[1]);
        //cout << a << " " << b << endl;
        for(long long int i = a; i <= b; i++)
        {
          if(check(i))
          {
            ans_1 += i;
            //cout << i << endl;
          }
          if(check_1(i))
          {
            ans_2 += i;
            cout << i << endl;
          }
        }
      }
    }
  }
  cout << ans_1 << endl;
  cout << ans_2 << endl;
  return 0;
}
