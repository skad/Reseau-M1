/* 
 * File:   Bind_Thread_TCP.cpp
 * Author: skad
 * 
 * Created on 19 janvier 2012, 09:34
 */

#include "Bind_Thread_TCP.h"
#include "fonctions.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include "Communication.h"
#include "config.h"
Bind_Thread_TCP::Bind_Thread_TCP(){};

Bind_Thread_TCP::Bind_Thread_TCP(Loggin * l, Element_Proto e) : Bind_Thread(l,e) {
}

Bind_Thread_TCP::~Bind_Thread_TCP() {
}

void Bind_Thread_TCP::Run() {
    if(listen(_Socket, 5)<0)
    {
        _Run = false;
        string msg = "Erreure dans le listen sur le port : "+int_to_string(_Sin.sin_port);
        _Log->Ecrire(msg);
        perror("");
    }
    
    sockaddr_in csin;
    int size;
    while(_Run)
    {
        _Log->Ecrire("En attente de connection sur le port "+int_to_string(_Port));
        socklen_t taille = sizeof(csin);
        int csock = accept(_Socket, (struct sockaddr*)&csin, &taille);
        _Log->Ecrire("Communication etablie sur le port"+int_to_string(_Port));
        _Communication_vector.push_back(new Communication(_Log,TCP,_Port,csock,csin,_Dest,_Liste_Mots));
        size = _Communication_vector.size()-1;
        if(_Communication_vector.back()->IsReady())
        {
          _Communication_vector.back()->Start();
           _Log->Ecrire("Thread Lance");
        }
        else
        {
            _Log->Ecrire("Suppretion client");
            _Communication_vector.pop_back();
            _Log->Ecrire("Fermeture de la socket");
            close(csock);
        }
    }
}
