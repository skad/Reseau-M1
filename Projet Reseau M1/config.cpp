/* 
 * File:   config.cpp
 * Author: skad
 * 
 * Created on 18 janvier 2012, 11:18
 */

#include "config.h"
#include "Loggin.h"
#include <fstream>
#include <string>
#include <iostream>
#include "fonctions.h"
#include <vector>
using namespace std;

Config::Config() {
    _Run_Mode = NORMAL;
}

Config::Config(const Config& orig) {
    _Run_Mode = orig._Run_Mode;
}

Config::~Config() {
}

bool Config::Is_Debug()
{
    return _Run_Mode;
}

vector<Element_Proto> Config::Get_Vector_Proto()
{
    return _Liste_Proto;
}

string Config::toString()
{
    string out;
    out+="Config :\r\n";
    for (int i = 0;i < _Liste_Proto.size();i++)
    {
        switch (_Liste_Proto[i].proto)
        {
            case TCP:
                out+= "tcp";
                break;
            case UDP:
                out+= "udp";
                break;
        }
        out.append(" : ");
        out.append(int_to_string(_Liste_Proto[i]._num_port));
        out.append("\r\n");
    }

    out+="run mode : ";

    switch (_Run_Mode)
    {
        case NORMAL:
            out+= "normal";
            break;
        case DEBUG:
            out+= "debug";
            break;
    }

    return out+"\r\n";
}

void Config::Load_Config(string url)
{
    ifstream file(url.c_str(),ios::in);
    string line;
    vector<string> liste;
    if ( file )
    {
        while( getline(file,line) )
        {
            if(line[0] != '#')
            {
                liste = split(line,':');
                switch (liste[0][0])
                {
                    case 'm':
                        if(liste[1].compare("normal") == 0)
                        {
                            _Run_Mode = NORMAL;
                        }
                        else
                        {
                            _Run_Mode = DEBUG;
                        }
                        break;
                }
            }

        }
    }
    else
    {
        cout<<"Config File : "+url+" is missing"<<endl;
    }
}

void Config::Load_Service(string url)
{
    vector<string> temp;
    Element_Proto temp_elem;

    ifstream file(url.c_str(),ios::in);
    string line;
    vector<string> liste;
    if ( file )
    {
        while( getline(file,line) )
        {
            if(line[0] != '#')
            {
                liste = split(line,' ');
                temp_elem._num_port = string_to_int(liste[1]);
                if(liste[2].compare("tcp")==0)
                {
                    temp_elem.proto = TCP;
                }
                else
                {
                    temp_elem.proto = UDP;
                }
                temp_elem._host = liste[3];
            }
            _Liste_Proto.push_back(temp_elem);
        }
    }
    else
    {
        cout<<"Service File : "+url+" is missing"<<endl;
    }
}
