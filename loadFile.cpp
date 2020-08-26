#include "before.hpp"

void loadFile(ifstream fp) {
	char buf[1024];

	if(fp.is_open()){
		while (!fp.eof())
		{
			fp.getline(buf, sizeof(buf));
			string name = buf;
			fp.getline(buf, sizeof(buf));
			string password = buf;
			fp.getline(buf, sizeof(buf));
			int money = stoi((string)buf);
			fp.getline(buf, sizeof(buf));
			string record = buf;
			users.push_back(User(name,password,money,record));
		}
	}
}
