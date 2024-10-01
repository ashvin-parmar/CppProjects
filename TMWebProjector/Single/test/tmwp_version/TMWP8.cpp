#include<tmwp>
#include<stdio.h>
#include<windows.h>
#include<iostream>
#include<urldecoder>
#include<map>
using namespace std;
using namespace tmwp;
using namespace urldecoder;
int dataComparator(std::string *a,std::string *b)
{
return (*a)<(*b);
}
void parseRequest(const char *bytes,Request &rq);
Request::Request()
{
this->request=(REQUEST *)malloc(sizeof(REQUEST));
this->request->method=NULL;
this->request->resource=NULL;
this->request->mimeType=NULL;
this->request->isClientSideTechnologyResource='0';
this->data=new map<string *,string *>;
}
Request::Request(const char *request)
{
this->request=(REQUEST *)malloc(sizeof(REQUEST));
this->request->resource=NULL;
this->request->method=NULL;
this->request->mimeType=NULL;
this->request->isClientSideTechnologyResource='0';
this->data=new map<string *,string *>;
parseRequest(request,*this);
}
Request& Request::operator=(const Request &other)
{
if(this->request->method!=NULL) free(this->request->method);
if(this->request->resource) free(this->request->resource);
if(this->request->mimeType) free(this->request->mimeType);
map<string *,string *>::iterator i;
for(i=this->data->begin();i!=this->data->end();i++) 
{
delete i->first;
delete i->second;
}
for(i=other.data->begin();i!=other.data->end();i++)
{
this->data->insert(pair<string *,string *>(new string(i->first->c_str()),new string(i->second->c_str())));
}
this->request->method=(char *)malloc(sizeof(char)*strlen(other.request->method)+1);
strcpy(this->request->method,other.request->method);
this->request->isClientSideTechnologyResource=other.request->isClientSideTechnologyResource;
this->request->resource=NULL;
this->request->mimeType=NULL;
if(other.request->resource==NULL) return *this;
this->request->resource=(char *)malloc(sizeof(char)*strlen(other.request->resource)+1);
strcpy(this->request->resource,other.request->resource);
if(other.request->mimeType==NULL) return *this;
this->request->mimeType=(char *)malloc(sizeof(char)*strlen(other.request->mimeType)+1);
strcpy(this->request->mimeType,other.request->mimeType);
return *this;
}
Request::~Request()
{
if(this->request->method) free(this->request->method);
if(this->request->resource) free(this->request->resource);
if(this->request->mimeType) free(this->request->mimeType);
free(this->request);
map<string *,string *>::iterator i;
for(i=this->data->begin();i!=this->data->end();i++) 
{
delete i->first;
delete i->second;
}
delete this->data;
}
void Request::setRequest(REQUEST *request)
{
if(this->request->method) free(this->request->method);
if(this->request->resource) free(this->request->resource);
if(this->request->mimeType) free(this->request->mimeType);
this->request->method=(char *)malloc(sizeof(char)*strlen(request->method)+1);
strcpy(this->request->method,request->method);
this->request->resource=NULL;
this->request->mimeType=NULL;
this->request->isClientSideTechnologyResource=request->isClientSideTechnologyResource;
if(request->resource==NULL) return ;
this->request->resource=(char *)malloc(sizeof(char)*strlen(request->resource)+1);
strcpy(this->request->resource,request->resource);
if(request->mimeType==NULL) return ;
this->request->mimeType=(char *)malloc(sizeof(char)*strlen(request->mimeType)+1);
strcpy(this->request->mimeType,request->mimeType);
}
void Request::setData(map<string *,string *>::iterator start,map<string *,string *>::iterator end)
{
map<string *,string *>::iterator i;
for(i=this->data->begin();i!=this->data->end();i++) 
{
delete i->first;
delete i->second;
}
for(i=start;i!=end;i++)
{
this->data->insert(pair<string *,string *>(new string(*i->first),new string(*i->second)));
}
}
map<string *,string *> * Request::getData() 
{
map<string *,string *> *data;
data=new map<string *,string *>;
map<string *,string *>::iterator i;
for(i=this->data->begin();i!=this->data->end();i++)
{
data->insert(pair<string *,string *>(new string(*i->first),new string(*i->second)));
}
return data;
}
REQUEST *Request::getRequest() 
{
REQUEST *request;
request=(REQUEST *)malloc(sizeof(REQUEST));
request->method=(char *)malloc(sizeof(char)*(strlen(this->request->method)+1));
strcpy(request->method,this->request->method);
request->isClientSideTechnologyResource=this->request->isClientSideTechnologyResource;
request->resource=NULL;
request->mimeType=NULL;
if(this->request->resource==NULL) return request;
request->resource=(char *)malloc(sizeof(char)*(strlen(this->request->resource)+1));
strcpy(request->resource,this->request->resource);
if(this->request->mimeType==NULL) return request;
request->mimeType=(char *)malloc(sizeof(char)*(strlen(this->request->mimeType)+1));
strcpy(request->mimeType,this->request->mimeType);
return request;
}
string Request::get(const char *dataVariable)
{
string dataVar(dataVariable);
cout<<"dataVaribelt: "<<dataVariable<<endl;
map<string *,string *,int (*)(string *,string *)> data(dataComparator);//donedone
data.insert(this->data->begin(),this->data->end());
map<string *,string *>::iterator i;
i=data.find(&dataVar);
if(i==data.end()) return string("");
else return string(*i->second);
}
Response::Response()
{
this->clientSocketDescriptor=0;
this->messege="";
}
Response::Response(const Response &other)
{
this->clientSocketDescriptor=other.clientSocketDescriptor;
this->messege=other.messege;
}
Response::Response(int clientSocketDescriptor)
{
this->clientSocketDescriptor=clientSocketDescriptor;
}
Response& Response::operator=(const Response &other)
{
this->clientSocketDescriptor=other.clientSocketDescriptor;
this->messege=other.messege;
return *this;
}
Response::~Response()
{
//Do nothing
closesocket(clientSocketDescriptor);
}
void Response::setClientSocket(int clientSocketDescriptor)
{
this->clientSocketDescriptor=clientSocketDescriptor;
}
void Response::write(string messege)
{
this->messege+=messege;
}
void Response::sendResponse()
{
string a;
char tmp[501];
sprintf(tmp,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\nConnection: close\n\n",this->messege.size());
a=tmp;
a+=this->messege;
if(clientSocketDescriptor==0) return;
send(this->clientSocketDescriptor,a.c_str(),a.size(),0);
}
int extensionEquals(const char *left,const char *right)
{
int a,b;
while(*left!='\0' && *right!='\0')
{
a=*left;
b=*right;
if(a>=65 && a<=90) a+=32;
if(b>=65 && b<=90) b+=32;
if(a!=b) return 0;
left++;
right++;
}
return *left==*right;
}
char isClientSideResource(const char *resource)
{
int i;
for(i=0;resource[i]!='\0' && resource[i]!='.'; i++);
if(resource[i]=='\0') return 'N';
return 'Y';	//There are some changes have to be done later on
}
char * getMIMEType(char *resource)
{
char *mimeType;
mimeType=NULL;
int len=strlen(resource);
int lastIndexOfDot=len-1;
for(;lastIndexOfDot>0 && resource[lastIndexOfDot]!='.';lastIndexOfDot--);
if(lastIndexOfDot==0) return mimeType;
if(extensionEquals(resource+lastIndexOfDot+1,"html"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
if(extensionEquals(resource+lastIndexOfDot+1,"css"))
{
mimeType=(char *)malloc(sizeof(char)*9);
strcpy(mimeType,"text/css");
}
if(extensionEquals(resource+lastIndexOfDot+1,"js"))
{
mimeType=(char *)malloc(sizeof(char)*16);
strcpy(mimeType,"text/javascript");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpeg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"png"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"image/png");
}
if(extensionEquals(resource+lastIndexOfDot+1,"ico"))
{
mimeType=(char *)malloc(sizeof(char)*13);
strcpy(mimeType,"image/x-icon");
}
return mimeType;
}
void parseRequest(const char *bytes,Request &rq)
{
map<string *,string *,int (*)(string *,string *)> dataMap(dataComparator);
printf("BYTES: %s\n",bytes);
char resource[1001];
char method[11];
int i,j;
int len=strlen(bytes);
for(i=0;bytes[i]!=' ' && bytes[i]!='\0';i++) method[i]=bytes[i];
method[i]='\0';
i+=2;
int dataCount=0;
char **data=NULL;
char **dataVariable=NULL;
if(strcmp(method,"GET")==0)
{
for(j=0;bytes[i]!=' ' && bytes[i]!='\0';j++,i++) 
{
if(bytes[i]=='?') break;
resource[j]=bytes[i];
}
resource[j]='\0';
if(bytes[i]=='?')
{
i++;
dataCount=0;
int si=i;
while(bytes[i]!=' ')
{
if(bytes[i]=='&') dataCount++;
i++;
}
dataCount++;
data=(char **)malloc(sizeof(char *)*dataCount);
dataVariable=(char **)malloc(sizeof(char *)*dataCount);
int *cp=(int *)malloc(sizeof(int)*(dataCount*2));
i=si;
int j=0;
while(bytes[i]!=' ')
{
if(bytes[i]=='=') cp[j++]=i;
if(bytes[i]=='&') cp[j++]=i;
i++;
}
cp[j]=i;
i=si;
j=0;
int k=0;
int howManyToPick;
while(k<dataCount)
{
howManyToPick=cp[j]-i;
if(j%2!=0)
{
data[k]=(char *)malloc(sizeof(char)*(howManyToPick+1));
memcpy(data[k],(const void *)(bytes+i),sizeof(char)*howManyToPick);
data[k][howManyToPick]='\0';
dataMap.insert(pair<string *,string *>(new string(dataVariable[k]),new string(data[k])));
k++;
}
else
{
dataVariable[k]=(char *)malloc(sizeof(char)*(howManyToPick+1));
memcpy(dataVariable[k],(const void *)(bytes+i),sizeof(char)*howManyToPick);
dataVariable[k][howManyToPick]='\0';
}
i=cp[j]+1;
j++;
}
}
}//Method is GET ends here
REQUEST *request=(REQUEST *)malloc(sizeof(REQUEST));
request->method=(char *)malloc(sizeof(char)*(strlen(method)+1));
strcpy(request->method,method);
if(resource[0]=='\0')
{
request->resource=NULL;
request->isClientSideTechnologyResource='Y';
request->mimeType=NULL;
}
else
{
request->resource=(char *)malloc(sizeof(char)*(strlen(resource)+1));
strcpy(request->resource,resource);
request->isClientSideTechnologyResource=isClientSideResource(resource);
request->mimeType=getMIMEType(resource);
}
printf("Request arrived: (%s)\n",resource);

//Releasing memory
if(data!=NULL)
{
for(int k=0;k<dataCount;k++) free(data[k]);
free(data);
}
rq.setData(dataMap.begin(),dataMap.end());
map<string *,string *>::iterator z;
for(z=dataMap.begin();z!=dataMap.end();z++) 
{
delete z->first;
delete z->second;
}
rq.setRequest(request);
printf("Here check for request data: \n");

if(request->resource) free(request->resource);
if(request->mimeType) free(request->mimeType);
if(request->method) free(request->method);
free(request);
}
TMWebProjector::TMWebProjector(int portNumber)
{
this->portNumber=portNumber;
this->ptrOnRequest=NULL;
this->url=NULL;
}
void TMWebProjector::onRequest(const char *url,void (*ptrOnRequest)(Request &,Response &))
{
if(this->url) delete [] this->url;
this->url=NULL;
this->ptrOnRequest=NULL;
if(url==NULL || ptrOnRequest==NULL) return;
this->url=new char[strlen(url)+1];
strcpy(this->url,url);
this->ptrOnRequest=ptrOnRequest;
//printf("URL ASSIGENed: (%s), p2f: %d\n",this->url,this->ptrOnRequest);
}
TMWebProjector::~TMWebProjector()
{
if(this->url) delete [] this->url;
}
void TMWebProjector::start()
{
int length;
int cn,rc;
FILE *f;
WORD ver;
WSADATA wsaData;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int successCode,byteExtracted,len;
char requestBuffer[8192]; 	//8192=1024 * 8 
char responseBuffer[1024]; 	//1024 chunk of data 
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
WSACleanup();
return ;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(this->portNumber);
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
char messege[500];
if(successCode<0)
{
sprintf(messege,"Unable to bind server with port %d",this->portNumber);
printf("%s\n",messege);
closesocket(serverSocketDescriptor);
WSACleanup();
return ;
}
listen(serverSocketDescriptor,10);
len=sizeof(clientSocketInformation);
while(1)
{
sprintf(messege,"TMServer is ready to accept request on port %d",this->portNumber);
printf("%s\n",messege);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
printf("Client Socket Descriptor: %d\n",clientSocketDescriptor);
if(clientSocketDescriptor==0) continue;
if(clientSocketDescriptor<0)
{
printf("Unable to accept client request\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return ;
}
byteExtracted=recv(clientSocketDescriptor,requestBuffer,8192,0);
printf("Request Byte Extracted : %d\n",byteExtracted);
if(byteExtracted<0)
{
// Something to done here, Implemeted later on
}
else if(byteExtracted==0)
{
//Something to done here, Implemeted later on
}
else 
{
requestBuffer[byteExtracted]='\0';	//Request taken from browser are not contain termination
URLDecoder url(requestBuffer);
Request rq;
parseRequest(url.getDecodedURL().c_str(),rq);
REQUEST *request;
request=rq.getRequest();
if(request->isClientSideTechnologyResource=='Y')
{
cout<<"clientSideTech"<<endl;
if(request->resource==NULL)
{
cout<<"Resource Null"<<endl;
f=fopen("index.html","rb");
if(f==NULL)
{
f=fopen("index.htm","rb");
}
if(f==NULL)
{
printf("Sending 404 page\n");
strcpy(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 163\nConnection: close\n\n<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource / not found</h2></body></html>");
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
closesocket(clientSocketDescriptor);
}
else
{
fseek(f,0,2);
length=ftell(f);
fseek(f,0,0);
printf("Size of length: %d\n",length);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\nConnection: close\n\n",length);
byteExtracted=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
cn=0;
while(cn<length)
{
rc=length-cn;
if(rc>1024) rc=1024;
fread(responseBuffer,rc,1,f);
if(feof(f)) break;
byteExtracted=send(clientSocketDescriptor,responseBuffer,rc,0);
cn+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
}
}
else		//if request->resource!=NULL
{
printf("Resource not null\n");
f=fopen(request->resource,"rb");
if(f==NULL)
{
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
closesocket(clientSocketDescriptor);
}
else
{
fseek(f,0,2);
length=ftell(f);
fseek(f,0,0);
printf("Size of length: %d\n",length);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: %s\nContent-Length: %d\nConnection: close\n\n",request->mimeType,length);
byteExtracted=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
cn=0;
while(cn<length)
{
rc=length-cn;
if(rc>1024) rc=1024;
fread(responseBuffer,rc,1,f);
if(feof(f)) break;
byteExtracted=send(clientSocketDescriptor,responseBuffer,rc,0);
cn+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
}
}
}
else
{
Response rs;
rs.setClientSocket(clientSocketDescriptor);
cout<<"serverSideResource"<<endl;
if(this->url==NULL || this->ptrOnRequest==NULL) 
{
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
int ii=0;
if(this->url[0]=='/') ii=1;
if(strcmp(this->url+ii,request->resource)==0)
{
this->ptrOnRequest(rq,rs);
printf("Request Processed Successfully\n");
}
else
{
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
}
}//server part else ends here
if(request->resource) free(request->resource);
if(request->mimeType) free(request->mimeType);
if(request->method) free(request->method);
if(request) free(request);
}//else part ends here
}// while loop ends
closesocket(serverSocketDescriptor);
WSACleanup();
}