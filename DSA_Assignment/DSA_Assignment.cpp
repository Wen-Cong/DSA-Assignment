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
#include "IT_Booking.h"
#include "BST_OccupiedBooking.h"
#include "Dictionary_Room.h"
#include "Dictionary_Price.h"
#include "Booking.h"
#include "List.h"
#include "Queue.h"
using namespace std;

// Convert string to integer
int toInt(string text);

// Convert date string in dd/mm/yyyy format to tm
tm toDateTime(string dateString);

// Convert tm to date string in dd/mm/yyyy format
string fromDateTime(tm date);

// Calculate the last date of each month
int getMaxDay(int month, int year);

// Read from room csv file and initialise room data to dictionary
void initRoomData(Dictionary_Room& roomList, Dictionary_Price& priceList, List& availRoom);

// Read from booking csv file and initialise booking data to interval tree
void initBookingData(IT_Booking& bookingList, Dictionary_Room& roomList, Dictionary_Price& priceList);

// Print all main menu options
void displayMainMenu(tm todayDate);

// Print all months from January to December
void displayAllMonths();

// Convert user option 1,2,3,4 to respective room type name
string convertOptionToRoomTypeName(string opt);

// Insert booking to booking collection and append data to booking csv file
bool addNewBooking(IT_Booking& bookingList, Booking b);

// Update booking data in csv file for any editing changes made to booking data
void updateBookingData(Booking b);

