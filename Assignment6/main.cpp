#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "priorityQ.h"
#include "lander.h"
using namespace std;

void topThreeLanders(priorityQ<string,lander>& input) {
	// save names and landers to push back later
	string names[3];
	lander landers[3];
	int count = 0;

	for (int i = 0 ; i < 3; ++i) {
		// if there are no landers to print
		if (input.isEmpty()) {
			break;
		}

		// get information of lander
		string name = input.get_front_key();
		lander obj = input.get_element(name);

		cout << "(" << i+1 << ") Name: " << name << " "  
			<< fixed << setprecision(6) 
			<< obj.get_altitude() << " meters from the moon surface" << endl
			<< "traveling at " << obj.get_velocity() << " m/s" << endl
			<< "Fuel: " << obj.get_fuel_amount() << endl << endl; 
		
		// update arrays
		names[count] = name;
		landers[count] = obj;
		++count;

		input.pop_front();
	}

	for (int i = 0 ; i < count ; ++i) {
		input.push_back(names[i], landers[i]);
	}
}

int main()
{
	priorityQ<string, lander> raceToTheMoon;
	ifstream infile("LanderInput.txt");
	double mass, max_thrust, max_fuel, alt, fuel;
	string name;

	// read into file each variable
	while (infile >> name >> mass >> max_thrust >> max_fuel >> alt >> fuel) {
		// create lander object
		lander obj(name, mass, max_thrust, max_fuel, alt, fuel);

		// insert using push_back to the priorityQ obj
		raceToTheMoon.push_back(name, obj);
	}

	// output the top 3 landers 
	topThreeLanders(raceToTheMoon);
	
	while (true) {
		string landerName;
		double throttleAmount;
		cout << "Enter lander name and throttle amount: ";
		cin >> landerName >> throttleAmount;
		cout << endl;

		// get users chosen lander
		lander current = raceToTheMoon.get_element(landerName);
		// cout << current.get_name();
		// update landers flow amount
		current.change_flow_rate(throttleAmount);
		// simulate it
		current.simulate();
		// update lander on priorityQueue
		raceToTheMoon.update_element(landerName, current);

		if (current.get_status() == 'c') {
			cout << landerName << " crashed :(" << endl;

			raceToTheMoon.pop_front();
		} 
		else if (current.get_status() == 'l') {
			cout << landerName << " landed :)" << endl;

			raceToTheMoon.pop_front();
		}

		// output the top 3 landers 
		topThreeLanders(raceToTheMoon);

		if (raceToTheMoon.isEmpty()) {
			break;
		}
	}

	return 0;
}

