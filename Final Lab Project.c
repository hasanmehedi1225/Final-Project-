
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure Definitions
typedef struct {
    int routeId;
    char source[30];
    char destination[30];
    int totalSeats;
    int bookedSeats;
} Route;

typedef struct {
    int busId;
    char busName[30];
    int routeId;
} Bus;

typedef struct {
    int userId;
    char name[30];
    char email[50];
    char password[20];
} User;

typedef struct {
    int bookingId;
    int userId;
    int busId;
    int routeId;
    int seatNumber;
} Booking;

// Global Variables for Data Management
Route routes[100];
Bus buses[100];
User users[100];
Booking bookings[200];

int routeCount = 0, busCount = 0, userCount = 0, bookingCount = 0;
char adminUsername[30] = "admin";  // Default admin username
char adminPassword[20] = "admin123"; // Default admin password

// Function Prototypes
void displayAdminMenu();
void displayUserMenu(int userId);
void adminLogin();
void userLogin();
void registerUser();
void addRoute();
void addBus();
void viewRoutes();
void viewBuses();
void viewUsers();
void bookTicket(int userId);
void cancelTicket(int userId);
void viewBookings(int userId);
void saveAllData();
void loadAllData();

// Main Function
int main() {
    loadAllData(); // Load all data from files at startup

    int choice;
    while (1) {
        printf("\n--- Welcome to Digital Bus Services ---\n");
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Register as New User\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume newline character after scanf

        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                userLogin();
                break;
            case 3:
                registerUser();
                break;
            case 4:
                saveAllData(); // Save data before exiting
                printf("Exiting the system. Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to display admin menu
void displayAdminMenu() {
    int choice;
    while (1) {
        printf("\n--- Admin Menu ---\n");
        printf("1. Add New Route\n");
        printf("2. Add New Bus\n");
        printf("3. View All Routes\n");
        printf("4. View All Buses\n");
        printf("5. View All Users\n");
        printf("6. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume newline character after scanf

        switch (choice) {
            case 1:
                addRoute();
                break;
            case 2:
                addBus();
                break;
            case 3:
                viewRoutes();
                break;
            case 4:
                viewBuses();
                break;
            case 5:
                viewUsers();
                break;
            case 6:
                return;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

// Function to handle admin login
void adminLogin() {
    char adminUser[30], adminPass[20];
    printf("Enter Admin Username: ");
    scanf("%s", adminUser);
    printf("Enter Admin Password: ");
    scanf("%s", adminPass);

    if (strcmp(adminUser, adminUsername) == 0 && strcmp(adminPass, adminPassword) == 0) {
        printf("Admin login successful.\n");
        displayAdminMenu();
    } else {
        printf("Invalid credentials, please try again.\n");
    }
}

// Function to handle user login
void userLogin() {
    char email[50], password[20];
    int userId = -1;
    printf("Enter Email: ");
    scanf("%s", email);
    printf("Enter Password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0) {
            userId = users[i].userId;
            break;
        }
    }

    if (userId != -1) {
        printf("User login successful.\n");
        displayUserMenu(userId);
    } else {
        printf("Invalid credentials, please try again.\n");
    }
}

// Function to register a new user
void registerUser() {
    printf("\n--- Register New User ---\n");
    users[userCount].userId = userCount + 1;
    printf("Enter Name: ");
    scanf("%s", users[userCount].name);
    printf("Enter Email: ");
    scanf("%s", users[userCount].email);
    printf("Enter Password: ");
    scanf("%s", users[userCount].password);

    printf("User registered successfully with ID %d.\n", users[userCount].userId);
    userCount++;
}

// Function to display user menu
void displayUserMenu(int userId) {
    int choice;
    while (1) {
        printf("\n--- User Menu ---\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. View Bookings\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume newline character after scanf

        switch (choice) {
            case 1:
                bookTicket(userId);
                break;
            case 2:
                cancelTicket(userId);
                break;
            case 3:
                viewBookings(userId);
                break;
            case 4:
                return;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

// Function to add a new route
void addRoute() {
    printf("\n--- Add New Route ---\n");
    routes[routeCount].routeId = routeCount + 1;
    printf("Enter Source: ");
    scanf("%s", routes[routeCount].source);
    printf("Enter Destination: ");
    scanf("%s", routes[routeCount].destination);
    printf("Enter Total Seats: ");
    scanf("%d", &routes[routeCount].totalSeats);
    routes[routeCount].bookedSeats = 0; // Initialize booked seats to 0

    printf("Route added successfully with ID %d.\n", routes[routeCount].routeId);
    routeCount++;
}

// Function to add a new bus
void addBus() {
    printf("\n--- Add New Bus ---\n");
    buses[busCount].busId = busCount + 1;
    printf("Enter Bus Name: ");
    scanf("%s", buses[busCount].busName);
    printf("Enter Route ID (1 to %d): ", routeCount);
    scanf("%d", &buses[busCount].routeId);

    printf("Bus added successfully with ID %d.\n", buses[busCount].busId);
    busCount++;
}

// Function to view all routes
void viewRoutes() {
    printf("\n--- View All Routes ---\n");
    for (int i = 0; i < routeCount; i++) {
        printf("Route ID: %d, Source: %s, Destination: %s, Total Seats: %d, Booked Seats: %d\n",
            routes[i].routeId, routes[i].source, routes[i].destination,
            routes[i].totalSeats, routes[i].bookedSeats);
    }
}

// Function to view all buses
void viewBuses() {
    printf("\n--- View All Buses ---\n");
    for (int i = 0; i < busCount; i++) {
        printf("Bus ID: %d, Bus Name: %s, Route ID: %d\n",
            buses[i].busId, buses[i].busName, buses[i].routeId);
    }
}

// Function to view all users
void viewUsers() {
    printf("\n--- View All Users ---\n");
    for (int i = 0; i < userCount; i++) {
        printf("User ID: %d, Name: %s, Email: %s\n",
            users[i].userId, users[i].name, users[i].email);
    }
}

// Function to book a ticket
void bookTicket(int userId) {
    int busId, seatNumber;
    printf("\n--- Book Ticket ---\n");
    printf("Enter Bus ID: ");
    scanf("%d", &busId);

    // Check if the bus exists
    int busFound = 0;
    for (int i = 0; i < busCount; i++) {
        if (buses[i].busId == busId) {
            busFound = 1;
            printf("Enter Seat Number (1 to %d): ", routes[buses[i].routeId - 1].totalSeats);
            scanf("%d", &seatNumber);

            // Check if the seat is available
            if (seatNumber < 1 || seatNumber > routes[buses[i].routeId - 1].totalSeats) {
                printf("Invalid seat number!\n");
            } else if (routes[buses[i].routeId - 1].bookedSeats >= routes[buses[i].routeId - 1].totalSeats) {
                printf("No seats available!\n");
            } else {
                // Book the ticket
                Booking booking;
                booking.bookingId = bookingCount + 1;
                booking.userId = userId;
                booking.busId = busId;
                booking.routeId = buses[i].routeId;
                booking.seatNumber = seatNumber;

                bookings[bookingCount++] = booking;
                routes[buses[i].routeId - 1].bookedSeats++;
                printf("Ticket booked successfully! Booking ID: %d\n", booking.bookingId);
            }
            break;
        }
    }

    if (!busFound) {
        printf("Bus ID not found!\n");
    }
}

// Function to cancel a ticket
void cancelTicket(int userId) {
    int bookingId;
    printf("\n--- Cancel Ticket ---\n");
    printf("Enter Booking ID: ");
    scanf("%d", &bookingId);

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingId == bookingId && bookings[i].userId == userId) {
            // Update booked seats and remove booking
            routes[bookings[i].routeId - 1].bookedSeats--;
            printf("Ticket canceled successfully!\n");

            // Shift bookings left to maintain order
            for (int j = i; j < bookingCount - 1; j++) {
                bookings[j] = bookings[j + 1];
            }
            bookingCount--;
            return;
        }
    }
    printf("Booking ID not found!\n");
}

// Function to view bookings
void viewBookings(int userId) {
    printf("\n--- View Bookings ---\n");
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].userId == userId) {
            printf("Booking ID: %d, Bus ID: %d, Route ID: %d, Seat Number: %d\n",
                bookings[i].bookingId, bookings[i].busId, bookings[i].routeId, bookings[i].seatNumber);
        }
    }
}

// Function to save all data to files
void saveAllData() {
    FILE *routeFile = fopen("routes.dat", "wb");
    fwrite(routes, sizeof(Route), routeCount, routeFile);
    fclose(routeFile);

    FILE *busFile = fopen("buses.dat", "wb");
    fwrite(buses, sizeof(Bus), busCount, busFile);
    fclose(busFile);

    FILE *userFile = fopen("users.dat", "wb");
    fwrite(users, sizeof(User), userCount, userFile);
    fclose(userFile);

    FILE *bookingFile = fopen("bookings.dat", "wb");
    fwrite(bookings, sizeof(Booking), bookingCount, bookingFile);
    fclose(bookingFile);
}

// Function to load all data from files
void loadAllData() {
    FILE *routeFile = fopen("routes.dat", "rb");
    if (routeFile) {
        routeCount = fread(routes, sizeof(Route), 100, routeFile);
        fclose(routeFile);
    }

    FILE *busFile = fopen("buses.dat", "rb");
    if (busFile) {
        busCount = fread(buses, sizeof(Bus), 100, busFile);
        fclose(busFile);
    }

    FILE *userFile = fopen("users.dat", "rb");
    if (userFile) {
        userCount = fread(users, sizeof(User), 100, userFile);
        fclose(userFile);
    }

    FILE *bookingFile = fopen("bookings.dat", "rb");
    if (bookingFile) {
        bookingCount = fread(bookings, sizeof(Booking), 200, bookingFile);
        fclose(bookingFile);
    }
}

