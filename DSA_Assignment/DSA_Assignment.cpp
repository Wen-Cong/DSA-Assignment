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
#include "Dictionary_Room.h"
#include "Dictionary_Price.h"
#include "Booking.h"
#include "List.h"
#include "List_AvailableRooms.h"
using namespace std;


int toInt(string text);
tm toDateTime(string dateString);
string fromDateTime(tm date);
int getMaxDay(int month, int year);
void initRoomData(Dictionary_Room& roomList, Dictionary_Price& priceList, List_AvailableRooms& availRoom);
void initBookingData(BST_Booking& bookingList, Dictionary_Room roomList, Dictionary_Price priceList);
void displayMainMenu(tm todayDate);
void displayAllMonths();
string convertOptionToRoomTypeName(string opt);
bool addNewBooking(BST_Booking& bookingList, Booking b);

int main()
{
    cout << "Initialising Data, Please wait..." << endl << endl;
    // Initialise room data using dictionary data structure
    BST_Booking bookingList = BST_Booking();
    Dictionary_Room roomList = Dictionary_Room();
    Dictionary_Price priceList = Dictionary_Price();
    List_AvailableRooms availRoom= List_AvailableRooms();
    initRoomData(roomList, priceList,availRoom);
    initBookingData(bookingList, roomList, priceList);

    bookingList.inorder();
    //Setting up the start date of the application
    tm todayDate = toDateTime("02/04/2021");

    string choice;
    while (choice != "0")
    {
        // Display main menu options
        displayMainMenu(todayDate);
        cin >> choice;
        if (choice == "0")
            break;

        else if (choice == "1")
        {
            //Check in a guest using the booking information
            cout << "\n===================== Check In =====================\n";
            cout << "Today's Date: " << fromDateTime(todayDate) << endl;

            tm endDate = todayDate;
            endDate.tm_mday++;
            //Search for checkin date that falls on today's date
            BST_Booking booking;
            // Search all bookings that occupies a room within given date range
            bookingList.overlapSearch(todayDate, endDate, booking, true);
            if (booking.isEmpty()) {
                cout << "No bookings today!" << endl;
            }
            else {
                int userInput;
                List dispList;
                booking.transferList(dispList);
                cout << "\n===================== Select Guest =====================\n";
                dispList.print();
                cout << "[0] Cancel" << endl;
                cout << endl;
                cout << "Please select user to check in:";
                cin >> userInput;
                if (userInput != '0') {
                    Booking target = dispList.get(userInput);
                    BST_Booking occupiedRoom;
                    List_AvailableRooms availRoomList;
                    bookingList.overlapSearch(target.getCheckIn(),target.getCheckOut(), occupiedRoom,false);
                    for (int i = 0; i < availRoom.getLength(); i++) {
                        if (roomList.get(availRoom.get(i)).getType() == target.getRoom().getType()) {
                            availRoomList.add(availRoom.get(i));
                        }
                    }
                    //Get not occupied rooms of the same type
                    int roomNum = occupiedRoom.availRoomList(availRoomList, target.getRoom().getType());
                    if (roomNum != -1) {
                        target.setStatus("Checked In");
                        Room r = target.getRoom();
                        r.setRoomNum(roomNum);
                        target.setRoom(r);
                        bookingList.insert(target);
                        target.print();
                    }
                    if (target.getStatus() != "Checked In") {
                        cout << "No available rooms to check in!" << endl;
                    }
                }
            }            
        }

        else if (choice == "2")
        {
            // Add and save a new booking for the hotel
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

            // Set price and room type into room object to be added to booking object
            Room r = Room();
            r.setPrice(priceList.get(roomType).price);
            r.setType(roomType);

            Booking targetBooking = Booking(r, in, out); // This booking will only be used to check for availability
            BST_Booking occupiedBookings;

            // Check availability of room based on room type, check in date and check out date.
            int totalNumOfRoom = priceList.get(roomType).count;
            bookingList.overlapSearch(targetBooking, occupiedBookings);
            // All rooms of selected type are occupied or booked during this date range
            if (occupiedBookings.countNodes() >= totalNumOfRoom)
            {
                cout << endl << roomType << " rooms are fully occupied during selected time.\n";
                cout << "Please choose another date or room. Thank You!\n\n";
                continue;
            }
            else {
                cout << "\nAvailable Rooms Found!\n\n";
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

            // Get new booking id for latest booking added
            int bookingId = bookingList.countNodes() + 1;

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
        //Finished
            string selectedDate;
            tm dateInput;
            // TO DO : Display guests staying in a particular date

            //Check in a guest using the booking information
            cout << "\n===================== Display Guest Staying On A Particular Date =====================\n";
            cout << "Today's Date: " << fromDateTime(todayDate) << endl;
            cout << "Please Enter Check In Date (dd/mm/yyyy): ";
            cin >> selectedDate;
            dateInput = toDateTime(selectedDate);
            //setting the end date (Note: Not inclusive)
            tm checkout = dateInput;
            checkout.tm_mday++;
            //Search for checkin date
            BST_Booking bookings;
            // Search all bookings that occupies a room within given date range
            bookingList.overlapSearch(dateInput, checkout, bookings, false);
            bookings.inorder();

        }

        else if (choice == "4")
        {
            string month;
            string year;
            // TO DO: Display for a particular month, the dates that each room is occupied
            cout << "\n===================== DISPLAY OCCUPIED DATES OF ROOMS =====================\n";
            cout << "Please Enter Year: ";
            cin >> year;
            displayAllMonths();
            cout << "Please Choose a Month: ";
            cin >> month;
            //skip a line
            cout << endl;
            string startStr = "01/" + month + "/" + year;
            string endStr = to_string(getMaxDay((toInt(month) - 1), toInt(year))) + "/" + month + "/" + year;
            tm start = toDateTime(startStr);
            tm end = toDateTime(endStr);

            //Booking targetBooking = Booking(); // This booking will only be used to check for availability
            //targetBooking.setCheckIn(start); // Set range start
            //targetBooking.setCheckOut(end); // Set range end
            BST_Booking occupiedBookings;
            // Search all bookings that occupies a room within given date range
            bookingList.overlapSearch(start,end, occupiedBookings, false);

            occupiedBookings.inorder();
        }
        else if (choice == "7") {
            // This code is used to change the date of today
            string dateEntered;
            cout << "\n===================== Change Today's Date =====================\n";
            cout << "Today's Date: " << fromDateTime(todayDate) << endl;
            cout << "Which date do you want to change to: ";
            cin >> dateEntered;
            cout << endl;
            todayDate = toDateTime(dateEntered);
            cout << "Date successfully changed!\n";
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

    // Convert to year since 1900 for tm_year and 0-indexed format for tm_mon
    date.tm_year -= 1900;
    date.tm_mon--;

    return date;
}

string fromDateTime(tm date) {
    // Convert tm type to string in (dd/mm/yyyy) format
    string dateStr = "";
    // Append year, month and day in human readable format
    dateStr = to_string(date.tm_mday) + "/" + to_string(date.tm_mon + 1) + "/" + to_string(date.tm_year + 1900);
    // If hour and minute is found, append hour and minute
    if (date.tm_hour != NULL && date.tm_min != NULL) {
        dateStr += " " + to_string(date.tm_hour) + ":" + to_string(date.tm_min);
    }

    return dateStr;
}


int getMaxDay(int month, int year) {
    if (month == 0 || month == 2 || month == 4 || month == 6 || month == 7 || month == 9 || month == 11)
        return 31;
    else if (month == 3 || month == 5 || month == 8 || month == 10)
        return 30;
    else {
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                if (year % 400 == 0)
                    return 29;
                return 28;
            }
            return 29;
        }
        return 28;
    }
}

void initRoomData(Dictionary_Room& roomList, Dictionary_Price& priceList, List_AvailableRooms& availRoom) {
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

            // If Room Number not found then skip this row to ensure quality data (File Validation)
            if (roomNumberString == "") {
                continue;
            }

            // Remove the first 4 char "Room" and convert reamining char from string to integer
            int roomNum = toInt(roomNumberString.erase(0, 4));
            // Convert string to double for price
            double price = stod(roomPrice);

            // Append to room list
            Room r = Room(roomNum, roomType, price);
            roomList.add(roomNum, r);
            availRoom.add(roomNum);
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

            // If booking ID not found then skip this row to ensure quality data (File Validation)
            if (bId == "") {
                continue;
            }

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
            // Room number is not assigned to this booking yet, create a room object without room number first
            if (bookedRoom.getRoomNum() < 0) {
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

void displayMainMenu(tm todayDate) {
    cout << "===================== MAIN MENU =====================\n";
    cout << "Today's date is " << fromDateTime(todayDate) << endl;
    cout << "[1] Check In Guest\n";
    cout << "[2] Add Booking\n";
    cout << "[3] Display Staying Guest by Date\n";
    cout << "[4] Display Occupied Rooms by Month\n";
    cout << "[7] Change Today's Date\n";
    cout << "[0] Exit\n\n";
    cout << "Your Choice: ";
}

void displayAllMonths() {
    cout << "[1]  January\n";
    cout << "[2]  Febuary\n";
    cout << "[3]  March\n";
    cout << "[4]  April\n";
    cout << "[5]  May\n";
    cout << "[6]  June\n";
    cout << "[7]  July\n";
    cout << "[8]  August\n";
    cout << "[9]  September\n";
    cout << "[10] October\n";
    cout << "[11] November\n";
    cout << "[12] December\n\n";
    cout << "[0]  Back\n\n";
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
        csvFile << b.getId() << "," << bDateStr << "," << b.getGuestName() << "," << roomNumStr << ",";
        csvFile << b.getRoom().getType() << "," << b.getStatus() << "," << inStr << "," << outStr << ",";
        csvFile << b.getNumOfGuest() << "," << b.getRequest() << endl;
    }
    // Close file
    csvFile.close();

    return true;
}