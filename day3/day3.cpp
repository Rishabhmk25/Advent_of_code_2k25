#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

long long int joltage(vector<int> v)
{
  vector<int> d(12);
  int n = 12;
  long long int ans = 0;
  int index = 0;
  for(int i = 0; i < 12; i++)
  {
    int a = *max_element(v.begin()+index, v.end()-11+i);
    auto it = find(v.begin()+index, v.end(), a);
    index = it - v.begin() + 1;
    //cout << a << " " << index << endl;
    d.push_back(a);
  }
  for(int c: d)
  {
    ans *= 10;
    ans += c;
  }
  //cout << "ans " << ans << endl; 
  return ans;
}

int main()
{
  ifstream inputFile("d3.txt");
  int ans_1 = 0;
  int long long ans_2 = 0;
  if(inputFile.is_open())
  {
    string bank;
    while(getline(inputFile, bank))
    {
      vector<int> batteries;
      for(char batteri: bank)
      {
        int battery = batteri - '0';
        batteries.push_back(battery);
      }
      int max_1 = *max_element(batteries.begin(), batteries.end() - 1);
      auto it = find(batteries.begin(), batteries.end(), max_1);
      int index = it - batteries.begin();
      int max_2 = *max_element(batteries.begin() + index + 1, batteries.end());
      ans_1 += max_1*10 + max_2;
      ans_2 += joltage(batteries);
    }
  }
  cout << ans_1 << endl;
  cout << ans_2 << endl;
  return 0;
}
