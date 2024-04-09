#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct hotel 
{
    char name[50];
    long int ph;
    char place[20];
    long int adh;
    int rno;
    struct hotel* next;
};

typedef struct hotel Hotel;

Hotel* head = NULL;
int lastRoomNumber = 100;

bool isRoomNumberUnique(int rno) {
    Hotel* temp = head;
    while (temp != NULL) {
        if (temp->rno == rno) {
            return false;
        }
        temp = temp->next;
    }
    return true;
}

int generateUniqueRoomNumber() {
    int roomNumber = lastRoomNumber + 1;
    while (!isRoomNumberUnique(roomNumber)) {
        roomNumber++;
    }
    lastRoomNumber = roomNumber;
    return roomNumber;
}

void addHotel(char name[], long int ph, char place[], long int adh) {
    Hotel* newHotel = (Hotel*)malloc(sizeof(Hotel));
    strcpy(newHotel->name, name);
    newHotel->ph = ph;
    strcpy(newHotel->place, place);
    newHotel->adh = adh;
    newHotel->rno = generateUniqueRoomNumber();
    newHotel->next = NULL;

    if (head == NULL) {
        head = newHotel;
    }
    else {
        Hotel* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newHotel;
    }
    printf("Your Room Number is %d\n",newHotel->rno);
}

void displayHotels() {
    if (head == NULL) {
        printf("No hotels booked.\n");
        return;
    }

    Hotel* temp = head;
    printf("Booked Hotels:\n");
    while (temp != NULL) {
        printf("Name: %s\n", temp->name);
        printf("Phone Number: %ld\n", temp->ph);
        printf("Place: %s\n", temp->place);
        printf("Aadhar Number: %ld\n", temp->adh);
        printf("Room Number: %d\n", temp->rno);
        printf("\n");
        temp = temp->next;
    }
}

void removeHotel(int rno) {
    if (head == NULL) {
        printf("No hotels booked.\n");
        return;
    }

    if (head->rno == rno) {
        Hotel* temp = head;
        head = head->next;
        free(temp);
        printf("Hotel checkout successful.\n");
        return;
    }

    Hotel* temp = head;
    while (temp->next != NULL) {
        if (temp->next->rno == rno) {
            Hotel* deletedHotel = temp->next;
            temp->next = temp->next->next;
            free(deletedHotel);
            printf("Hotel checkout successful.\n");
            return;
        }
        temp = temp->next;
    }

    printf("No hotel booked with the given room number.\n");
}
void console_clear()
{
    system("clear");
}


int main() {
    int rno,choice;
    console_clear();

    do {
        printf("1-Room booking\n");
        printf("2-Room checkout\n");
        printf("3-Display booked hotels\n");
        printf("4-Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Room booking
                console_clear();
                char name[50];
                long int ph;
                char place[20];
                long int adh;

                printf("Enter your name: ");
                scanf("%s", name);
                printf("Enter your phone number: ");
                scanf("%ld", &ph);
                printf("Enter your place: ");
                scanf("%s", place);
                printf("Enter your Aadhar number: ");
                scanf("%ld", &adh);

                addHotel(name, ph, place, adh);
                printf("Room booked successful\n");
                break;
            }
            case 2: {
                // Room checkout
                console_clear();
                long int adh;
                printf("Enter the room number to checkout:");
                scanf("%d", &rno);

                removeHotel(rno);
                break;
            }
            case 3: {
                // Display booked hotels
                console_clear();
                displayHotels();
                break;
            }
            case 4: {
                // Exit
                console_clear();
                printf("Thank you!!!\n");
                break;
            }
            default: {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }

        printf("\n");
    } while (choice != 4);

    // Free memory allocated for hotels
    Hotel* temp = head;
    while (temp != NULL) {
        Hotel* nextHotel = temp->next;
        free(temp);
        temp = nextHotel;
    }

    return 0;
}
