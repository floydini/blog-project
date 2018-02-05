#include<map>
#include<cstdlib>
#include<regex>
#include<iostream>
#include<sstream>
#include<fstream>

#define SP " "
#define CRLF "\r\n"

#ifndef MAXLEN
#define MAXLEN 1048576
#endif

stringstream ss;
fstream ff;


const char* HTTP_Version = "HTTP/1.1";
const char* path = "website";
const map<int, char*> Status_Code = {
	{200, (char*)"200 OK"},
	{404, (char*)"404 Not Found"},
	{503, (char*)"503 Service Unavailable"}
};

const map<string, char*> Content_Type = {
	{"html"	, (char*)"text/html"},
	{"plain", (char*)"text/plain"},
	{"xml"	, (char*)"text/xml"},
	{"css"	, (char*)"text/css"},
	{"gif"	, (char*)"image/gif"},
	{"jpeg"	, (char*)"image/jpeg"},
	{"png"	, (char*)"image/png"},
	{"ico"	, (char*)"image/x-icon"}
};

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
	ff.open("website/add.html");
	ff << a << " + " << b << " = " << a + b << endl;
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
		cmatch cm;
		regex re("(.*)\\.(.*)");
		if (strcmp(filename, "/") == 0) strcpy(filename, "/index.html");
		/*		else if (strcmp(filename, "/add/([0-9]+)/([0-9]+)") == 0) {
					strcpy(filename, "/add.html");
					add(stoi(cm[1]), stoi(cm[2]));
				} */

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
	} else cout << "Should not reach here ! (method : " << method << ")\n";

	cout << "filename = " << filename << endl;
	int len = get_data(IsBinary(type), filename, data);
	pack(type, head, data, len);
	return len;
}


// class Response {
//   private:
// 	char *filename;
// 	char *filetype;
//   public:
// 	Response() {
// 		HTTP_Version["0"] = "HTTP/1.1";

// 		Status_Code["OK"] = "200 OK";
// 		Status_Code["NF"] = "404 Not Found";
// 		Status_Code["NA"] = "406 Not Acceptable";
// 		Status_Code["SU"] = "503 Service Unavailable";

// 		Reason_Phrase[""]
// 	};
// 	void name(char *file) {
// 		strcpy(filename, file);
// 	}
// 	char *Content_Type() {
// 		int sz = strlen(filename);
// 		while (sz > 0 && filename[sz - 1] != '.') sz--;
// 		char * suffix = filename + sz;
// 		switch (suffix) {
// 		case "jpeg": 	{filetype = "image/jpeg"; break;}
// 		case "png": 	{filetype = "image/png"; break;}
// 		default: 		{filetype = "application/octet-stream"; break;}
// 		}
// 	}

// 	void get_data(char b[]) {
// 		ff.open(filename);
// 		ff.seekg(0, std::ios::end);
// 		int len = ff.tellg();
// 		if (len > 0) {
// 			ff.seekg(0, std::ios::beg);
// 			ff.read(b, len);
// 		} else strcpy(b, " ");

// 		ff.close();
// 	}


// 	char *Content_Length(char *filename) {

// 	}

// 	~Response();

// };

