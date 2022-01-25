//============================================================
// Student Number : S10205010, S10194723
// Student Name : Lim Xiang, Yeo Wen Cong
// Team Number : 10
// Module Group : P02 
//============================================================
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Room.h"
#include "Dictionary.h"
#include "BST.h"
#include "Booking.h"
using namespace std;

int toInt(string text);
tm toDateTime(string dateString);
void initRoomData(Dictionary& roomList);
void initBookingData(BST& bookingList, Dictionary roomList);

int main()
{
    // Initialise room data using dictionary data structure
    Dictionary roomList = Dictionary();
    initRoomData(roomList);
    roomList.print();
}

int toInt(string text) {
    stringstream intValue(text);
    int number = 0;
    intValue >> number;
    return number;
}

tm toDateTime(string dateString) {
    // TO-DO: Convert string to tm type
    return tm();
}

void initRoomData(Dictionary& roomList) {
    // Open room csv file and import room data
    ifstream inputFile;
    inputFile.open("Rooms.csv");

    // Check if file open successfully
    if (inputFile.is_open()) {
        // Initialise variables
        string roomNumberString;
        string roomType;
        string roomPrice;

        // Skip the first row (header) in file
        getline(inputFile, roomNumberString, ',');
        getline(inputFile, roomType, ',');
        getline(inputFile, roomPrice);

        // Read room csv data row while it still have rows
        while (!inputFile.eof()) {
            getline(inputFile, roomNumberString, ',');
            getline(inputFile, roomType, ',');
            getline(inputFile, roomPrice);

            // Remove the first 4 char "Room" and convert reamining char from string to integer
            int roomNum = toInt(roomNumberString.erase(0, 4));
            // Convert string to double for price
            double price = stod(roomPrice);

            Room r = Room(roomNum, roomType, price);
            roomList.add(roomNum, r);
        }
    }

    // Close file stream
    inputFile.close();
}

void initBookingData(BST& bookingList, Dictionary roomList) {
    // Open booking csv file and import booking data
    ifstream inputFile;
    inputFile.open("Bookings.csv");

    // Check if file open successfully
    if (inputFile.is_open()) {
        // Initialise variables
        string bId;
        string bDate;
        string bGuestName;
        string bRoomNumber;
        string bRoomType;
        string bStatus;
        string bIn;
        string bOut;
        string bGuestNum;
        string bReq;

        // Skip the first row (header) in file
        getline(inputFile, bId, ',');
        getline(inputFile, bDate, ',');
        getline(inputFile, bGuestName, ',');
        getline(inputFile, bRoomNumber, ',');
        getline(inputFile, bRoomType, ',');
        getline(inputFile, bStatus, ',');
        getline(inputFile, bIn, ',');
        getline(inputFile, bOut, ',');
        getline(inputFile, bGuestNum, ',');
        getline(inputFile, bReq);

        // Read room csv data row while it still have rows
        while (!inputFile.eof()) {
            getline(inputFile, bId, ',');
            getline(inputFile, bDate, ',');
            getline(inputFile, bGuestName, ',');
            getline(inputFile, bRoomNumber, ',');
            getline(inputFile, bRoomType, ',');
            getline(inputFile, bStatus, ',');
            getline(inputFile, bIn, ',');
            getline(inputFile, bOut, ',');
            getline(inputFile, bGuestNum, ',');
            getline(inputFile, bReq);

            // Remove the first 4 char "Room" and convert reamining char from string to integer
            int roomNum = toInt(bRoomNumber.erase(0, 4));
            // Convert booking ID and Number of Guest to int
            int id = toInt(bId);
            int guestNum = toInt(bGuestNum);
            // Convert booking date, checkin date, checkout date from string to time
            tm date = toDateTime(bDate);
            tm in = toDateTime(bIn);
            tm out = toDateTime(bOut);
            // Get room item from room list using room number
            Room bookedRoom = (Room) (roomList.get(roomNum));
            if (bookedRoom.getRoomNum() == NULL) {
                bookedRoom.setType(bRoomType);
                // TO-DO: Find price for room type retrieve set room price for bookedRoom
            }

            Booking b = Booking(id, date, bGuestName, bookedRoom, bStatus, in, out, guestNum, bReq);
            //bookingList.insert(b);
        }
    }

    // Close file stream
    inputFile.close();
}