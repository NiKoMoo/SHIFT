// Sleeping_Barber_Problem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <vector>
using namespace std;

mutex m;
int M;//M seats in the waiting room
int WaitingPeople;//People waiting for the barber
int LeavingPeople;//numbers of leaving people when seats are not available
int ID;//integer serves as customer's ID
int Customer;//customer's ID who is having haircut
int n;//control the function which generates customer
vector<int>WaitingRoom;//store the ID who are in waiting room

void Sleeping()
{
	while (WaitingPeople == 0)
	{
		cout << "Barber sleeping\n";
		cout << "Waiting room: \n";
	}
}

void ArrivingPeople(int a)
{
	while (true)
	{
		m.lock();
		if (n == 0)
		{
			ID = a;
			ID++;
			n++;
		}
		else
		{
			ID++;
		}
		WaitingPeople++;

		if (WaitingPeople > M)//there is no available seats in waiting room 
		{
			LeavingPeople++;
		}
		else
		{
			WaitingRoom.push_back(ID);
			//cout << "Waiting room added " << ID << endl;
		}

		this_thread::sleep_for(3s);
		m.unlock();
		n++;
	}

}

void Working(int a)
{
	while (WaitingPeople != 0)
	{
		m.lock();
		int N = rand() % 5 + 1;
		Customer = a;

		cout << "Barber cutting the hair of customer " << Customer << endl;
		cout << "Waiting room: ";
		for (int i = 0; i < WaitingRoom.size(); i++)
		{
			cout << WaitingRoom[i] << " ";
		}
		cout << "\n";
		Sleep(N * 1000);
		if (WaitingPeople > M)
			cout << "Customer " << ID << " leaving " << endl;
		m.unlock();
	}
}

int main()
{
	
	cout << "Please enter the seats in waiting room:";
	cin >> M;
	WaitingPeople = 0;
	LeavingPeople = 0;
	ID = 0;
	n = 0;

	thread SleepingThread(Sleeping);
	thread CreateThread(ArrivingPeople, 12);
	thread WorkingThread(Working,12);

	SleepingThread.join();
	CreateThread.join();
	WorkingThread.join();

	system("pause");
	return 0;
}