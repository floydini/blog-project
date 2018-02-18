#ifndef rand_bafbsfasdas
#define rand_bafbsfasdas

#include<map>
#include<cstdio>
#include<iostream>


#define SP " "
#define CRLF "\r\n"
#define MAXLEN 16777216
#define BACKLOG 20

const char* HTTP_Version = "HTTP/1.1";
const char* path = "website";
const map<int, char*> Status_Code = {
		{200, (char*)"200 OK"},
			{404, (char*)"404 Not Found"},
				{503, (char*)"503 Service Unavailable"}
};

#define Log(format, ...) \
	do { \
		fprintf(stdout, "\33[1;34m[%s,%d,%s] " format "\33[0m", \
				__FILE__, __LINE__, __func__, ## __VA_ARGS__);  \
		fflush(stdout);\
	} while (0)

#endif
