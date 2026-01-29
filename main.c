#include <stdio.h>
#include <stdlib.h>
#include "hospital.h"

int main() {
    int choice;

    while (1) {
        printf("--- Hospital Management System ---\n\n");
        printf("1. Add Doctor\n");
        printf("2. Add Patient\n");
        printf("3. View Doctors\n");
        printf("4. View Patients\n");
        printf("5. Book Appointment\n");
        printf("6. View Appointments\n");
        printf("7. Exit\n\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addDoctor(); break;
            case 2: addPatient(); break;
            case 3: viewDoctors(); break;
            case 4: viewPatients(); break;
            case 5: bookAppointment(); break;
            case 6: viewAppointments(); break;
            case 7: exit(0);
            default: printf("\nInvalid choice!\n");
        }
    }
}
