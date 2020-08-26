#include "before.hpp"
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>

pid_t r_wait(int* stat_loc) {
	int retval;
	while (((retval = wait(stat_loc)) == -1) && (errno == EINTR));
	return retval;
}


void gotoxy(int x, int y)
{
	printf(" \033[%d;%df", y, x);
	//fflush(stdout);
}

void race_start()
{
	if (users.at(current_login).money == 0) {
		cout << "=============================================================" << endl;
		cout << " Charge the money. You are not allowed to participate in betting." << endl;
		cout << "=============================================================" << endl;
		return;
	}
	int signal[5];
	//show snail data
	srand((unsigned int)time(NULL));

	int charNum[5] = {
	   0,
	};
	bool checkExist[5] = {
	   false,
	};

	for (int i = 0; i < 5;)
	{
		/* Make Snail Info */
		int character = (rand() % 5);

		if (checkExist[character] == false)
		{
			checkExist[character] = true;
			charNum[i] = character;
			Snail* babySnail = new Snail(character);
			snail[i] = babySnail;
			++i;
		}
	}

	//bet

	system("clear");
	for (int i = 0; i < snail.size(); i++)
	{
		cout << "================================" << endl;
		cout << " [ Snail " << i + 1 <<" ]"<< endl;
		cout << " Weight : " << snail[i]->weight << endl;
		cout << " Age : " << snail[i]->age << endl;
		string tempchar;
		switch (snail[i]->character)
		{
		case 0:
			tempchar = "Diligent"; break;
		case 1:
			tempchar = "Unpredictable"; break;
		case 2:
			tempchar = "Shy"; break;
		case 3:
			tempchar = "Lonely"; break;
		case 4:
			tempchar = "A matchmaker"; break;
		default:
			break;
		}
		cout << " Characteristic : " << tempchar << endl;
		cout << " MIN SPEED : " << snail[i]->minSpeed << " ~ MAX SPEED : " << snail[i]->maxSpeed << endl;
	}
	cout << "================================" << endl;
	int goal, goalmoney;
	do {
		cout << " Who's the No. 1 snail ? ▶ ";
		cin >> goal;
		if (goal >= 1 && goal <= 5) {
			do {
				cout << "\n How much do you want to bet ? ▶ ";
				cin >> goalmoney;
				if (goalmoney <= users.at(current_login).money) {
					system("clear");
					cout << " You bet " << goalmoney << " won on the snail [" << goal << "]" << endl;
					break;
				}
				else {
					cout << " You have" << users.at(current_login).money << "Won. Please re-enter. " << endl;
				}
			} while (true);
			break;
		}
		else {
			cout << " Invalid input" << endl;
		}
	} while (true);


	//Clear Screen
	
	cout << " ▶ Let's Start The Race ! ◀" << endl;
	// Do Fork to Make 5 Snails.
	int snail_index = 0;
	int pid = -1;
	for (snail_index = 0; snail_index < 5; snail_index++)
	{
		pid = fork();
		if (pid <= 0)
			break;
	}
	//내가 몇번 달팽이인지 알아야해
	if (pid == 0)
	{
		Snail* s = snail[snail_index];
		// /* In a Race */
		int distance = 3000;
		int now = 1;
		int phase = 1;
		int show = 0;
		int new_index = snail_index;
		while (now < distance)
		{
			int tempSpeed = (rand() % (s->maxSpeed - s->minSpeed + 1)) + s->minSpeed;
			now += tempSpeed; //tempSpeed 나이랑 성격 무게 계수를 곱해줘야하니까
			//달팽이출력
			show = (int)(now / (distance / MAP));
			gotoxy(0, new_index*2 + 4);
			for (int i = 0; i < show; i++)
			{
				cout << "~";
			}
			cout << "@_i " << new_index + 1 << endl;
			sleep(1);
			phase++;

		}
		exit(new_index);
	}
	else
	{
		//벡터로 해서 1등 알아야됨
		for (int i = 0; i < 5; i++)
			r_wait(&signal[i]);

		vector<int> rank;
		for (int i = 0; i < 5; i++)
			rank.push_back(WEXITSTATUS(signal[i]));

		/* Temporary Print */
		gotoxy(0, 14);
		cout << " RANK ▶ ";
		for (int e : rank)
			cout << e+1 << " ";
		cout << endl;

		//결과에 따라서 상금지금 or 그냥 아웃
		cout << " Your prediction ▶ " << goal << endl;
		cout << " No. 1 Snail ▶ " << rank[0]+1 << endl;
		cout << "=====================================" << endl;
		if (goal == rank[0] + 1) {
			cout << " Win! You got " << goalmoney * 2 << " Won!" << endl;
			users.at(current_login).money += goalmoney;
			users.at(current_login).record += "1";
		}
		else {
			cout << " Lose! You lost " << goalmoney << " Won!" << endl;
			users.at(current_login).money -= goalmoney;
			users.at(current_login).record += "0";
		}
		cout << "=====================================" << endl;
		cout << endl;
	}
	users.at(current_login).money *= 2;

	//save data
	//FILE* fp2;
	//fp2 = fopen("./userinfo.txt", "w");
	//if (fp2 == NULL) {
	//	printf(" fail to save \n");
	//}
	//for (int i = 0; i < users.size(); i++) {
	//	string m = to_string(users.at(i).money);
	//	string temp = users.at(i).name + "\n" + users.at(i).password + "\n" + m + "\n" + users.at(i).record+"\n";
	//	//const char* name = temp.c_str();
	//	fwrite(temp, 1, temp.size(), fp2);
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
	//  /* Delete Snail Info */
	for (int i = 0; i < 5; i++)
		delete snail[i];
	return;
}
