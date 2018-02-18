#include<map>
#include<cstdlib>
#include<regex>
#include<iostream>
#include<sstream>
#include<fstream>

#include"Type.h"

#include"conf.h"

stringstream ss;
fstream ff;

void pack(char* type, char *head, char* data, int len) {
	char* state =  Status_Code.find((len == 0) ? 404 : 200)->second;
	cout << "\n\nsend {\n";
	cout << "	HTTP_Version :" << HTTP_Version << endl;
	cout << "	state :" << state << endl;
	cout << "	Content_Type :" << type << endl;
	cout << "	Content_Length :" << len << endl;
	cout << "}\n";
	sprintf(head, "%s %s\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", HTTP_Version, state, type, len);
}

int get_data(bool isBinary, char a[], char b[]) {
	cout << "isBinary = " << isBinary << endl;
	cout << "ff.open(" << a << ")\n";
	if (isBinary) ff.open(a, ios::in | ios::binary | ios::app);
	else ff.open(a);
	ff.seekg(0, std::ios::end);
	int len = ff.tellg();
	if (len > 0) {
		ff.seekg(0, std::ios::beg);
		ff.read(b, len);
	} else strcpy(b, " ");

	ff.close();
	return len;
}

bool IsBinary(char *type) {
	return strcmp(type, (char*)"image/gif" ) == 0 ||
	       strcmp(type, (char*)"image/jpeg") == 0 ||
	       strcmp(type, (char*)"image/png" ) == 0 ;
}

void add(int a, int b) {
	ff.open("website/add.html", ios::out | ios::trunc);
	ff.close();
	ff.open("website/add.html");
	ff << a << " + " << b << " = " << a + b << endl;
	cout << a << " + " << b << " = " << a + b << endl;
	ff.close();
}

int get_content(char *req, char* head, char* data) {
	char method[32] = "", filename[1024];
	char* type = (char*)"";
	ss.str("");
	ss.clear();
	ss << req;
	ss >> method;
	if (strcmp(method, "GET") == 0) {
		ss >> filename;
		{
			//this is temporary.
			int tmp = strlen(filename);
			for (int i = 0; i < tmp; i++) {
				if (filename[i] == '?') {
					filename[i] = '\0';
					break;
				}
			}
		}

		cmatch cm, cm_add;
		regex re("(.*)\\.(.*)"), re_add("/add/([0-9]+)/([0-9]+)");
		if (strcmp(filename, "/") == 0) strcpy(filename, "/index.html");
		else if (regex_match(filename, cm_add, re_add)) {
			int a1, a2;
			ss.str("");
			ss.clear();
			cout << cm_add.str(1) << " | " << cm_add.str(2) << endl;
			ss << cm_add.str(1) << " " << cm_add.str(2);
			ss >> a1 >> a2;
			add(a1, a2);
			strcpy(filename, "/add.html");
		}

		if (regex_match(filename, cm, re)) {
			string tt = cm.str(2);
			type = Content_Type.find(tt)->second;
		} else type = (char*)"text/plain";
		cout << "type = " << type << endl;
		ss.str("");
		ss.clear();
		ss << path << filename;
		ss >> filename;
	} else if (strcmp(method, "POST") == 0) {
		//TODO
		cout << "method POST !\n";
		cout << req << endl;
	} else cout << "Should not reach here ! (method : " << method << ")\n";

	cout << "filename = " << filename << endl;
	int len = get_data(IsBinary(type), filename, data);
	pack(type, head, data, len);
	return len;
}
