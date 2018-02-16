#include<iostream>
#include<sys/socket.h>
#include<unistd.h>
#include<cstdlib>
#include<netinet/in.h>
#include<cstdio>
#include<cstring>
#include<sstream>
#include<fstream>
#include<regex>

#include"mytcp.h"
#include"myhttp.h"
using namespace std;



#ifndef MAXLEN
#define MAXLEN 1048576
#endif


#define Log(format, ...) \
	do { \
		fprintf(stdout, "\33[1;34m[%s,%d,%s] " format "\33[0m", \
				__FILE__, __LINE__, __func__, ## __VA_ARGS__); \
		fflush(stdout);\
	} while (0)

char req[MAXLEN], head[MAXLEN], data[MAXLEN];

int main() {

	TCP server(8080);
	cout << "OK\n";

	while (server.ac()) {
		int fpid = fork();
		if (fpid < 0) Log("fork error\n");
		else if (fpid == 0) {
			Log("fork_pid = %d\n", getpid());
			Log("client_fd = %d\n", server.client_fd);

			int rclen = server.in(req);
			if(rclen != 0) {
				Log("receive complete\n");
				cout << req;
				int len = get_content(req, head, data);
//				server << data;
				int hlen = strlen(head);
				for (int i = 0; i < len; i++) head[hlen + i] = data[i];
				server.out(head, hlen + len);
				Log("send complete\n");
			}
			return EXIT_SUCCESS;
		}
	}

	return 0;
}
