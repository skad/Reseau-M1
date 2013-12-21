/* 
 * File:   Communication_Thread_TCP.h
 * Author: skad
 *
 * Created on 20 janvier 2012, 15:34
 */

#ifndef COMMUNICATION_THREAD_TCP_H
#define	COMMUNICATION_THREAD_TCP_H
#include "Communication_Thread.h"
#include "Data.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string>

class Communication_Thread_TCP : public Communication_Thread{
public:
    Communication_Thread_TCP();
    Communication_Thread_TCP(Loggin *, int,Data *,int,pthread_mutex_t *);
    Communication_Thread_TCP(const Communication_Thread_TCP& orig);
    virtual ~Communication_Thread_TCP();
    void Send();
private:
    virtual void Run();
    virtual void Stopping();
};

#endif	/* COMMUNICATION_THREAD_TCP_H */

