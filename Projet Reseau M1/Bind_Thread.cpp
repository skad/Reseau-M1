/* 
 * File:   Bind_Thread.cpp
 * Author: skad
 * 
 * Created on 18 janvier 2012, 19:37
 */

#include "Bind_Thread.h"
#include "Thread.h"
#include "config.h"
#include "fonctions.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

Bind_Thread::Bind_Thread(){};

Bind_Thread::Bind_Thread(Loggin* l,Element_Proto e): Thread() {
    _Log = l;
    _Socket = socket(AF_INET, e.proto, 0);
    if ((_Socket = socket(AF_INET, e.proto, 0))<0)
    {
        _Ready = false;
        string msg = "Erreure sur la socket : " + int_to_string(_Sin.sin_port);
        _Log->Ecrire(msg);
        perror("");
    }
    _Sin.sin_family = AF_INET;
    _Sin.sin_addr.s_addr = INADDR_ANY;
    _Sin.sin_port =  htons((u_short)e._num_port);
    _Ready = true;
    _Dest = e._host;
    _Port = e._num_port;
    int val = 1;
    if (setsockopt(_Socket,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val))<0)
    {
        _Ready = false;
        string msg = "Erreur dans la definition des options";
        _Log->Ecrire(msg);
        perror("");
    }

    if (bind(_Socket, (struct sockaddr *)&_Sin, sizeof(_Sin))<0)
    {
        _Ready = false;
        string msg = "Erreure dans le bin sur le port : " + int_to_string(_Sin.sin_port);
        _Log->Ecrire(msg);
        perror("");
    }
    _Log->Ecrire("Bind ok sur le port "+int_to_string(_Port));
    this->Load_Filtre();
}

bool Bind_Thread::Is_Ready(){
    return _Ready;
}
Bind_Thread::~Bind_Thread() {
}

void Bind_Thread::Stopping()
{
    _Log->Ecrire("Start stop for the child thread on port : "+int_to_string(_Port));
    for(int i = 0; i<_Communication_vector.size();i++)
    {
        _Communication_vector[i]->Stop();
    }
    _Log->Ecrire("End stop for the child thread on port : "+int_to_string(_Port));
    close(_Socket);
}

void Bind_Thread::Load_Filtre()
{
    ifstream file(int_to_string(_Port).c_str(),ios::in);
    string line;
    if ( file )
    {
        while( getline(file,line) )
        {
            if(line[0] != '#')
            {
                _Liste_Mots.push_back(line);

            }
        }
    }
    else
    {
        cout<<"Service File : "+int_to_string(_Port)+" is missing"<<endl;
    }

}