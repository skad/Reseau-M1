/* 
 * File:   Bien_Thread_UDP.cpp
 * Author: skad
 * 
 * Created on 22 janvier 2012, 17:20
 */

#include <netdb.h>
#include <memory.h>
#include "fonctions.h"
#include "Bien_Thread_UDP.h"

Bind_Thread_UDP::Bind_Thread_UDP() {
}

Bind_Thread_UDP::Bind_Thread_UDP(Loggin * l, Element_Proto e) : Bind_Thread(l, e) {

}

Bind_Thread_UDP::~Bind_Thread_UDP() {
}

void Bind_Thread_UDP::Run() {
    char buf[1024];
    int n;
    string chaine;
    struct sockaddr_in *from;
    struct sockaddr_in *to;
    socklen_t size = sizeof (struct sockaddr_in);
    _Log->Ecrire("En attente de connection sur le port " + int_to_string(_Port));
    while (_Run) {
        chaine = "";
        n = recvfrom(_Socket, buf, 1024, 0, (struct sockaddr *) from, &size);
        chaine.append(buf, n);
        if (chaine.size() > 0) {
            _Log->Ecrire("Reception complete depuis : 1");
            _Log->Ecrire("Msg : " + chaine);

            to->sin_family = AF_INET;
            to->sin_port = htons(_Port);
            struct hostent *recup;
            recup = gethostbyname(_Dest.c_str());
            memcpy((char *) &to->sin_addr, (char *) recup->h_addr, recup->h_length);

            sendto(_Socket, chaine.c_str(), strlen(chaine.c_str()), 0, (struct sockaddr *) to, size);

            n = recvfrom(_Socket, buf, 1024, MSG_DONTWAIT, (struct sockaddr *) to, &size);
            chaine.append(buf, n);
            sendto(_Socket, chaine.c_str(), strlen(chaine.c_str()), 0, (struct sockaddr *) from, size);
        }
        usleep(1000);
    }
}