//============================================================
// Student Number : S10205010, S10194723
// Student Name : Lim Xiang, Yeo Wen Cong
// Team Number : 10
// Module Group : P02 
//============================================================

#include "Booking.h";

Booking::Booking() {}

Booking::Booking(int id, tm date, string guestName, Room room, string status, tm in, tm out, int guestNum, string req)
{
	this->id = id;
	this->date = date;
	this->guestName = guestName;
	this->room = room;
	this->status = status;
	this->checkIn = in;
	this->checkOut = out;
	this->numOfGuest = guestNum;
	this->specialRequest = req;
}

int Booking::getId()
{
	return id;
}

void Booking::setDate(tm d)
{
	date = d;
}

tm Booking::getDate()
{
	return date;
}

void Booking::setGuestName(string name)
{
	guestName = name;
}

string Booking::getGuestName()
{
	return guestName;
}

void Booking::setRoom(Room r)
{
	room = r;
}

Room Booking::getRoom()
{
	return room;
}

void Booking::setStatus(string s)
{
	status = s;
}

string Booking::getStatus()
{
	return status;
}

void Booking::setCheckIn(tm in)
{
	checkIn = in;
}

tm Booking::getCheckIn()
{
	return checkIn;
}

void Booking::setCheckOut(tm out)
{
	checkOut = out;
}

tm Booking::getCheckOut()
{
	return checkOut;
}

void Booking::setNumOfGuest(int num)
{
	numOfGuest = num;
}

int Booking::getNumOfGuest()
{
	return numOfGuest;
}

void Booking::setRequest(string req)
{
	specialRequest = req;
}

string Booking::getRequest()
{
	return specialRequest;
}
