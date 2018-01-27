#include<iostream>
#include<sys/socket.h>
#include<unistd.h>
#include<cstdlib>
#include<netinet/in.h>
#include<cstdio>
#include<cstring>
using namespace std;

#ifndef MAXLEN
#define MAXLEN 4096
#endif

#ifndef BACKLOG
#define BACKLOG 10
#endif


class TCP {
  private:
	int fd, client_fd;
	struct sockaddr_in addr, client_addr;
  public:
	TCP(int port) {
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		memset(addr.sin_zero, 0, sizeof(addr.sin_zero));
		fd = socket(AF_INET, SOCK_STREAM, 0);
		if (fd == -1)
			printf("sockfd == -1\n");

		bind(fd, (sockaddr*)&addr, sizeof(addr));
		listen(fd, BACKLOG);
	}

	bool ac() {
		socklen_t len = sizeof(client_addr);
		client_fd = accept(fd, (sockaddr*)&client_addr, &len);
		if (client_fd != -1)
			return true;
		printf("accept error\n");
		return false;
	}

	void in(char buf[]) {
		if (recv(client_fd, buf, MAXLEN, 0) == MAXLEN)
			printf("The buf may overflow!\n");
	}

	void out(char data[]) {
		char *tmp = data;
		int len = strlen(data);
		while (len) {
			int aclen = send(client_fd, tmp, len, 0);
			if (aclen == -1) {
				printf("send error\n");
				return;
			}
			len -= aclen;
			tmp += aclen;
		}
	}

};

