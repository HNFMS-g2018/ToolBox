/*Infor {{{
    > File Name: c.cpp
    > Author: samcompu
    > Mail: a1592710567@126.com
    > Website: https://www.samcompu.com
    > Created Time: 2018年08月24日 星期五 11时12分40秒
    > Usage: 批量编译 C++ 文件
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
class NAME {
  public:
    string fullName;
    string fileName;
};
/*}}}*/

/*Variable {{{*/
string choose;
vector<NAME>file;
/*}}}*/

/*Declare {{{*/
void Compile(NAME);
void ShowWrong();
void ShowHelp();
void init();
/*}}}*/

/*Main {{{*/
int main(int argc, char* argv[]) {
  ios::sync_with_stdio(false);
  init();
  if (argc == 1) {
    vector<NAME>need;
    cout << "Compile all or compile part of this?[a/p]";
    cin >> choose;
    if (choose.at(0) == 'a') {
      FOR(i, 0, file.size() - 1) Compile(file.at(i));
    }
    else {
      FOR(i, 0, file.size() - 1) {
        NAME t = file.at(i);
        cout << "Do you want to compile " << t.fullName << "?[y/n]";
        cin >> choose;
        if (choose.at(0) == 'n' || choose.at(0) == 'N') continue;
        need.push_back(t);
      }
      FOR(i, 0, need.size() - 1) Compile(need.at(i));
    }
  } else {
    if (argv[1][0] == '-' && argv[1][1] == 'h') {
      ShowHelp();
      return 0;
    }
    FOR(i, 1, argc - 1) {
      string need = argv[i];
      int f = -1;
      FOR(j, 0, file.size() - 1) {
        NAME t = file.at(j);
        if (t.fullName == need || t.fileName == need) f = j;
      }
      if (f == -1) cout << "Sorry! Can't find file " << BOLDRED << need << RESET << "." << endl;
      else Compile(file.at(f));
    }
  }
  return 0;
}
/*}}}*/

/*Define {{{*/
void ShowHelp() {
  cout << "Usage:" << endl;
  cout << "\tJust use 'c' to compile C++ or C file everywhere." << endl;
}

void Compile(NAME t) {
  string command0 = "g++ -o " + t.fileName + " " + t.fullName + " -g -W";
  system(command0.data());
  cout << "Compile " << BOLDRED << t.fullName << RESET << " successfully." << endl;
}

void ShowWrong() {
  cout << "Please check what you type or use '-h' to know how to use this." << endl;
  exit(0);
}

void init() {
  system("ls | grep .cpp > .file.list");
  ifstream fin(".file.list");
  string name;
  while (fin >> name) {
    string s;
    FOR(i, 0, name.size() - 1) {
      if (name.at(i) == '.') break;
      s.push_back(name.at(i));
    }
    file.push_back((NAME) {name, s});
  }
  fin.close();
  system("rm .file.list");
}
/*}}}*/
