#ifndef __TMWP_H
#define __TMWP_H
#include<tmwp>
using namespce tmwp;
void nice_TPL(Request &request,Response &response);
void getCityView_TPL(Request &request,Response &response);
void Hello_TPL(Request &request,Response &response);
void registerTPLs(TMWebProjector *server)
{
server->onRequest(".tpl.cpp",nice_TPL);
server->onRequest("abcd.tpl.cpp",getCityView_TPL);
server->onRequest("hii.tpl.cpp",Hello_TPL);
}
#endif
