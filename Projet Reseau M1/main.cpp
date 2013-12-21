/* 
 * File:   main.cpp
 * Author: skad
 *
 * Created on 17 janvier 2012, 18:43
 */

#include <cstdlib>
#include <iostream>
#include <signal.h>
#include "Loggin.h"
#include "config.h"
#include "Server_Bind.h"
#include <vector>
#include "fonctions.h"

using namespace std;
Loggin Loger;
vector<Server_Bind *> Vector_Bind;

void Stop_App()
{
    ::Loger.Ecrire("Asking to stop ...");
    for (int i=0; i< ::Vector_Bind.size();i++)
    {
       if(::Vector_Bind[i]->Is_Alive())
       {
           ::Vector_Bind[i]->Stop();
       }
    }
    exit(0);
}
void Signal_Handler(int s)
{
    switch(s)
    {
        case SIGINT:
            ::Loger.Ecrire("User action : ctrl+c");
        case SIGTERM:
            Stop_App();
            break;
        default :
            string chaine = "Signal recave : "+s;
            ::Loger.Ecrire(chaine);
    }
}

int main(int argc, char** argv)
{
    //def
    vector<Element_Proto> temp;
    Config Conf;
   //end def
    //start init
   Conf = Config();
   ::Loger = Loggin(&Conf);
   Conf.Load_Config("proxy_reseau.conf");
   Conf.Load_Service("services");
   ::Loger.Ecrire("Starting......");
   signal (SIGABRT,Signal_Handler);
   signal (SIGFPE,Signal_Handler);
   signal (SIGILL,Signal_Handler);
   signal (SIGINT,Signal_Handler);
   signal (SIGSEGV,Signal_Handler);
   signal (SIGTERM,Signal_Handler);
   ::Loger.Ecrire("Signals linked......");
   ::Loger.Ecrire(Conf.toString());
   temp = Conf.Get_Vector_Proto();
   for(int i=0; i<temp.size();i++)
   {
        ::Loger.Ecrire("Start bind on port : "+int_to_string(temp[i]._num_port)+" type "+int_to_string(temp[i].proto)+"....");
        ::Vector_Bind.push_back(new Server_Bind(&::Loger,temp[i]));
   }

   for (int i=0; i< ::Vector_Bind.size();i++)
   {
       if(::Vector_Bind[i]->Is_Ready())
       {
           ::Vector_Bind[i]->Start();
       }
   }
   bool one_service;
   //verification des lancement sinon arret
   for (int i=0; i<Vector_Bind.size();i++)
   {
       one_service = Vector_Bind[i]->Is_Alive();
   }

   if(!one_service)
   {
       ::Loger.Ecrire("None service is running -> shutdow");
       Stop_App();
   }
   //end init
   while(1)
   {
       sleep(1);
   }
}

