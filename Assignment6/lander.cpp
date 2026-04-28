#include "lander.h"
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

const int TIME = 1; //1 second of time for the simulation function

lander::lander(string name, double mass, double thrust, double max_fuel,
						double alt, double fuel)
{
	lander_mass = mass;
	max_thrust = thrust;
	max_fuel_consumption_rate = max_fuel;

	stillLanding = true;
	flow_rate = 0.0;
	velocity = 0.0;
	altitude = alt;
	fuel_amount = fuel;
	this->name = name;
}


char lander::get_status() const
{
	// if crashed
	if (altitude <= 0 && velocity <= -2) {
		return 'c';
	} 
	
	// if landed successfully
	else if (altitude <= 0 && velocity > -2) {
		return 'l';
	} 
	
	// if still airborne
	return 'a';
}

bool lander::change_flow_rate(double r)
{
	// is there's no fuel
	if (fuel_amount == 0) {
		flow_rate = 0;
	}
	
	// if r is between 0 and 1 (inclusive)
	if (r <= 1 && r >= 0) {
		// flow rate = r IF fuel amount is LARGER than 0, return true
		if (fuel_amount > 0) {
			flow_rate = r;
			return true;
		}
	} 
	
	// if r is NOT between 0 and 1
	return false;
}

void lander::simulate()
{
	// if lander is still airborne
	if (altitude > 0) {
		// calculate instantaneous velocity
		double v = TIME * ((flow_rate * max_thrust) / (lander_mass + fuel_amount)) - 1.62;

		// increment/update velocity field by v
		velocity += v;
		// increment/update altitude field by TIME * velocity field
		altitude += TIME * velocity;

		// update still landing if necessary
		if (altitude <= 0) {
			stillLanding = false;
		}

		// decrement/update fuel_amount by TIME * max_fuel_rate * |v|
		if (flow_rate > 0) {
			fuel_amount -= TIME * max_fuel_consumption_rate * abs(v);
		}
		
		// if fuel amount went negative, make it zero
		if (fuel_amount < 0) {
			fuel_amount = 0;
		}
	}
}

bool lander::operator<(const lander& rhs) const
{
    // check which altitude is lower
    if (altitude != rhs.altitude) {
        return altitude < rhs.altitude;
	}

    // check which fuel is lower
    if (fuel_amount != rhs.fuel_amount) {
        return fuel_amount < rhs.fuel_amount;
	}

    // check which mass is lower
    if (lander_mass != rhs.lander_mass) {
        return lander_mass > rhs.lander_mass;
	}
    
	// check which name is earlier in alphabet as final decider
    return name < rhs.name;
}

