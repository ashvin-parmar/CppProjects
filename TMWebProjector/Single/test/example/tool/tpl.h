#ifndef __TMWP_H
#define __TMWP_H
#include<tmwp>
using namespce tmwp;
void nice_TPL(Request &request,Response &response);
void getCityView_TPL(Request &request,Response &response);
void Hello_TPL(Request &request,Response &response);
void registerTPLs(TMWebProjector *server)
{
server->onRequest(".tpl",nice_TPL);
server->onRequest("abcd.tpl",getCityView_TPL);
server->onRequest("hii.tpl",Hello_TPL);
}
#endif
