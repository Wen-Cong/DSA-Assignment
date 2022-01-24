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
using namespace std;

int toInt(string text);

int main()
{
    // Initialise dictionary data structure list for rooms
    Dictionary roomList = Dictionary();

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

            // Remove the first 5 char "Room " and convert reamining char from string to integer
            int roomNum = toInt(roomNumberString.erase(0, 4));
            // Convert string to double for price
            double price = stod(roomPrice);

            Room r = Room(roomNum, roomType, price);
            //roomList.add(roomNum, r);
            cout << roomNum << " " << roomType << " " << price << endl;
        }
    }
    // Close file stream
    inputFile.close();
}

int toInt(string text) {
    stringstream intValue(text);
    int number = 0;
    intValue >> number;
    return number;
}

