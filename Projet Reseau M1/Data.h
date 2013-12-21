/* 
 * File:   Data.h
 * Author: skad
 *
 * Created on 21 janvier 2012, 00:34
 */

#ifndef DATA_H
#define	DATA_H
#include <string>
#define SERVER 0
#define CLIENT 1
using namespace std;
class Data {
public:
    Data();
    Data(const Data& orig);
    virtual ~Data();
    void Add(string);
    string Empty();
    bool Is_Ready();
    void Set_Ready();
    void SetOrigin(int _Origin) {
        this->_Origin = _Origin;
    }
    int GetOrigin() const {
        return _Origin;
    }
    int Is_in(string);
private:
    string _Data;
    bool _Ready;
    int _Origin;
};

#endif	/* DATA_H */

