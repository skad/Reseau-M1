/* 
 * File:   Communication_Thread_TCP.cpp
 * Author: skad
 * 
 * Created on 20 janvier 2012, 15:34
 */

#include "Communication_Thread_TCP.h"
#include "Communication.h"
#include "fonctions.h"
#include <string>

Communication_Thread_TCP::Communication_Thread_TCP() {
}

Communication_Thread_TCP::Communication_Thread_TCP(Loggin* l, int s, Data * d, int o, pthread_mutex_t * p) : Communication_Thread(l, s, d, o, p) {

}

Communication_Thread_TCP::Communication_Thread_TCP(const Communication_Thread_TCP& orig) {
}

Communication_Thread_TCP::~Communication_Thread_TCP() {
}

void Communication_Thread_TCP::Run() {
    char buf[1024];
    int n;
    string chaine;
    while (_Run) {
        chaine = "";
        n = 0;
        while ((n = recv(_Socket, buf, 1024,MSG_DONTWAIT)) > 0)
        {
            chaine.append(buf, n);
        }
        if (chaine.size() > 0) {
            _Log->Ecrire("Reception complete depuis : " + int_to_string(_Origin));
            _Log->Ecrire("Msg : "+chaine);
            pthread_mutex_lock(_Mutex);
            _Data->SetOrigin(_Origin);
            _Data->Add(chaine);
            _Data->Set_Ready();
            pthread_mutex_unlock(_Mutex);
        }
        if(n == 0)
        {
            _Run = false;
        }
        usleep(1000);
    }
}

void Communication_Thread_TCP::Send() {
    pthread_mutex_lock(_Mutex);
    string chaine = _Data->Empty();
    pthread_mutex_unlock(_Mutex);
    //chaine = chaine.substr(0,chaine.size()-1);
    _Log->Ecrire("Envoi : "+chaine+" Taille : "+int_to_string(chaine.size()));
    send(_Socket, chaine.c_str(), chaine.size(), 0);
}

void Communication_Thread_TCP::Stopping(){
    close(_Socket);
}