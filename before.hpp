#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>

#include <unistd.h>

#include "user.hpp"
#include "Snail.hpp"

#define MAP 30
#define MINSPEED 1
#define MAXSPEED 100
#define RATE 2

using namespace std;

// 모든 유저의 객체, Data 저장.
extern vector<User> users;
// 전역변수 user 중 현재 login한 User의 index. default는 -1.
extern int current_login;
// 모든 달팽이의 객체 저장.
extern vector<Snail*> snail;

void race_start();
void loadFile(ifstream fp);
