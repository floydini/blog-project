#include<iostream>
#include<sys/socket.h>
#include<unistd.h>
#include<cstdlib>
#include<netinet/in.h>
#include<cstdio>
#include<cstring>
#include<sstream>
#include<fstream>

#include"mytcp.h"
using namespace std;

stringstream ss;
fstream ff;


void pack(char a[]) {
	int len;
	ss.clear();
	ss << strlen(a) - 1;
	ss >> len;
	char tmp[MAXLEN];
	sprintf(tmp, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n%s\n", len, a);
	strcpy(a, tmp);
}

void get_data(char a[], char b[]) {
	ff.clear();
	ff.open(a);
	ff.seekg(0, std::ios::end);
	int len = ff.tellg();
	ff.seekg(0, std::ios::beg);
	ff.read(b, len);
	ff.close();
}


#ifndef MAXLEN
#define MAXLEN 4096
#endif

char a[MAXLEN], b[MAXLEN];

int main() {

	strcpy(a, "helloworld!!!");
	pack(a);

	TCP server(8080);

	while (server.ac()) {
		server.in(b);
		cout << "receive :\n" << b;
		server.out(a);
	}
	return 0;
}