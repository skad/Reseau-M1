/* 
 * File:   Communication_Thread_Socket.cpp
 * Author: skad
 * 
 * Created on 20 janvier 2012, 15:41
 */

#include "Communication_Thread_Socket.h"
#include "config.h"
#include "Communication_Thread_TCP.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

Communication_Thread_Socket::Communication_Thread_Socket() {
}

Communication_Thread_Socket::Communication_Thread_Socket(Loggin *l,int type,int sock,Data * d,int o, pthread_mutex_t * m) {
    _type = type;
    if(_type == TCP)
    {
        _Thread_Tcp = Communication_Thread_TCP(l,sock,d,o,m);
    }
    else
    {
        _Thread_Tcp = Communication_Thread_TCP(l,sock,d,o,m);
    }
}

Communication_Thread_Socket::Communication_Thread_Socket(const Communication_Thread_Socket& orig) {
}

Communication_Thread_Socket::~Communication_Thread_Socket() {
}

void Communication_Thread_Socket::Start()
{
    if(_type == TCP)
    {
        _Thread_Tcp.Start();
    }
}

void Communication_Thread_Socket::Stop()
{
    if(_type == TCP)
    {
        _Thread_Tcp.Stop();
    }
}

void Communication_Thread_Socket::Send()
{
    if(_type == TCP)
    {
        _Thread_Tcp.Send();
    }
}

bool Communication_Thread_Socket::IsAlive()
{
    bool retour;
    if(_type == TCP)
    {
        retour =  _Thread_Tcp.isAlive();
    }

    return retour;
}