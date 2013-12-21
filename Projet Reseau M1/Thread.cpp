/* 
 * File:   Thread.cpp
 * Author: skad
 * 
 * Created on 18 janvier 2012, 16:26
 */

#include "Thread.h"
#include <pthread.h>

Thread::Thread() {
    _Run = false;
}

Thread::Thread(const Thread& orig) {
}

Thread::~Thread() {
}

int Thread::Start()
{
    _Run = true;
    return pthread_create(&_T, NULL, Entry_Point, this);
}

void Thread::blabla()
{
    this->Run();
}

int Thread::Stop()
{
    this->Stopping();
    _Run = false;
    return pthread_cancel(_T);
    
}

void * Entry_Point(void * data)
{
    Thread * ptr = (Thread*)data;
    ptr->blabla();
}

bool Thread::isAlive()
{
    return _Run;
}

