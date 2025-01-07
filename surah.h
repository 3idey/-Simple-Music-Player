#ifndef SURAH_H
#define SURAH_H
#include <iostream>
#include <string>
using namespace std;
class surah
{
private:
    string name;
    string audiopath;
    string type;
public:
    surah(const string& name="",const string& type="", const string& audiopath="")
        :name(name),type(type),audiopath(audiopath) {}

    string getname() const
    {
        return name;
    }

    string gettype()const
    {
        return type;
    }
    string getaudiopath()const
    {
        return audiopath;
    }
    void setname(const string& name)
    {
        this->name=name;
    }

    void settype(const string& type)
    {
        this->type=type;
    }
    void setaudiopath(const string& audiopath)
    {
        this->audiopath=audiopath;
    }
    void display() const
    {

        cout  << getname() << "        "
              << gettype() << "        "
              << getaudiopath() << endl;
    }

    

};
#endif
