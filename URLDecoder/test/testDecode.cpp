#include<stdio.h>
#include<urldecoder>
using namespace urldecoder;
using namespace std;

int main() {
    URLDecoder decoder;

    std::string encodedURL1 ="http://localhost:8080/register?nm=Ashvin%7E%3F%3F%3F%3FWhat+is+your+name+%5E%25%26%24*%23%28%25%23%28%23%29%40*%24%28%25*%24+%22%22%22%22%22+%3E%3C%3A%3F%3A%7B%7D%7C%2B%3A%22%3E%22&ct=432423MEDFMEOg%3F%3F%3E%3E";
cout<<"Encoded URL 1: "<<encodedURL1 <<endl;	
    std::string decodedURL1 = decoder.decode(encodedURL1);
    std::cout << "Decoded URL 1: " << decodedURL1 << std::endl;

    std::string encodedURL2 ;
cout<<"Enter Your URL: ";
getline(cin,encodedURL2);

    std::string decodedURL2 = decoder.decode(encodedURL2);
    std::cout << "Decoded URL 2: " << decodedURL2 << std::endl;

    return 0;
}