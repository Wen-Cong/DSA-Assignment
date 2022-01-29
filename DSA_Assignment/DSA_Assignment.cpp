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
string fromDateTime(tm date);
void initRoomData(Dictionary_Room& roomList, Dictionary_Price& priceList);
void initBookingData(BST_Booking& bookingList, Dictionary_Room roomList, Dictionary_Price priceList);
void displayMainMenu();
string convertOptionToRoomTypeName(string opt);
bool addNewBooking(BST_Booking& bookingList, Booking b);

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
            string guestName;
            string numOfGuest;
            string specReq;

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

            // Check availability of room based on room type, check in date and check out date.
            int numOfRoomsOccupied = bookingList.searchRange(in, out, roomType);
            int totalNumOfRoom = priceList.get(roomType).count;
            // All rooms of selected type are occupied or booked during this date range
            if (numOfRoomsOccupied == totalNumOfRoom) 
            {
                cout << endl << roomType << " rooms are fully occupied during selected time.\n";
                cout << "Please choose another date or room. Thank You!\n\n";
                continue;
            }
            else {
                cout << "\nAvailable Rooms Found.\n\n";
            }

            // Prompt user for guest name, number of guest and special request
            cout << "Please Enter Name of Representative: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, guestName);
            cout << "Please Enter the Number of Guest: ";
            cin >> numOfGuest;
            cout << "Please Enter Special Request (If any): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, specReq);

            // Get current date time to be set as booking time
            time_t t = time(0); // get current time
            tm now = tm();
            localtime_s(&now, &t); // Convert to tm type
            now.tm_year += 1900; // Convert from year since 1900 to human readable year
            now.tm_mon++; // Month generated would be indexed starting from 0, hence add 1 to make it human readable

            // Get new booking id for latest booking added
            int bookingId = bookingList.countNodes() + 1;

            // Set price and room type into room object to be added to booking object
            Room r = Room();
            r.setPrice(priceList.get(roomType).price);
            r.setType(roomType);

            // Define status and convert number of guest to int to be added to booking object
            int guestNum = toInt(numOfGuest);
            string status = "Booked";
            Booking b = Booking(bookingId, now, guestName, r, status, in, out, guestNum, specReq);

            // Add new booking created to book list and update Excel file
            addNewBooking(bookingList, b);
            // Display sucess message upon new booking added
            cout << endl << "Your booking has been created successfully!\n\n";

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
    char aString[17];
    strcpy_s(aString, dateString.c_str());
    sscanf_s(aString, "%d/%d/%4d  %d:%d",
        &date.tm_mday, &date.tm_mon, &date.tm_year, &date.tm_hour, &date.tm_min);

    return date;
}

string fromDateTime(tm date) {
    // Convert tm type to string in (dd/mm/yyyy) format
    string dateStr = "";
    // Append year, month and day
    dateStr = to_string(date.tm_mday) + "/" + to_string(date.tm_mon) + "/" + to_string(date.tm_year);
    // If hour and minute is found, append hour and minute
    if (date.tm_hour != NULL && date.tm_min != NULL) {
        dateStr += " " + to_string(date.tm_hour) + ":" + to_string(date.tm_min);
    }

    return dateStr;
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

            // Append to room list
            Room r = Room(roomNum, roomType, price);
            roomList.add(roomNum, r);

            // Append to price list
            PriceRoomType rt = PriceRoomType();
            rt.price = price;
            rt.count = 1;
            priceList.add(roomType, rt);
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
                double price = priceList.get(bRoomType).price;
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
        return "President Suite";
    }
    else if (opt == "2")
    {
        return "Standard City View";
    }

    else if (opt == "3")
    {
        return "Deluxe City View";
    }
    else if (opt == "4")
    {
        return "Executive Sea View";
    }
    else
    {
        cout << "Invalid Option\n\n";
        return "";
    }
}

bool addNewBooking(BST_Booking& bookingList, Booking b) {
    // Insert data into booking list
    bookingList.insert(b);
    // Insert data into Excel file
    ofstream csvFile;
    // Open Bookings csv File in append mode
    csvFile.open("Bookings.csv", ios::app);
    // Check if file open successfully
    if (csvFile.is_open()) {
        // Convert data to string
        string inStr = fromDateTime(b.getCheckIn());
        string outStr = fromDateTime(b.getCheckOut());
        string bDateStr = fromDateTime(b.getDate());
        string roomNumStr = "";
        if (b.getRoom().getRoomNum() >= 0)
            roomNumStr = "Room " + to_string(b.getRoom().getRoomNum());

        // Write new row into booking csv file
        csvFile << b.getId() << ", " << bDateStr << ", " << b.getGuestName() << ", " << roomNumStr << ", ";
        csvFile << b.getRoom().getType() << ", " << b.getStatus() << ", " << inStr << ", " << outStr << ", ";
        csvFile << b.getNumOfGuest() << ", " << b.getRequest() << endl;
    }
    // Close file
    csvFile.close();

    return true;
}