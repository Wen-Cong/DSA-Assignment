//============================================================
// Student Number : S10205010, S10194723
// Student Name : Lim Xiang, Yeo Wen Cong
// Team Number : 10
// Module Group : P02 
//============================================================
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