#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>

using namespace std;

class Snail
{
public:
	Snail() {	};
	~Snail() {};
	int index;

	int weight;						//��� ��					
	int age;							//��� ��
	int minSpeed, maxSpeed;		//�� �� ��
	int character;			
	
	bool sincerity_flag ;
	bool shy_flag ;
	bool lonely_flag ;
	bool adventure_flag ;

	Snail(int character)
		:character(character)
	{		

		this->sincerity_flag = false;
		this->shy_flag = false;
		this->lonely_flag = false;
		this->adventure_flag = false;

		weight = (rand() % 20) + 1;		//1kg ~ 20kg
		age = (rand() % 5) + 1;				//1years ~ 5years
		//cout<<"달팽이 나이 : "<<age<<endl;
		minSpeed = 50-(weight*age/4);		// default : 50 -> 25~50
		maxSpeed = 100-(weight*age/4);	//default : 100 -> 75~100

		switch(character){
			case 0:
				//sincerity
				sincerity_flag = true;
				break;
			case 1:
				//moodiness
				minSpeed /= 1.3;
				maxSpeed *= 1.3;
				break;
			case 2:
				//shyness
				shy_flag = true;
				break;
			case 3:
				//loneliness
				lonely_flag = true;
				break;
			case 4:
				//adventurer
				adventure_flag = true;
				break;
		}
		//cout<< "character : "<< character <<endl;
	}
};
