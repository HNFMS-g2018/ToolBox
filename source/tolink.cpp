#include <bits/stdc++.h>

using namespace std;
typedef string PATH;
#define rep(i, a, b) for (int i = (int)a; i <= (int)b; i++)

class Link {
	public:
		bool deleted;
		string name; PATH path;
};

namespace SURVICE {
	PATH HOME; // The path of home dir.
/* Functions {{{*/
	void init(void); // Get the HOME path.
	void bash_run(string); // Give a command and run in bash.
	void show_wrong(string); // Show 'Error', give the error code and quit.
	void install(); // Install the application into the computer
	void uninstall(); // Uninstall the application from the computer
	bool check_path(string); // Check if there is the designated path.
	bool check_address(string); // Check if it is a legal website address.
	string to_string(char *); // Trun char array to string
	string read_path(void); // Read in a path (Will turn '~' to home path).
	string expand_user(string); // Expand '~' to the home path.
/* }}} */
}

namespace PROGRAM {
	PATH configFile; // The path of config file.
	vector<Link>link; // All the link
	string defaltBrowser; // The defalt browser for opening the link.
	/* Functions {{{ */
	void init(void); // Get the config file path.
	void read_config(void); // Read the config from the config file.
	void write_config(void); // Write the infor into the config file.
	void show_help(void); // Show program's help.
	void welcome(void); // A welcome guide for the first time .
	void add_link(Link); // Add the designated link.
	void list_link(); // List all the added link.
	void del_link(string); // Delete the designated path.
	void open_web(string); // Open the designated web address in browser
	void change_browser(string); // Change the defalt browser
	void open_link(string); // Open the saved link or designated link
	bool start_test(void); // Start https://www.samcompu.com to check the browser
	int get_id(string); // Find the link by the string
	int find_link(string); // Check if the link is exist and return its ID.
	/* }}} */
}

void quit(void); // Quit the application with some necessary operating.

int main(int argc, char* argv[]) {
	SURVICE::init();
	PROGRAM::init();
	if (argc == 1) {
		PROGRAM::list_link();
		quit();
	}
	string parameter = SURVICE::to_string(argv[1]);
	if (parameter == "-a" || parameter == "--add") {
		if (argc == 2) PROGRAM::add_link((Link) {false, "", ""});
		else if (argc == 4) PROGRAM::add_link((Link) {false, SURVICE::to_string(argv[2]), SURVICE::to_string(argv[3])});
		else SURVICE::show_wrong("0001");
	} else if (parameter == "-c" || parameter == "--change") {
		if (argc == 2) PROGRAM::change_browser("");
		else if (argc == 3) PROGRAM::change_browser(SURVICE::to_string(argv[2]));
		else SURVICE::show_wrong("0001");
	} else if (parameter == "-d" || parameter == "--delete") {
		if (argc == 2) PROGRAM::del_link("");
		else if (argc == 3) PROGRAM::del_link(SURVICE::to_string(argv[2]));
		else SURVICE::show_wrong("0001");
	} else if (parameter == "-h" || parameter == "--help") {
		if (argc == 2) PROGRAM::show_help();
		else SURVICE::show_wrong("0001");
	} else if (parameter == "-i" || parameter == "--install") {
		if (argc == 2) SURVICE::install();
		else SURVICE::show_wrong("0001");
	} else if (parameter == "-l" || parameter == "--list") {
		if (argc == 2) PROGRAM::list_link();
		else SURVICE::show_wrong("0001");
	} else if (parameter == "-u" || parameter == "--uninstall") {
		if (argc == 2) SURVICE::uninstall();
		else SURVICE::show_wrong("0001");
	} else {
		if (argv[1][0] == '-') SURVICE::show_wrong("0003");
		if (argc != 2) SURVICE::show_wrong("0001");
		PROGRAM::open_link(SURVICE::to_string(argv[1]));
	}
	quit();
	return 0;
}

void quit(void) {
	PROGRAM::write_config();
	exit(0);
}

/* SURVICE {{{ */
bool SURVICE::check_path(string s) {
	ifstream fin(s.data());
	bool ok = !fin;
	fin.close();
	return !ok;
}

