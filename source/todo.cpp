/*Infor {{{
    > File Name: todo.cpp
    > Author: samcompu
    > Mail: a1592710567@126.com
    > Website: https://www.samcompu.com
    > Created Time: 2018年08月22日 星期三 17时14分50秒
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
class DATE {
  public:
    int year;
    int month;
    int day;
    static DATE makeDATE(int);
    friend ostream& operator << (ostream&, DATE&);
    int data();
};

class THING {
  public:
    THING() {
      name = "";
      description = "";
      beDeleted = false;
    }
    string name;
    DATE date;
    string description;
    bool beDeleted;
    static THING makeTHING(string, DATE, string, bool);
};

class TODO {
  public:
    void init();
    void show();
    void add();
    void find();
    void del();
    void save();
};

class SERVICE {
  public:
    SERVICE() {
      version = 1.1;
      update = (DATE) {2018, 10, 05};
      author = "Samcompu";
    }
    void help();
    void wrong();
    void infor();
  private:
    int version;
    DATE update;
    string author;
};
/*}}}*/

/*Variable {{{*/
vector<THING>thing;
TODO todo;
SERVICE service;
/*}}}*/

/*Declare {{{*/
int getTime();
/*}}}*/

/*Main {{{*/
int main(int argc, char* argv[]) {
  ios::sync_with_stdio(false);
  if (argc == 1) service.infor();
  else if (argc > 2) service.wrong();
  else {
    string command = argv[1];
    todo.init();
    if (command[0] == 'v' || command == "version") service.infor();
    if (command[0] == 'h' || command == "help") service.help();
    if (command[0] == 's' || command == "show") todo.show();
    if (command[0] == 'a' || command == "add") todo.add();
    if (command[0] == 'f' || command == "find") todo.find();
    if (command[0] == 'd' || command == "delete") todo.del();
  }
  return 0;
}
/*}}}*/

/*Define {{{*/
/*function: getTime() {{{*/
int getTime() {
 time_t tt = time(NULL);
 tm* t= localtime(&tt);
 int ans = (t->tm_year + 1900) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday;
 return ans;
}
/*}}}*/

/*class: DATE{{{*/
ostream& operator << (ostream& output, DATE& c) {
  output << c.year << "-" << c.month << "-" << c.day;
  return output;
}

DATE DATE::makeDATE(int t) {
  DATE ans = (DATE) {t / 10000, (t / 100) % 100, t % 100};
  return ans;
}

int DATE::data() {
  return year * 10000 + month * 100 + day;
}
/*}}}*/

/*class: THING{{{*/
THING THING::makeTHING(string p1, DATE p2, string p3, bool p4) {
  THING t;
  t.name = p1;t.date = p2;t.description = p3;t.beDeleted = p4;
  return t;
}
/*}}}*/

/*class: TODO{{{*/
/*function: init() {{{*/
void TODO::init() {
  ifstream fin(".todo.thing");
  if (!fin) system("echo "" > .todo.thing");
  THING t;
  int d;
  while (fin >> t.name >> d >> t.description) {
    t.date = DATE::makeDATE(d);
    thing.push_back(t);
  }
  fin.close();
}
/*}}}*/
/*function: show() {{{*/
void TODO::show() {
  cout << "You have " << thing.size() << " thing" << (thing.size() > 1 ? "s" : "") << " to do:" << endl;
  FOR(i, 0, thing.size() - 1) {
    THING t = thing[i];
    cout << "(" << i + 1 << ") " << "[" << t.date << "] " << t.name << " {" << t.description << "}" << endl;
  }
  exit(0);
}
/*}}}*/
/*function: add() {{{*/
void TODO::add() {
  string name = "", des = "";
  while (name.size() == 0) {
    cout << "Please input the name for this thing:";
    cin >> name;
  }
  while (des.size() == 0) {
    cout << "Please input the description for this thing:";
    cin >> des;
  }
  THING t = THING::makeTHING(name, DATE::makeDATE(getTime()), des, false);
  thing.push_back(t);
  this->save();
  cout << "Add success!" << endl;
  cout << endl;
}
/*}}}*/
/*function: find() {{{*/
void TODO::find() {
  cout << "Sorry! We don't export 'find' now!" << endl;
}
/*}}}*/
/*function: del() {{{*/
void TODO::del() {
  int id = 0;
  while (id == 0) {
    cout << "Please input the id of this thing(You can use 'show' to know that):";
    cin >> id;
  }
  thing.at(id - 1).beDeleted = true;
  this->save();
  cout << "Delete seccess!" << endl;
}
/*}}}*/
/*function: save() {{{*/
void TODO::save() {
  int id = 0;
  ofstream fout(".todo.thing");
  FOR(i, 0, thing.size() - 1) {
    THING t = thing.at(i);
    if (t.beDeleted) continue;
    fout << t.name << " " << t.date.data() << " " << t.description << endl;
  }
  fout.close();
}
/*}}}*/
/*}}}*/

/*SERVICE {{{*/
void SERVICE::help() {
  cout << "Usage: todo <command> [<parameter>]" << endl;
  cout << endl;
  cout << "Commands:" << endl;
  cout << "\tversion" << endl;
  cout << "\tadd" << endl;
  cout << "\tfind" << endl;
  cout << "\tdelete" << endl;
  cout << "\tshow" << endl;
  cout << "\thelp" << endl;
}

void SERVICE::wrong() {
  cout << "Please check what you type or type 'help' to know how to use it." << endl;
}

void SERVICE::infor() {
  cout << "todo v" << version << "." << update.month << "." << update.day << endl;
  cout << "Power by " << author << endl;
  cout << endl;
  cout << "Use 'help' to know more about this" << endl;
}
/*}}}*/
/*}}}*/
