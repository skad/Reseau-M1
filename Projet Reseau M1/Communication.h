/* 
 * File:   Communication.h
 * Author: skad
 *
 * Created on 19 janvier 2012, 09:35
 */

#ifndef COMMUNICATION_H
#define	COMMUNICATION_H
#include "Loggin.h"
#include "Thread.h"
#include "Communication_Thread_Socket.h"
#include "Data.h"
#include <pthread.h>
class Communication : public Thread{
public:
    Communication();
    Communication(Loggin *,int, int, int, sockaddr_in&,string,vector<string>);
    Communication(const Communication& orig);
    virtual ~Communication();
    bool IsReady();
private:
    pthread_mutex_t _Mutex;
    Loggin * _Log;
    Data _Data;
    bool _Ready;
    Communication_Thread_Socket _Client;
    Communication_Thread_Socket _Server;
    virtual void Run();
    virtual void Stopping();
    vector<string> _Liste_Mots;
};

#endif	/* COMMUNICATION_H */

