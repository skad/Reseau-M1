/* 
 * File:   Server_Bind.cpp
 * Author: skad
 * 
 * Created on 19 janvier 2012, 15:43
 */

#include "Server_Bind.h"
#include "Bind_Thread_TCP.h"
#include "Bien_Thread_UDP.h"
#include "config.h"

Server_Bind::Server_Bind(Loggin * l, Element_Proto e)
{
    if (e.proto == TCP)
    {
        _Thread_Tcp = Bind_Thread_TCP(l,e);
    }
    else
    {
        _Thread_Udp = Bind_Thread_UDP(l,e);
    }

    _type = e.proto;
}

Server_Bind::~Server_Bind() {
}

void Server_Bind::Start()
{
    if(_type == TCP)
    {
        _Thread_Tcp.Start();
    }
    else
    {
        _Thread_Udp.Start();
    }

}

bool Server_Bind::Is_Ready()
{
    bool retour;
    if (_type == TCP)
    {
        retour = _Thread_Tcp.Is_Ready();
    }
    else
    {
        retour = _Thread_Udp.Is_Ready();
    }

    return retour;
}

bool Server_Bind::Is_Alive()
{
    bool retour;
    if (_type == TCP)
    {
        retour = _Thread_Tcp.isAlive();
    }
    else
    {
        retour = _Thread_Udp.isAlive();
    }

    return retour;
}

void Server_Bind::Stop()
{
    if (_type == TCP)
    {
        _Thread_Tcp.Stop();
    }
    else
    {
        _Thread_Udp.Stop();
    }
}