#include <stdio.h>
#include "before.hpp"

vector<User> users;
int current_login = -1;
vector<Snail*> snail(5);
void show_menu();
bool login(vector<User> users, string id, string password) {

	for (int i = 0; i < users.size(); i++) {
		if (id == users[i].name) {
			if (password == users[i].password) {
				current_login = i;
				return true;
			}
		}
	}
	return false;
}


void my_page() {
	system("clear");
	cout << " ▶   My Page   ◀" << endl;
	cout << " ID : " << users.at(current_login).name << endl;
	cout << " My Money : " << users.at(current_login).money << endl << endl;
	cout << " < Race Record >" << endl;
	for (int i = 0; i < users.at(current_login).record.length(); i++) {
		cout << " Race  " << i + 1 << " : ";
		if (users.at(current_login).record[i] == '1')
			cout << " Win" << endl;
		else
			cout << " Lose" << endl;
	}
	cout << endl;
}

void charge_money() {
	system("clear");
	if (users.at(current_login).money == 0) {
		do {
			cout << " Amount to charge (1~100,000) ▶ ";
			int charge;
			cin >> charge;
			if (charge > 1 && charge < 100000) {
				users.at(current_login).money = charge;
				cout <<" "<< charge << " Won charged." << endl;
				//save data
				//FILE* fp2;
				//fp2 = fopen("./userinfo.txt", "w");
				//if (fp2 == NULL) {
				//	printf(" fail to save \n");
				//}
				//for (int i = 0; i < users.size(); i++) {
				//	string m = to_string(users.at(i).money);
				//	string temp = users.at(i).name + "\n" + users.at(i).password + "\n" + m + "\n" + users.at(i).record;
				//	const char* name = temp.c_str();
				//	fwrite(name, 1, temp.size(), fp2);
				//}
				//fclose(fp2);
				ofstream out("./userinfo.txt");
				if (out.is_open()) {
					for (int i = 0; i < users.size(); i++) {
						out << users.at(i).name << endl;
						out << users.at(i).password << endl;
						out << to_string(users.at(i).money) << endl;
						out << users.at(i).record << endl;
					}
				}
				break;
			}
			else {
				cout << " You can charge 1~100,000 Won!" << endl;
			}
		} while (true);

	}
	else {
		cout << "=================================================================" << endl;
		cout << " You can't charge. When you run out of money, you can charge it.." << endl;
		cout << "=================================================================" << endl;
	}
	cout << endl;
}


int main() {

	ifstream fp;

	//fp .open("/home/noakfakf/바탕화면/workspace/noa/userinfo.txt");
	fp.open("./userinfo.txt");
	//if(fp == NULL){
	//    printf("fail \n");
	//    return 1;
	//}

   // loadFile(fp);
	char buf[1024];

	if (fp.is_open()) {
		while (!fp.eof())
		{
			fp.getline(buf, sizeof(buf));
			if (buf == "")
				break;
			string name = buf;
			fp.getline(buf, sizeof(buf));
			string password = buf;
			fp.getline(buf, sizeof(buf));
			string t = buf;
			int money = atoi(t.c_str());
			fp.getline(buf, sizeof(buf));
			string record = buf;
			users.push_back(User(name, password, money, record));
		}
	}
	else {
		return 0;
	}

	for (int i = 0; i < users.size(); i++) {
		cout << users[i].name << endl;
		cout << users[i].password << endl;
		cout << users[i].money << endl;
		cout << users[i].record << endl;
	}
	fp.close();

	system("clear");
	// Login
	while (1)
	{
		int num;
		cout << " ▶   MENU   ◀" << endl;
		cout << " 1) Login\n 2) Join\n 3) Exit\n" << endl;
		cout << " Select Menu ▶ ";
		cin >> num;
		if (num == 1) {
			system("clear");
			cout << " ▶ Login ◀" << endl;
			string t1;
			string t2;
			cout << " ID ▶ ";
			cin >> t1;
			cout << " PW ▶ ";
			cin >> t2;
			if (login(users, t1, t2)) {
				//cout << "login success" << endl;
				show_menu();
			}
			else {
				cout << " No member information." << endl;
			}
		}
		else if (num == 2) {
			system("clear");
			cout << " ▶ Join ◀" << endl;
			string t1;
			string t2;
			do {
				cout << " ID ▶ ";
				cin >> t1;
				bool flag = true;
				for (int i = 0; i < users.size(); i++) {
					if (users.at(i).name == t1)
						flag = false;
				}
				if (flag == false) {
					cout << " This ID already taken. Please try another one !" << endl;
					continue;
				}
				break;
			} while (true);
			cout << " PW ▶ ";
			cin >> t2;
			users.push_back(User(t1, t2, 0, ""));
			cout << " Join Success !" << endl;
			ofstream out("./userinfo.txt");
			if (out.is_open()) {
				for (int i = 0; i < users.size(); i++) {
					out << users.at(i).name << endl;
					out << users.at(i).password << endl;
					out << to_string(users.at(i).money) << endl;
					out << users.at(i).record << endl;
				}
			}
		}
		else if (num == 3) {
			exit(0);
		}
		else {
			cout << " Invalid input." << endl;
		}
	}
	return 0;
}

void show_menu() {
	int menu;
	system("clear");
	do {
		cout << " ▶   MENU   ◀" << endl;
		cout << " 1) Race\n 2) My Page\n 3) Charging\n 4) Logout\n" << endl;
		cout << " Select Menu ▶ ";
		cin >> menu;
		switch (menu) {
		case 1:
			race_start();
			break;
		case 2:
			my_page();
			break;
		case 3:
			charge_money();
			break;
		case 4:
			system("clear");
			cout << " Succesfully logged out." << endl;
			break;
		default:
			cout << " Invalid input." << endl;
			break;
		}
	} while (menu != 4);
}