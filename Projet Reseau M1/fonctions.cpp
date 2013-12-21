#include "fonctions.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
# include <stdlib.h>
using namespace std;

vector<string> split(string chaine, const char c)
{

    vector<string> retour;

    int pos;
    string substring = chaine;
    while(substring.find(c,0) != -1)
    {
        pos = substring.find(c,0);
        retour.push_back(substring.substr(0,pos));
        substring = substring.substr(pos+1,substring.size()-pos);
    }
    retour.push_back(substring);
    return retour;
}

string int_to_string(int i)
{
    stringstream temp;
    temp<<i;
    return temp.str();

}

int string_to_int(string s)
{
    return atoi(s.c_str());
}