bool SURVICE::check_address(string s) { return !min(min(s.find("http://", 0), s.find("https://", 0)), s.find("ftp://", 0)); }

void SURVICE::init(void) { SURVICE::HOME = getenv("HOME"); }

void SURVICE::show_wrong(string code) { 
	cout << "Something went wrong!" << endl << "Error code: " << code << endl << "You can use '-h' to know why." << endl; 
	quit();
}

string SURVICE::expand_user(string s) {
	if (s.at(0) == '~') s.replace(0, 1, SURVICE::HOME);
	return s;
}

string SURVICE::read_path(void) {
	string path;
	cin >> path;
	return SURVICE::expand_user(path);
}

void SURVICE::bash_run(string s) { system(s.data()); }


string SURVICE::to_string(char *c) {
	string s = c;
	return s;
}

void SURVICE::install() {
	SURVICE::bash_run("sudo cp tolink /usr/bin");
}

void SURVICE::uninstall() {
	SURVICE::bash_run("sudo rm /usr/bin/tolink");
}
/* }}} */

/* PROGRAM {{{ */
void PROGRAM::init(void) {
	string configPath = SURVICE::HOME + "/.config/tolink";
	if (!SURVICE::check_path(configPath)) {
		SURVICE::bash_run("mkdir " + configPath);
		if (!SURVICE::check_path(configPath)) SURVICE::show_wrong("0002");
	}
	PROGRAM::configFile = SURVICE::HOME + "/.config/tolink/init.cfg";
	if (!SURVICE::check_path(PROGRAM::configFile)) PROGRAM::welcome();
	else PROGRAM::read_config();
}

void PROGRAM::show_help(void) {
	cout << 
"'tolink' can open the designated or saved link in the browser." << endl << endl <<
"Usage: " << endl << 
"  tolink <ID>/<name>      Open the saved link by its ID or name" << endl <<
"  tolink [options]        Change or show the saved information" << endl << 
"  tolink <path>           Open the designated link" << endl << endl <<
"Options: " << endl << 
"  -a, -a <name> <path>    Add new address with the unique name" << endl <<
"      --add" << endl <<
"  -c, -c <browser>        Change the defalt browser" << endl << 
"      --change" << endl << 
"  -d, -d <ID>/<name>      Delete the address by its ID and name" << endl << 
"      --delete" << endl <<
"  -h                      Show help" << endl <<
"      --help" << endl << 
"  -i                      Install 'tolink' into the computer" << endl <<
"      --install" << endl <<
"  -l                      List the all the address with its ID and name" << endl <<
"      --list" << endl << 
"  -u                      Uninstall 'tolink' from the computer" << endl <<
"      --uninstall" << endl << endl <<
"Error code: " << endl <<
"  0001      Too much or too less parameter" << endl << 
"  0002      Can't create or write the config file" << endl <<
"  0003      No such '-' options" << endl <<
"  0004      Illegal website address" << endl << 
"  0005      No such name or ID" << endl << 
"  0006      Already have the name" << endl << endl <<
"Report bugs to email: admin@samcompu.com" << endl;
}

bool PROGRAM::start_test(void) {
	string c;
	PROGRAM::open_web("https://www.samcompu.com");
	cout << "Have you open 'https://www.samcompu.com'? (y/n)";
	cin >> c;
	return c != "n";
}

void PROGRAM::welcome(void) {
	string c = "n";
	cout << "Welcome to use 'tolink'!" << endl << "This is the first time you run this application!" << endl;
	while (c == "n") {
		cout << "Please set your defult browser first: ";
		cin >> PROGRAM::defaltBrowser;
		cout << "Now start your defult browser for checking if is useable." << endl;
		cout << "Type 'y' for starting checking or 'n' for changing defult browser:";
		cin >> c;
	}
	while (!PROGRAM::start_test()) {
		cout << "Sorry about that! It means 'tolink' doesn't support this browser." << endl;
		cout << "Please set another browser: ";
		cin >> PROGRAM::defaltBrowser;
	}
	cout << "Congratulations! You can't use 'tolink' now!" << endl << endl;
}