int main()
{
    cout << "Initialising Data, Please wait..." << endl << endl;
    // Initialise room data using dictionary data structure
    IT_Booking bookingList = IT_Booking();
    Dictionary_Room roomList = Dictionary_Room();
    Dictionary_Price priceList = Dictionary_Price();
    List availRoom = List();
    initRoomData(roomList, priceList,availRoom);
    initBookingData(bookingList, roomList, priceList);
    //Setting up the start date of the application
    tm todayDate = toDateTime("01/04/2021\n");
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

            //Search for checkin date that falls on today's date
            IT_Booking booking;
            // Search all bookings that are booked today
            bookingList.overlapSearch(todayDate, todayDate, booking, "True");
            if (booking.isEmpty()) {
                cout << "No bookings today!" << endl;
            }
            else {
                //To-Do: Check in users.
                int index = 0;
                int userInput;
                // from the list, let user select which guest to check in on that day
                cout << "\n===================== Select Guest =====================\n";
                booking.printOption(index);
                cout << "[0] Cancel" << endl;
                cout << endl;
                cout << "Please select user to check in:";
                cin >> userInput;
                cout << endl;
                if (userInput != 0|| (userInput >0 && userInput<=index)) {
                    Booking target;
                    // get the booking details from the user input.
                    booking.getBooking(target, userInput);
                    // Interval tree for occupied room
                    IT_Booking occupiedRoom;
                    // List for rooms that are available
                    List availRoomList;
                    //Search if any room is occupied during this time period
                    bookingList.overlapSearch(target.getCheckIn(),target.getCheckOut(), occupiedRoom,"False");
                    for (int i = 0; i < availRoom.getLength(); i++) {
                        if (roomList.get(availRoom.get(i)).getType() == target.getRoom().getType()) {
                            availRoomList.add(availRoom.get(i));
                        }
                    }
                    
                    //Get unoccupied rooms of the same type and return the first available room number
                    int roomNum = occupiedRoom.availRoomList(availRoomList, target.getRoom().getType());
                    if (roomNum != -1) {
                        //Update details of the booking
                        target.setStatus("Checked In");
                        Room r = target.getRoom();
                        r.setRoomNum(roomNum);
                        target.setRoom(r);
                        string specialReq = "";
                        if (target.getRequest() == "") {
                            specialReq = "No Special Requests!";
                        }
                        else {
                            specialReq = target.getRequest();
                        }
                        //Update the booking in the list
                        bookingList.updateBooking(target);
                        //Update the details in the file
                        updateBookingData(target);
                        cout << "-----  Guest Checkin  -----" << endl;
                        cout << "Booking ID: " << target.getId() << "\nName: " << target.getGuestName()
                            << "\nStatus: "<< target.getStatus()
                            << "\nRoom No.: " << target.getRoom().getRoomNum() 
                            << "\nNumber of Guests: " << target.getNumOfGuest() 
                            << "\nSpecial Requests: " << specialReq << endl;
                        cout << endl;
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
            cout << "Enter [0] Anytime to Cancel" << endl;
            // Prompt user for room type choice, check in date and check out date
            cout << "\nPlease Choose a Room Type: ";
            cin >> roomTypeChoice;
            // Go back to main menu if user enter 0 (cancels)
            if (roomTypeChoice == "0") {
                cout << endl;
                continue;
            }

            cout << "Please Enter Check In Date (dd/mm/yyyy): ";
            cin >> checkIn;
            // Go back to main menu if user enter 0 (cancels)
            if (checkIn == "0") {
                cout << endl;
                continue;
            }

            cout << "Please Enter Check Out Date (dd/mm/yyyy): ";
            cin >> checkOut;
            // Go back to main menu if user enter 0 (cancels)
            if (checkOut == "0") {
                cout << endl;
                continue;
            }

            tm in = toDateTime(checkIn);
            tm out = toDateTime(checkOut);
            string roomType = convertOptionToRoomTypeName(roomTypeChoice);

            // Check if check out date input is later than check in date input
            if (difftime(mktime(&in), mktime(&out)) > 0) {
                cout << "\nInvalid Dates .Check out date must be after check in date.\n\n";
                continue;
            }

            // Set price and room type into room object to be added to booking object
            Room r = Room();
            r.setPrice(priceList.get(roomType).price);
            r.setType(roomType);

            Booking targetBooking = Booking(r, in, out); // This booking will only be used to check for availability
            IT_Booking occupiedBookings;

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
            // Go back to main menu if user enter 0 (cancels)
            if (guestName == "0") {
                cout << endl;
                continue;
            }

            cout << "Please Enter the Number of Guest: ";
            cin >> numOfGuest;
            // Go back to main menu if user enter 0 (cancels)
            if (numOfGuest == "0") {
                cout << endl;
                continue;
            }

            cout << "Please Enter Special Request (If any): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, specReq);
            // Go back to main menu if user enter 0 (cancels)
            if (specReq == "0") {
                cout << endl;
                continue;
            }

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
            string selectedDate;
            tm dateInput;
            // Display guests staying in a particular date
            cout << "\n===================== Display Guest Staying On A Particular Date =====================\n";
            cout << "[Enter 0 to return]" << endl;
            cout << "Please Enter Date (dd/mm/yyyy): ";
            
            cin >> selectedDate;
            if (selectedDate != "0") {
                //Convert to TM Struct
                dateInput = toDateTime(selectedDate);
                //Search for checkin date
                IT_Booking bookings;
                // Search all bookings that occupies a room within given date range
                bookingList.overlapSearch(dateInput, dateInput, bookings, "All");
                if (bookings.countNodes() > 0) {
                    bookings.printDetails();
                }
                else {
                    cout << "No Bookings Found!" << endl;
                }
            }
            cout << endl;
        }

        else if (choice == "4")
        {
            string month;
            string year;
            // Display for a particular month, the dates that each room is occupied
            cout << "\n===================== DISPLAY OCCUPIED DATES OF ROOMS =====================\n";
            cout << "Please Enter Year [Enter 0 to go back]: ";
            cin >> year;

            // Return back to main menu if user exit
            if (year == "0") {
                continue;
            }
            displayAllMonths();
            cout << "Please Choose a Month: ";
            cin >> month;
            //skip a line
            cout << endl;

            // Return back to main menu if user exit
            if (month == "0") {
                continue;
            }

            string startStr = "01/" + month + "/" + year;
            string endStr = to_string(getMaxDay((toInt(month) - 1), toInt(year))) + "/" + month + "/" + year;
            tm start = toDateTime(startStr);
            tm end = toDateTime(endStr);

            BST_OccupiedBooking occupiedBookings;
            // Search all bookings that occupies a room within given date range
            bookingList.overlapSearch(start, end, occupiedBookings);

            occupiedBookings.inorder();
        }

        else if (choice == "5")
        {
            // Search for the most popular room type
            string roomType;
            int count;
            bookingList.searchHighestRoomTypeCount(roomType, count);
            cout << "\n===================== Most Popular Room Type =====================\n\n";
            cout << "Room Type: " << roomType << "\nNumber of Bookings Made: " << count << endl << endl;
            cout << "==================================================================\n\n";
        }
        else if (choice == "6") {
            // To-Do: Display all the bookings of the hotel within a given time period
            string startDate, endDate;
            tm startDateTM, endDateTM;
            //Check in a guest using the booking information
            cout << "\n===================== Display All Guest Within Time Period =====================\n";
            cout << "[Enter 0 to return]" << endl;
            cout << "Please Enter Start Date (dd/mm/yyyy): ";
            cin >> startDate;
            cout << "Please Enter End Date (dd/mm/yyyy): ";
            cin >> endDate;
            //Convert input into TM Struct
            startDateTM = toDateTime(startDate);
            endDateTM = toDateTime(endDate);
            if (startDate != "0" && endDate != "0") {
                if (difftime(mktime(&endDateTM), mktime(&startDateTM)) <= 0) {
                    cout << "Start date must be earlier than end date!" << endl;
                }
                else {
                    //Search for checkin date
                    IT_Booking bookings;
                    // Search all bookings that occupies a room within given date range
                    bookingList.overlapSearch(startDateTM, endDateTM, bookings, "All");
                    if (bookings.countNodes() > 0) {
                        bookings.printDetails();
                    }
                    else {
                        cout << "No Bookings Found!" << endl;
                    }

                }
            }
            cout << endl;
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
            //Suggestion to auto check people out as time move along
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

void initRoomData(Dictionary_Room& roomList, Dictionary_Price& priceList, List& availRoom) {
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

void initBookingData(IT_Booking& bookingList, Dictionary_Room& roomList, Dictionary_Price& priceList) {
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
    cout << "[3] Display Guest Staying On A Particular Date\n";
    cout << "[4] Display Occupied Rooms by Month\n";
    cout << "[5] Search for the most popular room type\n";
    cout << "[6] Display bookings within a given time period\n";
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
        return "Deluxe City View";
    }
    else if (opt == "2")
    {
        return "Standard City View";
    }

    else if (opt == "3")
    {
        return "Executive Sea View";
    }
    else if (opt == "4")
    {
        return "President Suite";
    }
    else
    {
        cout << "Invalid Option\n\n";
        return "";
    }
}

bool addNewBooking(IT_Booking& bookingList, Booking b) {
    // Open booking csv file and import booking data
    ifstream inputFile;
    inputFile.open("Bookings.csv");
    Queue q = Queue();
    int count = 0;// Initialise variables
    string bId, header1;
    string bDate, header2;
    string bGuestName, header3;
    string bRoomNumber, header4;
    string bRoomType, header5;
    string bStatus, header6;
    string bIn, header7;
    string bOut, header8;
    string bGuestNum, header9;
    string bReq, header10;
    // Check if file open successfully
    if (inputFile.is_open()) {

        string line;
        getline(inputFile, header1, ',');
        getline(inputFile, header2, ',');
        getline(inputFile, header3, ',');
        getline(inputFile, header4, ',');
        getline(inputFile, header5, ',');
        getline(inputFile, header6, ',');
        getline(inputFile, header7, ',');
        getline(inputFile, header8, ',');
        getline(inputFile, header9, ',');
        getline(inputFile, header10);
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
            if (bId == "") {
                continue;
            }
            else {
                line = bId + "," + bDate + "," + bGuestName + "," + bRoomNumber + "," + bRoomType + ","
                    + bStatus + "," + bIn + "," + bOut + "," + bGuestNum + "," + bReq;
                    q.enqueue(line);
            }
        }
    }
    // Close file stream
    inputFile.close();
    string inStr = fromDateTime(b.getCheckIn());
    string outStr = fromDateTime(b.getCheckOut());
    string bDateStr = fromDateTime(b.getDate());
    string roomNumStr = "";
    if (b.getRoom().getRoomNum() >= 0)
        roomNumStr = "Room " + to_string(b.getRoom().getRoomNum());
    // Insert data into Excel file
    ofstream csvFile;
    // Open Bookings csv File in append mode
    csvFile.open("Bookings_New.csv", ios::app);
    // Check if file open successfully
    if (csvFile.is_open()) {
        csvFile << header1 << "," << header2 << "," << header3 << "," << header4 << ",";
        csvFile << header5 << "," << header6 << "," << header7 << "," << header8 << ",";
        csvFile << header9 << "," << header10 << endl;
        while (!q.isEmpty()) {
            string e;
            q.dequeue(e);
            csvFile << e << endl;
        }
        csvFile << b.getId() << "," << bDateStr << "," << b.getGuestName() << "," << roomNumStr << ",";
        csvFile << b.getRoom().getType() << "," << b.getStatus() << "," << inStr << "," << outStr << ",";
        csvFile << b.getNumOfGuest() << "," << b.getRequest() << endl;
    }
    
    // Close file
    csvFile.close();
    remove("Bookings.csv");
    // renaming the updated file with the existing file name
    rename("Bookings_New.csv", "Bookings.csv");
    // Insert data into booking list
    bookingList.insert(*&b);
    return true;
}
void updateBookingData(Booking b) {
    // Open booking csv file and import booking data
    ifstream inputFile;
    inputFile.open("Bookings.csv");
    Queue q = Queue();
    int count = 0;// Initialise variables
    bool found = false;
        string bId, header1;
        string bDate, header2;
        string bGuestName,header3;
        string bRoomNumber,header4;
        string bRoomType,header5;
        string bStatus,header6;
        string bIn,header7;
        string bOut,header8;
        string bGuestNum,header9;
        string bReq,header10;
    // Check if file open successfully
    if (inputFile.is_open()) {
        
        string line;
        getline(inputFile, header1, ',');
        getline(inputFile, header2, ',');
        getline(inputFile, header3, ',');
        getline(inputFile, header4, ',');
        getline(inputFile, header5, ',');
        getline(inputFile, header6, ',');
        getline(inputFile, header7, ',');
        getline(inputFile, header8, ',');
        getline(inputFile, header9, ',');
        getline(inputFile, header10);
        
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
            if (bId == "") {
                continue;
            }
            else {
                line = bId + "," + bDate + "," + bGuestName + "," + bRoomNumber + "," + bRoomType + ","
                    + bStatus + "," + bIn + "," + bOut + "," + bGuestNum + "," + bReq;

                if (toInt(bId) == b.getId())
                    found = true;
                else
                    q.enqueue(line);
            }
            if (!found) {
                count++;
            }
        }
    }
    // Close file stream
    inputFile.close();
    string inStr = fromDateTime(b.getCheckIn());
    string outStr = fromDateTime(b.getCheckOut());
    string bDateStr = fromDateTime(b.getDate());
    string roomNumStr = "";
    if (b.getRoom().getRoomNum() >= 0)
        roomNumStr = "Room " + to_string(b.getRoom().getRoomNum());
    // Insert data into Excel file
    ofstream csvFile;
    // Open Bookings csv File in append mode
    csvFile.open("Bookings_New.csv", ios::app);
    // Check if file open successfully
    if (csvFile.is_open()) {
        csvFile << header1 << "," << header2 << "," << header3 << "," << header4 << ",";
        csvFile << header5 << "," << header6 << "," << header7 << "," << header8 << ",";
        csvFile << header9 << "," << header10 << endl;

            while (!q.isEmpty()) {
                if (count == 0) {
                    csvFile << b.getId() << "," << bDateStr << "," << b.getGuestName() << "," << roomNumStr << ",";
                    csvFile << b.getRoom().getType() << "," << b.getStatus() << "," << inStr << "," << outStr << ",";
                    csvFile << b.getNumOfGuest() << "," << b.getRequest() << endl;
                }
                else {
                    string e;
                    q.dequeue(e);
                    csvFile << e << endl;
                }
                count--;
            }
            //In case the queue empty first cause the not edited version will not be added to the queue
            // So queue length is n-1
            // but if the booking to change is index n
            // it will miss adding the last line hence this is to catch it.
            if (count == 0) {
                csvFile << b.getId() << "," << bDateStr << "," << b.getGuestName() << "," << roomNumStr << ",";
                csvFile << b.getRoom().getType() << "," << b.getStatus() << "," << inStr << "," << outStr << ",";
                csvFile << b.getNumOfGuest() << "," << b.getRequest() << endl;
            }
    }
    // Close file
    csvFile.close();
    remove("Bookings.csv");
    // renaming the updated file with the existing file name
    rename("Bookings_New.csv", "Bookings.csv");
}