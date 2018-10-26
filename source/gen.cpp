#include <bits/stdc++.h>

using namespace std;
 
#define L_RED "\e[1;31m"
#define L_GREEN "\e[1;32m"
#define NONE "\e[0m"

bool have_file(string);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Too many to too less parameter for this command. (You just need to enter one parameter)" << endl;
    return 0;
  }
  if (!have_file("born.cpp") || !have_file("std.cpp")) {
    cout << "Please first put the file " << L_RED << "'born.cpp'" << NONE << " and " << L_RED << "'std.cpp'" << NONE << " here and then run this command." << endl;
    return 0;
  }
  if (!have_file("born")) {
    cout << "Compiling " << L_RED << "born.cpp" << NONE << " ......" << endl;
    system("g++ -o born born.cpp");
  }
  if (!have_file("std")) {
    cout << "Compiling " << L_RED << "std.cpp" << NONE << " ......" <<endl;
    system("g++ -o std std.cpp -O2");
  }
  int caseNum;
  sscanf(argv[1], "%d", &caseNum);
  string getIn, getOut;
  for (int i = 1; i <= caseNum; i++) {
#ifdef linux
    getIn = "./born " + to_string(i);
    getOut = "./std " + to_string(i);
#endif
#ifndef linux
    getIn = "born.exe " + to_string(i);
    getOut = "std.exe " + to_string(i);
#endif
    system(getIn.data());
    system(getOut.data());
    cout << "Success born " << L_GREEN << "Test Case #" << i << NONE << endl;
  }
	cout << endl;
	cout << "All success! Welcome to use next time" << endl;
  return 0;
}

bool have_file(string name) {
  ifstream file(name);
  bool have = false;
  if (file) have = true;
  else have = false;
  file.close();
  return have;
}
