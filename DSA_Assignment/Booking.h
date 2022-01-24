#pragma once

#include <string>
#include <time.h>
#include "Room.h"
using namespace std;

class Booking {
private:
    int id;
    tm date;
    string guestName;
    Room room;
    string status;
    tm checkIn;
    tm checkOut;
    int numOfGuest;
    string specialRequest;

public:
    Booking();
    Booking(int id, tm date, string guestName, Room room, string status, tm in, tm out, int guestNum, string req);
    int getId();
    void setDate(tm d);
    tm getDate();
    void setGuestName(string name);
    string getGuestName();
    void setRoom(Room r);
    Room getRoom();
    void setStatus(string s);
    string getStatus();
    void setCheckIn(tm in);
    tm getCheckIn();
    void setCheckOut(tm out);
    tm getCheckOut();
    void setNumOfGuest(int num);
    int getNumOfGuest();
    void setRequest(string req);
    string getRequest();
};