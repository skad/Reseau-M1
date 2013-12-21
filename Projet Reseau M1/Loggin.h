/* 
 * File:   Loggin.h
 * Author: skad
 *
 * Created on 18 janvier 2012, 07:26
 */

#ifndef LOGGIN_H
#define	LOGGIN_H
#include <strings.h>
#include "config.h"

using namespace std;
class Loggin {
public:
    Loggin();
    Loggin(Config *);
    Loggin(const Loggin& orig);
    virtual ~Loggin();
    void Ecrire(string);
private:
    Config * _Conf;

};

#endif	/* LOGGIN_H */

