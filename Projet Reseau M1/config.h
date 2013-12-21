/* 
 * File:   config.h
 * Author: skad
 *
 * Created on 18 janvier 2012, 11:18
 */

#ifndef CONFIG_H
#define	CONFIG_H
#define NORMAL false
#define DEBUG true
#define TCP 1
#define UDP 2

#include <string>
#include <vector>
using namespace std;

typedef struct {
    int _num_port;
    int proto;
    string _host;
} Element_Proto;

class Config {
public:
    Config();
    Config(const Config& orig);
    virtual ~Config();
    void Load_Config(string url);
    void Load_Service(string url);
    vector<Element_Proto> Get_Vector_Proto();
    bool Is_Debug();
    string toString();
    ostream &operator<<( ostream & flux) {return flux<<toString();}
private:
    vector<Element_Proto> _Liste_Proto;
    bool _Run_Mode;
    string _Host_Server;

};

#endif	/* CONFIG_H */

