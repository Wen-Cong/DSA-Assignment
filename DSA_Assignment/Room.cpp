#include "Room.h"{}

Room::Room(){}

Room::Room(int roomNum, string type, double price)
{
	this->roomNumber = roomNum;
	this->type = type;
	this->price = price;
}

void Room::setRoomNum(int r) { roomNumber = r; }

int Room::getRoomNum() { return roomNumber;  }

void Room::setType(string t) { type = t; }

string Room::getType() { return type; }

void Room::setPrice(double p) { price = p; }2

double Room::getPrice() { return price; }