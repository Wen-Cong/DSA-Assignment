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
#include "BST_Booking.h"
#include "BST_Checkin.h"
#include "Dictionary_Room.h"
#include "Dictionary_Price.h"
#include "Booking.h"
using namespace std;

int toInt(string text);
tm toDateTime(string dateString);
void initRoomData(Dictionary_Room& roomList, Dictionary_Price& priceList);
void initBookingData(BST_Booking& bookingList, Dictionary_Room roomList, Dictionary_Price priceList);
void displayMainMenu();
string convertOptionToRoomTypeName(string opt);

int main()
{
    cout << "Initialising Data, Please wait..." << endl << endl;
    // Initialise room data using dictionary data structure
    BST_Booking bookingList = BST_Booking();
    Dictionary_Room roomList = Dictionary_Room();
    Dictionary_Price priceList = Dictionary_Price();
    initRoomData(roomList, priceList);
    initBookingData(bookingList, roomList, priceList);


    string choice;
    while (choice != "0")
    {
        // Display main menu options
        displayMainMenu();

        cin >> choice;
        if (choice == "0")
            break;

        else if (choice == "1")
        {
            // TO DO
        }

        else if (choice == "2")
        {
            // Add booking Use Case
            string checkIn;
            string checkOut;
            string roomTypeChoice;
            cout << "\n===================== ADD BOOKING =====================\n";
            // Display all rooms type and respective price tags
            priceList.print();
            // Prompt user for room type choice, check in date and check out date
            cout << "\nPlease Choose a Room Type: ";
            cin >> roomTypeChoice;
            cout << "Please Enter Check In Date (dd/mm/yyyy): ";
            cin >> checkIn;
            cout << "Please Enter Check Out Date (dd/mm/yyyy): ";
            cin >> checkOut;

            tm in = toDateTime(checkIn);
            tm out = toDateTime(checkOut);
            string roomType = convertOptionToRoomTypeName(roomTypeChoice);
        }

        else if (choice == "3")
        {
            // TO DO
        }

        else if (choice == "4")
        {
            // TO DO
        }

        else
        {
            cout << "Invalid Option\n\n";
            continue;
        }
    }
}

int toInt(string text) {
    stringstream intValue(text);
    int number = 0;
    intValue >> number;
    return number;
}

tm toDateTime(string dateString) {
    // Convert string to tm type
    tm date = tm();
    // Date time with hour and minute parameter
    if (dateString.length() == 16) {
        char aString[17];
        strcpy_s(aString, dateString.c_str());
        sscanf_s(aString, "%d/%d/%4d  %d:%d",
            &date.tm_mday, &date.tm_mon, &date.tm_year, &date.tm_hour, &date.tm_min);
    }
    // Date time with only day, month and year
    else if (dateString.length() == 10) {
        char aString[11];
        strcpy_s(aString, dateString.c_str());
        sscanf_s(aString, "%d/%d/%4d",
            &date.tm_mday, &date.tm_mon, &date.tm_year);
    }

    return date;
}

void initRoomData(Dictionary_Room& roomList, Dictionary_Price& priceList) {
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
            priceList.add(roomType, price);
        }
    }

    // Close file stream
    inputFile.close();
}

void initBookingData(BST_Booking& bookingList, Dictionary_Room roomList, Dictionary_Price priceList) {
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
            Room bookedRoom = roomList.get(roomNum);
            if (bookedRoom.getRoomNum() == NULL) {
                // Find price for room type retrieve set room price for bookedRoom
                double price = priceList.get(bRoomType);
                // Set price and room type into room object
                bookedRoom.setType(bRoomType);
                bookedRoom.setPrice(price);
            }

            Booking b = Booking(id, date, bGuestName, bookedRoom, bStatus, in, out, guestNum, bReq);
            bookingList.insert(b);
        }
    }

    // Close file stream
    inputFile.close();
}

void displayMainMenu() {
    cout << "===================== MAIN MENU =====================\n";
    cout << "[1] Check In Guest\n";
    cout << "[2] Add Booking\n";
    cout << "[3] Display Staying Guest by Date\n";
    cout << "[4] Display Occupied Rooms by Month\n";
    cout << "[0] Exit\n";
    cout << "Your Choice: ";
}

string convertOptionToRoomTypeName(string opt) {
    if (opt == "1")
    {
        return "Executive Sea View";
    }
    else if (opt == "2")
    {
        return "President Suite";
    }

    else if (opt == "3")
    {
        return "Deluxe City View";
    }
    else if (opt == "4")
    {
        return "Standard City View";
    }
    else
    {
        cout << "Invalid Option\n\n";
        return "";
    }
}