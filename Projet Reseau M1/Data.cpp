/* 
 * File:   Data.cpp
 * Author: skad
 * 
 * Created on 21 janvier 2012, 00:34
 */

#include "Data.h"

Data::Data() {
    _Data = "";
    _Ready = false;
}

Data::Data(const Data& orig) {
}

Data::~Data() {
}

void Data::Add(string chaine)
{
    _Data+=chaine;
}

string Data::Empty()
{
    string retour = _Data;
    _Data = "";
    _Ready = false;
    return retour;
}

bool Data::Is_Ready()
{
    return _Ready;
}

void Data::Set_Ready()
{
    _Ready = true;
}

int Data::Is_in(string s)
{
    int retour = -1;
    retour = _Data.find(s);
    return retour;
}