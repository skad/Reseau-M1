/* 
 * File:   Communication_Thread.cpp
 * Author: skad
 * 
 * Created on 20 janvier 2012, 15:24
 */

#include "Communication_Thread.h"
#include "Data.h"

Communication_Thread::Communication_Thread() {
}

Communication_Thread::Communication_Thread(Loggin* l, int s,Data * d, int o, pthread_mutex_t * p)
{
    _Log = l;
    _Socket = s;
    _Data = d;
    _Origin = o;
    _Mutex = p;
    _Online = true;
}

Communication_Thread::Communication_Thread(const Communication_Thread& orig) {
}

Communication_Thread::~Communication_Thread() {
}

