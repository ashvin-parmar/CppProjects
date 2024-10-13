#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main()
{
 	int serverSocketDescriptor;
	int clientSocketDescriptor;
	struct sockaddr_in serverSocketInformation;
	char response[5000];
	char request[5000];
	int successCode;
	clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
	serverSocketInformation.sin_family=AF_INET;
	serverSocketInformation.sin_port=htons(5050);
	serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
	connect(clientSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
	strcpy(request,"Hello Thinking machine, I have registered for a course ");
	send(clientSocketDescriptor,request,strlen(request)+1,0);
	while(1)
	{
		successCode=recv(clientSocketDescriptor,response,strlen(response)+1,0);
	if(!(successCode>0)) break; 
	printf("Response: %s\n",response);
	}
	return 0;
}

