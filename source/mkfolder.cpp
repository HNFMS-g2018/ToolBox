/*Infor {{{
    > File Name: mkfolder.cpp
    > Author: samcompu
    > Mail: a1592710567@126.com
    > Website: https://www.samcompu.com
    > Created Time: 2018年08月24日 星期五 10时48分17秒
    > Usage: 自动生成和 Cpp 文件对应的文件夹
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
/*}}}*/

/*Class {{{*/
/*}}}*/

/*Variable {{{*/
string name;
/*}}}*/

/*Declare {{{*/
/*}}}*/

/*Main {{{*/
int main() {
  ios::sync_with_stdio(false);
  system("ls | grep .cpp > .file.list");
  ifstream fin(".file.list");
  while (fin >> name) {
    string s;
    FOR(i, 0, name.size() - 1) {
      if (name.at(i) == '.') break;
      s.push_back(name.at(i));
    }
    string command0 = "rm " + s;
    string command1 = "mkdir " + s;
    string command2 = "cp " + name + " " + s;
    ifstream have(s.data());
    if (have) {
      have.close();
      system(command0.data());
    } else have.close();
    system(command1.data());
    system(command2.data());
  }
  return 0;
}
/*}}}*/

/*Define {{{*/
/*}}}*/
