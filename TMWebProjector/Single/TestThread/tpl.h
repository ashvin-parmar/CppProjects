#ifndef __TMWP_H
#define __TMWP_H
#include<tmwp>
using namespace tmwp;
void getCityView_TPL(Request &request,Response &response);
void registerTPLs(TMWebProjector *server)
{
server->onRequest("/errorPage.tpl",getCityView_TPL);
}
#endif
