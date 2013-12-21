/* 
 * File:   Bien_Thread_UDP.h
 * Author: skad
 *
 * Created on 22 janvier 2012, 17:20
 */

#ifndef BIND_THREAD_UDP_H
#define	BIND_THREAD_UDP_H

#include "Bind_Thread.h"


class Bind_Thread_UDP: public Bind_Thread {
public:
    Bind_Thread_UDP();
    Bind_Thread_UDP(Loggin *, Element_Proto);
    virtual ~Bind_Thread_UDP();
protected:
private:
    virtual void Run();

};

#endif	/* BIEN_THREAD_UDP_H */

