/* 
 * File:   Bind_Thread_TCP.h
 * Author: skad
 *
 * Created on 19 janvier 2012, 09:34
 */

#ifndef BIND_THREAD_TCP_H
#define	BIND_THREAD_TCP_H

#include "Bind_Thread.h"
#include "Loggin.h"
#include "config.h"


class Bind_Thread_TCP : public Bind_Thread {
public:
    Bind_Thread_TCP();
    Bind_Thread_TCP(Loggin *, Element_Proto);
    virtual ~Bind_Thread_TCP();
protected :
private:
    virtual void Run();
};

#endif	/* BIND_THREAD_TCP_H */

