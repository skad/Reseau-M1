/* 
 * File:   Bind_Thread.h
 * Author: skad
 *
 * Created on 18 janvier 2012, 19:37
 */

#ifndef BIND_THREAD_H
#define	BIND_THREAD_H
#include "Thread.h"
#include "Loggin.h"
#include "config.h"
#include "Communication.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

class Bind_Thread : public Thread {
public:
    Bind_Thread();
    Bind_Thread(Loggin *, Element_Proto);
    virtual ~Bind_Thread();
    bool Is_Ready();
protected :
    int _Socket;
    Loggin * _Log;
    sockaddr_in _Sin;
    vector<Communication *> _Communication_vector;
    bool _Ready;
    string _Dest;
    int _Port;
    vector<string> _Liste_Mots;
private:
    virtual void Run()=0;
    virtual void Stopping();
    void Load_Filtre();

};

#endif	/* BIND_THREAD_H */

