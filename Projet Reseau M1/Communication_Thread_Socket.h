/* 
 * File:   Communication_Thread_Socket.h
 * Author: skad
 *
 * Created on 20 janvier 2012, 15:41
 */

#ifndef COMMUNICATION_THREAD_SOCKET_H
#define	COMMUNICATION_THREAD_SOCKET_H
#include "Communication_Thread_Socket.h"

#include "Data.h"


#include "Communication_Thread_TCP.h"

#include "Loggin.h"

class Communication_Thread_Socket {
public:
    Communication_Thread_Socket();
    Communication_Thread_Socket(Loggin *,int ,int ,Data *,int, pthread_mutex_t *);
    Communication_Thread_Socket(const Communication_Thread_Socket& orig);
    virtual ~Communication_Thread_Socket();
    void Stop();
    void Start();
    void Send();
    bool IsAlive();
private:
    Communication_Thread_TCP _Thread_Tcp;
    int _type;
};

#endif	/* COMMUNICATION_THREAD_SOCKET_H */

