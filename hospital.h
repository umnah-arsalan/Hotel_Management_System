#ifndef HOSPITAL_H
#define HOSPITAL_H

#define DOCTOR_FILE "doctors.dat"
#define PATIENT_FILE "patients.dat"
#define APPOINT_FILE "appointments.dat"

struct Doctor {
    int id;
    char name[50];
    char specialization[50];
};

struct Patient {
    int id;
    char name[50];
    int age;
};

struct Appointment {
    int doctor_id;
    int patient_id;
    char date[20];
    char time[50];
};

/* Function Prototypes */
void Current_time(char *c_time, size_t size);
int doctorIDCheck(int id);
int patientIDCheck(int id);
void addDoctor();
void addPatient();
void viewDoctors();
void viewPatients();
void bookAppointment();
void viewAppointments();

#endif