void PROGRAM::write_config(void) {
	ofstream fout(PROGRAM::configFile);
	if (!fout) SURVICE::show_wrong("0002");
	fout << "[Links]" << endl;
	rep(i, 0, PROGRAM::link.size() - 1) {
		Link t = PROGRAM::link.at(i);
		if (t.deleted) continue;
		fout << t.name << " " << t.path << endl;
	}
	fout << endl;
	fout << "[Defalt Browser]" << endl << PROGRAM::defaltBrowser << endl;
	fout.close();
}

void PROGRAM::add_link(Link t) { 
	if (t.name == "") {
		cout << "Link name: ";
		cin >> t.name;
	}
	if (t.path == "") {
		cout << "Link path: ";
		cin >> t.path;
	}
	rep(i, 0, PROGRAM::link.size() - 1) {
		Link have = PROGRAM::link.at(i);
		if (have.name == t.name) SURVICE::show_wrong("0006");
	}
	if (!SURVICE::check_address(t.path)) SURVICE::show_wrong("0004");
	PROGRAM::link.push_back(t); 
}

void PROGRAM::read_config() {
	ifstream fin(PROGRAM::configFile);
	string s;
	fin >> s;
	while (1) {
		Link t;
		t.deleted = false;
		fin >> s, t.name = s;
		fin >> s, t.path = s;
		if (t.name == "[Defalt" && t.path == "Browser]") break;
		if (!SURVICE::check_address(t.path)) {
			cout << "----" << "Wronging: Some config files has been changed artificial." << endl << "You'd better have a check." << "----" << endl;
			continue;
		}
		PROGRAM::link.push_back(t);
	}
	fin >> PROGRAM::defaltBrowser;
	fin.close();
}

void PROGRAM::list_link() {
	if (!PROGRAM::link.size()) {
		cout << "You don't have any link now!" << endl << "Use '-a' to add one." << endl;
		return ;
	}
	cout << "Link list:" << endl;
	rep(i, 0, PROGRAM::link.size() - 1) {
		Link t = PROGRAM::link.at(i);
		cout << "  " << i << "  " << t.name << "  " << t.path << endl;
	}
}

void PROGRAM::del_link(string s) {
	if (s == "") {
		cout << "Pleace enter the id or name of the link: ";
		cin >> s;
	}
	PROGRAM::link.at(PROGRAM::get_id(s)).deleted = true;
}

int PROGRAM::get_id(string s) {
	rep(i, 0, PROGRAM::link.size() - 1) {
		Link t = PROGRAM::link.at(i);
		if (t.name == s) return i;
	}
	rep(i, 0, s.size() - 1) {
		if (s.at(i) < '0' || s.at(i) > '9') SURVICE::show_wrong("0005");
	}
	int id = stoi(s);
	if (id >= (int) PROGRAM::link.size()) SURVICE::show_wrong("0005");
	return id;
}

void PROGRAM::open_web(string s) {
	SURVICE::bash_run(PROGRAM::defaltBrowser + " " + s);
}

void PROGRAM::change_browser(string s) {
	if (s == "") {
		cout << "Please enter the browser you want to change to: ";
		cin >> s;
	}
	PROGRAM::defaltBrowser = s;
}

int PROGRAM::find_link(string s) {
	rep(i, 0, PROGRAM::link.size() - 1) {
		Link t = PROGRAM::link.at(i);
		if (t.path == s) return i;
	}
	return -1;
}

void PROGRAM::open_link(string s) {
	if (SURVICE::check_address(s)) {
		PROGRAM::open_web(s);
		int id = PROGRAM::find_link(s);
		if (id == -1) {
			string c;
			cout << "You haven't saved this link before. Save it? (y/n)";
			cin >> c;
			if (c != "n") PROGRAM::add_link((Link) {false, "", s});
		} else {
			Link t = PROGRAM::link.at(id);
			cout << "You have saved this link before." << endl << "You can use 'tolink " << t.name << "' to open it next time.";
		}
	}
	else PROGRAM::open_web(PROGRAM::link.at(PROGRAM::get_id(s)).path);
}
/* }}} */
