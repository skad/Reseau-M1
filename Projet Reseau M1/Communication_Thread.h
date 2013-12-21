/* 
 * File:   Communication_Thread.h
 * Author: skad
 *
 * Created on 20 janvier 2012, 15:24
 */

#ifndef COMMUNICATION_THREAD_H
#define	COMMUNICATION_THREAD_H

#include "Thread.h"
#include "Loggin.h"
#include "config.h"
#include "Data.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
class Communication_Thread : public Thread{
public:
    Communication_Thread();
    Communication_Thread(Loggin *, int, Data *,int,pthread_mutex_t *);
    Communication_Thread(const Communication_Thread& orig);
    virtual ~Communication_Thread();
protected:
    int _Socket;
    Loggin * _Log;
    Data * _Data;
    int _Origin;
    pthread_mutex_t * _Mutex;
    bool _Online;
private:
    virtual void Run()=0;
    virtual void Stopping()=0;

};

#endif	/* COMMUNICATION_THREAD_H */

