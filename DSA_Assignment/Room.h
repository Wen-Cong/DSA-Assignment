#pragma once

#include <string>
using namespace std;

class Room {
private: 
    int roomNumber;
    string type;
    double price;

public:
	Room();
	Room(int roomNum, string type, double price);
	void setRoomNum(int r);
	int getRoomNum();
	void setType(string t);
	string getType();
	void setPrice(double p);
	double getPrice();
};