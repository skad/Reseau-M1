/* 
 * File:   Loggin.cpp
 * Author: skad
 * 
 * Created on 18 janvier 2012, 07:26
 */

#include <iostream>
#include <syslog.h>
#include "Loggin.h"

using namespace std;
Loggin::Loggin(){}
Loggin::Loggin(Config * c) {
    _Conf = c;
    openlog("PROXY M1",LOG_PID,LOG_USER);
}

Loggin::Loggin(const Loggin& orig) {
    _Conf = this->_Conf;
    openlog("PROXY M1",LOG_PID,LOG_USER);
}

Loggin::~Loggin() {
    closelog();
}

void Loggin::Ecrire(string chaine)
{
    if (_Conf->Is_Debug())
    {
        cout<<chaine<<endl;
    }
    syslog(LOG_INFO,"%s", chaine.c_str());
}
