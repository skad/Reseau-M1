/* 
 * File:   Communication.cpp
 * Author: skad
 * 
 * Created on 19 janvier 2012, 09:35
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "Communication.h"
#include <stdlib.h>
#include <netdb.h>
#include <memory.h>
#include "fonctions.h"

Communication::Communication() {
}

Communication::Communication(Loggin * l,int type,int port, int client_id, sockaddr_in& c_in, string host, vector<string> vector) : Thread()
{
    _Liste_Mots = vector;
    _Log = l;
    _Data = Data();
    _Mutex = PTHREAD_MUTEX_INITIALIZER;
    _Client = Communication_Thread_Socket(l,type,client_id, &_Data, CLIENT,&_Mutex);
    _Log->Ecrire("Creation de la connection");
    int server_id = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    struct hostent *recup;
    recup = gethostbyname(host.c_str());
    memcpy((char *)&server.sin_addr, (char *)recup->h_addr, recup->h_length);
    socklen_t taille = sizeof(server);
    _Ready = true;
    if(connect(server_id,(sockaddr *)&server, sizeof(server))<0)
    {
        _Ready = false;
        string msg = "Erreure dans l'ouverture de la connection vers "+host+" sur le port : " + int_to_string(server.sin_port);
        _Log->Ecrire(msg);
        perror("");

    }
    else
    {
        _Server = Communication_Thread_Socket(l,type,server_id, &_Data, SERVER,&_Mutex);
        _Log->Ecrire("Socket server ok");
    }
    if(_Ready)
    {
        _Client.Start();
        _Server.Start();
        _Log->Ecrire("Thread client / serveurs lancees");
    }

    

}

Communication::Communication(const Communication& orig) {
}

Communication::~Communication() {
}

void Communication::Run()
{
    bool ready;
    while(_Run)
    {
        pthread_mutex_lock(&_Mutex);
        for(int i = 0; i < _Liste_Mots.size(); i++)
        {
            if (_Data.Is_in(_Liste_Mots[i]) > -1)
            {
                _Data.Empty();
            }
        }
        ready = _Data.Is_Ready();
        pthread_mutex_unlock(&_Mutex);
        if(ready)
        {
            if (_Data.GetOrigin() == CLIENT)
            {
                _Log->Ecrire("Send to server >");
                _Server.Send();
            }
            else
            {
                _Log->Ecrire("Send to client >");
                _Client.Send();
            }
        }
        if(!_Server.IsAlive())
        {
            _Client.Stop();
            _Run = false;
        }
        if(!_Client.IsAlive())
        {
            _Server.Stop();
            _Run = false;
        }
        usleep(1000);
    }
    _Log->Ecrire("End of communication");
}

bool Communication::IsReady()
{
    return _Ready;
}
void Communication::Stopping()
{
    _Log->Ecrire("Communication stop");
    _Client.Stop();
    _Server.Stop();
}