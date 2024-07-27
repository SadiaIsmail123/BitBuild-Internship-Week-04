#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> // For remove() and sprintf()
#include <limits> // For numeric_limits

using namespace std;

// Function to print welcome message
void printing() {
    cout << "\t \t \t \t \t \t===============================================\n";
    cout << "\t\t \t \t \t \tWelcome to PIA Online Flight Reservation System\n";
    cout << "\t \t \t \t \t \t===============================================\n";
}

// Function to display menu options
void DisplayMenu() {
    cout << "Please Select your Choice:\n\n";
    cout << "1. Flight Booking\n\n";
    cout << "2. Flight cancellation\n\n";
    cout << "3. Check Flight Bookings\n\n";
    cout << "4. Exit\n\n";
}

// Structure for storing passenger biodata
struct Biodata {
    string name;
    int CNIC;
    int passport;
    int Visa;
};

// Function to input passenger biodata
void BioData(Biodata &data) {
    cout << "Enter your name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, data.name);
    cout << "Enter your CNIC (Without Dashes): ";
    cin >> data.CNIC;
    cout << "Enter the passport No (Without Dashes): ";
    cin >> data.passport;
    cout << "Enter the Visa number: ";
    cin >> data.Visa;
}

// Function to calculate fare for domestic flights
float fair_domestic(int destination, float luggage) {
    float totalFare;
    int baseFare;

    switch (destination) {
        case 1: // Islamabad
            baseFare = 15000;
            break;
        case 2: // Karachi
            baseFare = 27000;
            break;
        case 3: // Lahore
            baseFare = 12000;
            break;
        default:
            cout << "Invalid destination.\n";
            return -1;
    }

    float extraChargePerKg = 200;
    if (luggage <= 0) {
        cout << "Invalid luggage weight.\n";
        return -1;
    } else if (luggage > 32) {
        totalFare = baseFare + (luggage - 32) * extraChargePerKg;
    } else {
        totalFare = baseFare;
    }

    return totalFare;
}

// Function to calculate fare for international flights
float fair_international(int destination, float luggage) {
    float totalFare;
    int baseFare;

    switch (destination) {
        case 1: // Dubai
            baseFare = 70000;
            break;
        case 2: // Saudi Arabia
            baseFare = 150000;
            break;
        case 3: // America
            baseFare = 100000;
            break;
        default:
            cout << "Invalid destination.\n";
            return -1;
    }

    float extraChargePerKg = 200;
    if (luggage <= 0) {
        cout << "Invalid luggage weight.\n";
        return -1;
    } else if (luggage > 32) {
        totalFare = baseFare + (luggage - 32) * extraChargePerKg;
    } else {
        totalFare = baseFare;
    }

    return totalFare;
}

// Function to print ticket details and save to file
void PrintTicket(Biodata &customer, int destination, float luggage, int isInternational, float fare) {
    cout << "\n\n-------------------------------------------\n";
    cout << "               Booking Details             \n";
    cout << "-------------------------------------------\n";
    cout << "Name: " << customer.name << endl;
    cout << "CNIC: " << customer.CNIC << endl;
    cout << "Passport: " << customer.passport << endl;
    cout << "-------------------------------------------\n";
    cout << "Destination: ";
    if (isInternational) {
        switch (destination) {
            case 1:
                cout << "Dubai\n";
                break;
            case 2:
                cout << "Saudi Arabia\n";
                break;
            case 3:
                cout << "America\n";
                break;
        }
        cout << "Total Fare: " << fare << endl;
    } else {
        switch (destination) {
            case 1:
                cout << "Islamabad\n";
                break;
            case 2:
                cout << "Karachi\n";
                break;
            case 3:
                cout << "Lahore\n";
                break;
        }
        cout << "Total Fare: " << fare << endl;
    }
    cout << "-------------------------------------------\n\n";

    // Save ticket to file
    char fileName[30];
    sprintf(fileName, "%d_ticket.txt", customer.passport); // Construct filename based on passport number
    ofstream file(fileName);
    if (file.is_open()) {
        file << "Name: " << customer.name << endl;
        file << "CNIC: " << customer.CNIC << endl;
        file << "Passport: " << customer.passport << endl;
        file << "Destination: ";
        if (isInternational) {
            switch (destination) {
                case 1:
                    file << "Dubai\n";
                    break;
                case 2:
                    file << "Saudi Arabia\n";
                    break;
                case 3:
                    file << "America\n";
                    break;
            }
            file << "Total Fare: " << fare << endl;
        } else {
            switch (destination) {
                case 1:
                    file << "Islamabad\n";
                    break;
                case 2:
                    file << "Karachi\n";
                    break;
                case 3:
                    file << "Lahore\n";
                    break;
            }
            file << "Total Fare: " << fare << endl;
        }
        file << "-------------------------------------------\n\n";
        file.close();
    } else {
        cout << "Error: File could not be created to save ticket.\n";
    }
}

