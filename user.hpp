#include <string>

using namespace std;

class User{
    public :
        string name;
        string password;
        int money;
        string record;

    User(string n, string p, int m, string r){
        this->name = n;
        this->password = p;
        this ->money = m;
        this->record = r;
    }
};
