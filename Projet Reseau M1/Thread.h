/* 
 * File:   Thread.h
 * Author: skad
 *
 * Created on 18 janvier 2012, 16:26
 */

#ifndef LISTEEN_SOCKET_H
#define	LISTEEN_SOCKET_H
#include <pthread.h>
using namespace std;
class Thread {
public:
    Thread();
    Thread(const Thread& orig);
    virtual ~Thread();
    int Start();
    int Stop();
    int Wait();
    bool isAlive();
    void blabla();
protected:
    virtual void Run()=0;
    virtual void Stopping()=0;
    bool _Run;
private:
    pthread_t _T;
};

void* Entry_Point(void *);

#endif	/* LISTEEN_SOCKET_H */

