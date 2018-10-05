/*Infor {{{
    > File Name: case.cpp
    > Author: samcompu
    > Mail: a1592710567@126.com
    > Website: https://www.samcompu.com
    > Created Time: 2018年09月18日 星期二 21时06分43秒
}}}*/
#include <bits/stdc++.h>

using namespace std;

/*Abbreviation {{{ */
#define FOR(i,a,b) for (int i = (int)(a); i <= (int)(b); i++)
#define ROF(i,a,b) for (int i = (int)(a); i >= (int)(b); i--)
#define FORLINE(i, t) for (int i = fi[t]; i; i = ne[i])
typedef long long ll;
typedef unsigned long long int ull;
/*}}}*/

/*Constant {{{*/
#define RESET "\033[0m" 
#define BOLDRED "\033[1m\033[31m" /* Bold Red */ 
/*}}}*/

/*Class {{{*/
/*}}}*/

/*Variable {{{*/
/*}}}*/

/*Declare {{{*/
/*}}}*/

/*Main {{{*/
int main() {
  ios::sync_with_stdio(false);
  cout << "Please enter the file name:";
  string fileName;
  cin >> fileName;
  string inFileName = fileName + ".in";
  string outFileName = fileName + ".out";
  cout << "Please enter the number of Test Data:";
  int testCase;
  cin >> testCase;
  string compileFile = "g++ -o " + fileName + " " + fileName + ".cpp";
  system(compileFile.data());
  for (int i = 0; i < testCase; i++) {
    string tInFileName = fileName + to_string(i) + ".in";
    string tOutFileName = fileName + to_string(i) + ".out";
    system("./born");
    string run = "./" + fileName;
    system(run.data());
    string moveInFile = "mv " + inFileName + " " + tInFileName;
    string moveOutFile = "mv " + outFileName + " " + tOutFileName;
    system(moveInFile.data());
    system(moveOutFile.data());
    cout << "Test Data " << BOLDRED << fileName << i << ".*" << RESET << " created successed!" << endl;
  }
  cout << "Do you need to create a floder and move all Test Data in?(y/n)";
  string choose;
  cin >> choose;
  if (choose[0] == 'y') {
    string clean = "rm -r " + fileName + " && mkdir " + fileName + " && mv *.in " + fileName + " && mv *.out " + fileName;
    system(clean.data());
    cout << "Create floder successed!" << endl;
  }
  cout << "Thanks for using. Made by samcompu." << endl;
  return 0;
}
/*}}}*/

/*Define {{{*/
/*}}}*/
