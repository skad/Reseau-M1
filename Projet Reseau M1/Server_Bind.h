/* 
 * File:   Server_Bind.h
 * Author: skad
 *
 * Created on 19 janvier 2012, 15:43
 */

#ifndef SERVER_BIND_H
#define	SERVER_BIND_H

#include "Bind_Thread_TCP.h"
#include "Bien_Thread_UDP.h"

class Server_Bind{
public:
    Server_Bind(Loggin *, Element_Proto);
    ~Server_Bind();
    void Start();
    bool Is_Ready();
    bool Is_Alive();
    void Stop();
private:
    Bind_Thread_TCP _Thread_Tcp;
    Bind_Thread_UDP _Thread_Udp;
    int _type;

};

#endif	/* SERVER_BIND_H */

