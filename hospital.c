#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "hospital.h"

void Current_time(char *c_time, size_t size) {
    time_t t;
    struct tm *time_info;

    time(&t);
    time_info = localtime(&t);

    strftime(c_time, size, "%Y-%m-%d %H:%M:%S", time_info);

    printf("Time: %02d-%02d-%04d  %02d:%02d:%02d\n\n",
        time_info->tm_mday, time_info->tm_mon + 1, time_info->tm_year + 1900,
        time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
}

int doctorIDCheck(int id) {
    struct Doctor d;
    FILE *fp = fopen(DOCTOR_FILE, "rb");
    if (!fp)
        return 0;

    while (fread(&d, sizeof(struct Doctor), 1, fp)) {
        if (id == d.id) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int patientIDCheck(int id) {
    struct Patient p;
    FILE *fp = fopen(PATIENT_FILE, "rb");
    if (!fp)
        return 0;

    while (fread(&p, sizeof(struct Patient), 1, fp)) {
        if (id == p.id) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void addDoctor() {
    FILE *fp;
    struct Doctor d;
    int id;

    fp = fopen(DOCTOR_FILE, "ab");

    printf("\nEnter doctor ID: ");
    scanf("%d", &id);

    if (doctorIDCheck(id) != 0) {
        printf("Enter doctor ID: ");
        scanf("%d", &id);
    }

    d.id = id;

    printf("\nEnter name: ");
    scanf(" %[^\n]", d.name);

    printf("\nEnter specialization: ");
    scanf(" %[^\n]", d.specialization);

    fwrite(&d, sizeof(struct Doctor), 1, fp);
    fclose(fp);

    printf("\nDoctor added successfully!\n\n");
}

void addPatient() {
    FILE *fp;
    struct Patient p;
    int id;

    fp = fopen(PATIENT_FILE, "ab");

    printf("\nEnter patient ID: ");
    scanf("%d", &id);

    if (patientIDCheck(id) != 0) {
        printf("\nID already exists!\n\n");
        printf("Enter patient ID: ");
        scanf("%d", &id);
    }

    p.id = id;

    printf("\nEnter name: ");
    scanf(" %[^\n]", p.name);

    printf("\nEnter age: ");
    scanf("%d", &p.age);

    fwrite(&p, sizeof(struct Patient), 1, fp);
    fclose(fp);

    printf("\nPatient added successfully!\n\n");
}

void viewDoctors() {
    FILE *fp;
    struct Doctor d;

    fp = fopen(DOCTOR_FILE, "rb");
    if (!fp) {
        printf("\nNo doctors found.\n\n");
        return;
    }

    printf("\nID\tName\t\tSpecialization\n");
    printf("-------------------------------------\n");

    while (fread(&d, sizeof(struct Doctor), 1, fp)) {
        printf("%d\t%-15s %s\n", d.id, d.name, d.specialization);
    }
    printf("\n");

    fclose(fp);
}

void viewPatients() {
    FILE *fp;
    struct Patient p;

    fp = fopen(PATIENT_FILE, "rb");
    if (!fp) {
        printf("\nNo patients found.\n\n");
        return;
    }

    printf("\nID\tName\t\tAge\n");
    printf("------------------------------\n");

    while (fread(&p, sizeof(struct Patient), 1, fp)) {
        printf("%d\t%-15s %d\n", p.id, p.name, p.age);
    }
    printf("\n");

    fclose(fp);
}

void bookAppointment() {
    FILE *fp;
    struct Appointment a;
    int d_id, p_id;

    fp = fopen(APPOINT_FILE, "ab");

    printf("\nEnter doctor ID: ");
    scanf("%d", &d_id);

    printf("\nEnter patient ID: ");
    scanf("%d", &p_id);

    if (doctorIDCheck(d_id) == 0 || patientIDCheck(p_id) == 0) {
        printf("\nDoctor or Patient ID doesn't exists!\n");
        
        printf("\nEnter doctor ID: ");
        scanf("%d", &d_id);

        printf("\nEnter patient ID: ");
        scanf("%d", &p_id);
    }
    a.doctor_id = d_id;
    a.patient_id = p_id;

    printf("\nEnter appointment date (DD-MM-YYYY): ");
    scanf(" %s", a.date);

    printf("\nAppointment booked successfully!\n");
    Current_time(a.time, sizeof(a.time));

    fwrite(&a, sizeof(struct Appointment), 1, fp);    

    fclose(fp);
}

void viewAppointments() {
    FILE *fp, *fpd, *fpf;
    struct Appointment a;
    struct Doctor d;
    struct Patient p;

    fp = fopen(APPOINT_FILE, "rb");
    fpd = fopen(DOCTOR_FILE, "rb");
    fpf = fopen(PATIENT_FILE, "rb");

    if (!fp) {
        printf("\nNo appointments found.\n\n");
        return;
    }

    if (!fpd || !fpf) {
        printf("\nFile error!\n\n");
        return;
    }

    printf("\n%-10s %-15s %-10s %-15s %-12s %-8s\n",
       "Doctor ID", "Doctor Name",
       "Patient ID", "Patient Name",
       "Date", "Time");
    printf("------------------------------------\n");

    while (fread(&a, sizeof(struct Appointment), 1, fp)) {
        // Find doctor
        rewind(fpd);
        struct Doctor d;
        int found_d = 0;
        while (fread(&d, sizeof(struct Doctor), 1, fpd)) {
            if (d.id == a.doctor_id) {
                found_d = 1;
                break;
            }
        }

        // Find patient
        rewind(fpf);
        struct Patient p;
        int found_p = 0;
        while (fread(&p, sizeof(struct Patient), 1, fpf)) {
            if (p.id == a.patient_id) {
                found_p = 1;
                break;
            }
        }

        if (found_d && found_p) {
            printf("%-10d %-15s %-10d %-15s %-12s %-8s\n",
                        a.doctor_id,
                        d.name,
                        a.patient_id,
                        p.name,
                        a.date,
                        a.time);
        }
    }
    printf("\n");

    fclose(fp);
}