// Function to cancel ticket
void cancelTicket(int passportNum) {
    char fileName[30];
    sprintf(fileName, "%d_ticket.txt", passportNum);

    if (remove(fileName) == 0) {
        cout << "Ticket with Passport Number " << passportNum << " has been cancelled successfully.\n";
    } else {
        cout << "No ticket found with Passport Number " << passportNum << ".\n";
    }
}

// Function to check booking
void checkBooking(int passportNum) {
    char fileName[30];
    sprintf(fileName, "%d_ticket.txt", passportNum); // Construct filename based on passport number

    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "No booking found with Passport Number " << passportNum << ".\n";
        return;
    }

    cout << "Booking Details for Passport Number " << passportNum << ":\n";

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

// Function for domestic flight booking
void Domestic() {
    int DomesticChoice;
    float luggageweight;
    Biodata customer;
    cout << "Which City you want to travel:\n";
    cout << "1. Islamabad\n";
    cout << "2. Karachi\n";
    cout << "3. Lahore\n";
    cin >> DomesticChoice;

    switch (DomesticChoice) {
        case 1: // Islamabad
        case 2: // Karachi
        case 3: // Lahore
            BioData(customer);
            cout << "Enter the luggage weight: ";
            cin >> luggageweight;
            {
                float fareDomestic = fair_domestic(DomesticChoice, luggageweight);
                if (fareDomestic != -1) {
                    PrintTicket(customer, DomesticChoice, luggageweight, 0, fareDomestic);
                }
            }
            break;
        default:
            cout << "Invalid choice.\n";
            break;
    }
}

// Function for international flight booking
void International() {
    int InternationalChoice;
    float luggageweight;
    Biodata customer;
    cout << "Which Country you want to travel:\n";
    cout << "1. Dubai\n";
    cout << "2. Saudi Arabia\n";
    cout << "3. America\n";
    cin >> InternationalChoice;

    switch (InternationalChoice) {
        case 1: // Dubai
        case 2: // Saudi Arabia
        case 3: // America
            BioData(customer);
            cout << "Enter the luggage weight: ";
            cin >> luggageweight;
            {
                float fareInternational = fair_international(InternationalChoice, luggageweight);
                if (fareInternational != -1) {
                    PrintTicket(customer, InternationalChoice, luggageweight, 1, fareInternational);
                }
            }
            break;
        default:
            cout << "Invalid choice.\n";
            break;
    }
}

// Main function
int main() {
    int ch;
    int travel;
    printing();
    cout << "\n";
    do {
        DisplayMenu();
        cout << "Enter your Choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "Do you want to travel Domestic or International? (Press 1 for Domestic and 2 for International): ";
                cin >> travel;
                if (travel == 1) {
                    Domestic();
                } else if (travel == 2) {
                    International();
                } else {
                    cout << "The input is invalid\n";
                }
                break;
            case 2:
                cout << "Enter your Passport Number for ticket cancellation: ";
                int passportNum;
                cin >> passportNum;
                cancelTicket(passportNum);
                break;
            case 3:
                cout << "Enter your Passport Number to check booking: ";
                int checkPassportNum;
                cin >> checkPassportNum;
                checkBooking(checkPassportNum);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid Choice.\n";
                break;
        }
    } while (ch != 4);

    return 0;
}
