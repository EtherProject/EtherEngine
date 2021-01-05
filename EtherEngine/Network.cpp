#include "Network.h"

ETHER_API getLinkDomain(lua_State* L)
{
	lua_pushstring(L, GetLinkDomain(luaL_checkstring(L, 1)).c_str());

	return 1;
}


ETHER_API getLinkRoute(lua_State* L)
{
	lua_pushstring(L, GetLinkRoute(luaL_checkstring(L, 1)).c_str());

	return 1;
}


ETHER_API requestGet(lua_State* L)
{
	string domain = GetLinkDomain(luaL_checkstring(L, 1));
	string route = GetLinkRoute(luaL_checkstring(L, 1));

	if (domain.find(':') != string::npos)
	{
		Client client(domain.substr(0, domain.find(':')), atoi(domain.substr(domain.find(':') + 1).c_str()));
		PushResponseTable(L, client.Get(route.c_str()));
	}
	else
	{
		Client client(domain);
		PushResponseTable(L, client.Get(route.c_str()));
	}

	return 1;
}


MoudleNetwork::MoudleNetwork(lua_State* L)
{
	_pL = L;

	_vCMethods = {
		{ "GetLinkDomain", getLinkDomain },
		{ "GetLinkRoute", getLinkRoute },
		{ "RequestGet", requestGet },
	};

	_vMacros = {};
}