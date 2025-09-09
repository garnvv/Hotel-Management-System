#include <iostream>
#include <string>
using namespace std;

class Room
{
    public:
        int roomId;
        bool isAvailable;
        double roomRent;
        Room* next;

        Room(int id, double rent) : roomId(id), isAvailable(true), roomRent(rent), next(nullptr) {}
};

class RoomBooking
{
    public:
        string guestName;
        string checkInDate;
        string aadhaarNumber;
        int roomId;
        double roomRent;
        RoomBooking* next;

        RoomBooking(string guestName, string checkInDate, string aadhaarNumber, int roomId, double roomRent)
            : guestName(guestName), checkInDate(checkInDate), aadhaarNumber(aadhaarNumber), roomId(roomId), roomRent(roomRent), next(nullptr) {}

        string toString()
        {
            return "Room ID: " + to_string(roomId) + ", Guest: " + guestName + ", Aadhaar: " + aadhaarNumber + ", Check-in Date: " + checkInDate + ", Room Rent: Rs " + to_string(roomRent);
        }
};

class HotelManagementSystem
{
    private:
        Room* roomHead;
        RoomBooking* bookingHead;
        RoomBooking* bookingHistoryHead;
        int nextRoomId = 1;

    public:
        HotelManagementSystem() : roomHead(nullptr), bookingHead(nullptr), bookingHistoryHead(nullptr) {}

        void addRoom(double rent)
        {
            Room* newRoom = new Room(nextRoomId++, rent);
            if (!roomHead)
            {
                roomHead = newRoom;
            }
            else
            {
                Room* temp = roomHead;
                while (temp->next)
                {
                    temp = temp->next;
                }
                temp->next = newRoom;
            }
        }

        void viewAvailableRooms()
        {
            cout << "Available Rooms: " << endl;
            bool found = false;
            Room* temp = roomHead;
            while (temp)
            {
                if (temp->isAvailable)
                {
                    cout << "Room ID: " << temp->roomId << ", Rent: Rs " << temp->roomRent << endl;
                    found = true;
                }
                temp = temp->next;
            }
            if (!found)
            {
                cout << "No rooms available." << endl;
            }
        }

        void bookRoom(string guestName, string checkInDate, string aadhaarNumber, int roomId)
        {
            Room* temp = roomHead;
            while (temp)
            {
                if (temp->roomId == roomId && temp->isAvailable)
                {
                    temp->isAvailable = false;
                    RoomBooking* newBooking = new RoomBooking(guestName, checkInDate, aadhaarNumber, temp->roomId, temp->roomRent);
                    if (!bookingHead)
                    {
                        bookingHead = newBooking;
                    }
                    else
                    {
                        RoomBooking* bookingTemp = bookingHead;
                        while (bookingTemp->next)
                        {
                            bookingTemp = bookingTemp->next;
                        }
                        bookingTemp->next = newBooking;
                    }
                    cout << "Room " << temp->roomId << " booked successfully with rent Rs " << temp->roomRent << "." << endl;
                    return;
                }
                temp = temp->next;
            }
            cout << "Room ID " << roomId << " is not available for booking." << endl;
        }

        void viewBookings()
        {
            if (!bookingHead)
            {
                cout << "No room bookings." << endl;
            }
            else
            {
                RoomBooking* temp = bookingHead;
                while (temp)
                {
                    cout << temp->toString() << endl;
                    temp = temp->next;
                }
            }
        }

        void viewBookingHistory()
        {
            if (!bookingHistoryHead)
            {
                cout << "No booking history." << endl;
            }
            else
            {
                RoomBooking* temp = bookingHistoryHead;
                while (temp)
                {
                    cout << temp->toString() << endl;
                    temp = temp->next;
                }
            }
        }

        void cancelBooking(int roomId)
        {
            RoomBooking* prev = nullptr;
            RoomBooking* current = bookingHead;

            while (current)
            {
                if (current->roomId == roomId)
                {
                    RoomBooking* historyBooking = new RoomBooking(current->guestName, current->checkInDate, current->aadhaarNumber, current->roomId, current->roomRent);
                    if (!bookingHistoryHead)
                    {
                        bookingHistoryHead = historyBooking;
                    }
                    else
                    {
                        RoomBooking* temp = bookingHistoryHead;
                        while (temp->next)
                        {
                            temp = temp->next;
                        }
                        temp->next = historyBooking;
                    }

                    if (prev)
                    {
                        prev->next = current->next;
                    }
                    else
                    {
                        bookingHead = current->next;
                    }
                    delete current;

                    Room* roomTemp = roomHead;
                    while (roomTemp)
                    {
                        if (roomTemp->roomId == roomId)
                        {
                            roomTemp->isAvailable = true;
                            break;
                        }
                        roomTemp = roomTemp->next;
                    }

                    cout << "Booking cancelled." << endl;
                    return;
                }
                prev = current;
                current = current->next;
            }
            cout << "Booking not found." << endl;
        }
};

int main()
{
    HotelManagementSystem HMS;
    int choice;

    HMS.addRoom(2000);
    HMS.addRoom(2500);
    HMS.addRoom(3000);
    HMS.addRoom(1500);
    HMS.addRoom(1800);
    HMS.addRoom(2200);
    HMS.addRoom(3500);
    HMS.addRoom(4000);
    HMS.addRoom(2800);
    HMS.addRoom(3200);

    while (true)
    {
        cout << "\n****** WELCOME TO GRAND HORIZON INN ******" << endl;
        cout << "\n1. Book a room\n2. View available rooms\n3. View active bookings\n4. Cancel a booking\n5. View booking history\n6. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            case 1:
            {
                string guestName, checkInDate, aadhaarNumber;
                int roomId;
                HMS.viewAvailableRooms();
                cout << "Enter Room ID to book: ";
                cin >> roomId;
                cin.ignore();
                cout << "Enter guest name: ";
                getline(cin, guestName);
                cout << "Enter Aadhaar number: ";
                getline(cin, aadhaarNumber);
                cout << "Enter check-in date (YYYY-MM-DD): ";
                getline(cin, checkInDate);
                HMS.bookRoom(guestName, checkInDate, aadhaarNumber, roomId);
                break;
            }
            case 2:
                HMS.viewAvailableRooms();
                break;
            case 3:
                HMS.viewBookings();
                break;
            case 4:
            {
                int roomId;
                cout << "Enter room ID to cancel: ";
                cin >> roomId;
                HMS.cancelBooking(roomId);
                break;
            }
            case 5:
                HMS.viewBookingHistory();
                break;
            case 6:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
    return 0;
}
