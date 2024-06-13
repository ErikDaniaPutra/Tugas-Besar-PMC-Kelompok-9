#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100
#define MAX_DATA 500

typedef struct {
    int number;
    char namaPasien[MAX_CHAR];
    char alamat[MAX_CHAR];
    char kota[MAX_CHAR];
    char tempatLahir[MAX_CHAR];
    char tanggalLahir[MAX_CHAR];
    int umur;
    char bpjs[MAX_CHAR];
    char idPasien[MAX_CHAR];
} DataPasien;

typedef struct {
    int number;
    char tanggal[MAX_CHAR];
    char idPasien[MAX_CHAR];
    char diagnosis[MAX_CHAR];
    char tindakan[MAX_CHAR];
    char kontrol[MAX_CHAR];
    int biaya;
} RiwayatPasien;

// Deklarasi array global untuk menyimpan data
DataPasien patient_data[MAX_DATA];
RiwayatPasien patient_record[MAX_DATA];
int total_patients = 0;
int total_records = 0;

void parseCSV(){
    // Deklarasi variabel yang dibutuhkan
    char buffer[512];

    // Membuka file CSV
    FILE *file1 = fopen("data_pasien.csv", "r"); // open file external data_pasien.csv
    if (file1 == NULL){
        printf("file 1 not found.");
    }
    
    FILE *file2 = fopen("riwayat_pasien.csv", "r"); // open file external riwayat_pasien.csv
        if (file2 == NULL){
        printf("file 2 not found.");
    }

    // Bagian parsing file CSV
    fgets(buffer, sizeof(buffer), file1); // Membaca baris pertama teks dari file1
    fgets(buffer, sizeof(buffer), file2); // Membaca baris pertama teks dari file2 

    // Parsing file 1
    while(fgets(buffer, sizeof(buffer), file1)){
        char* no = strtok(buffer, ",");
        char* name = strtok(NULL, ",");
        char* address = strtok(NULL, ",");
        char* city = strtok(NULL, ",");
        char* place_of_birth = strtok(NULL, ",");
        char* date_of_birth = strtok(NULL, ",");
        char* age = strtok(NULL, ",");
        char* id_bpjs= strtok(NULL, ","); 
        char* id = strtok(NULL, ",");

        if(no == NULL || name == NULL ||address == NULL || city == NULL || place_of_birth == NULL 
        || date_of_birth == NULL || age == NULL || id_bpjs == NULL || id == NULL){
            continue;
        }

        patient_data[total_patients].number = atoi(no);
        strncpy(patient_data[total_patients].namaPasien, name, sizeof(patient_data[total_patients].namaPasien));
        strncpy(patient_data[total_patients].alamat, address, sizeof(patient_data[total_patients].alamat));
        strncpy(patient_data[total_patients].kota, city, sizeof(patient_data[total_patients].kota));
        strncpy(patient_data[total_patients].tempatLahir, place_of_birth, sizeof(patient_data[total_patients].tempatLahir));
        strncpy(patient_data[total_patients].tanggalLahir, date_of_birth, sizeof(patient_data[total_patients].tanggalLahir));
        patient_data[total_patients].umur = atoi(age);
        strncpy(patient_data[total_patients].bpjs, id_bpjs, sizeof(patient_data[total_patients].bpjs));
        strncpy(patient_data[total_patients].idPasien, id, sizeof(patient_data[total_patients].idPasien));
        total_patients++;
    }
    fclose(file1);

    // Parsing file 2
    while(fgets(buffer, sizeof(buffer), file2)){
        char* no = strtok(buffer, ",");
        char* date = strtok(NULL, ",");
        char* id = strtok(NULL, ",");
        char* diagnose = strtok(NULL, ",");
        char* act = strtok(NULL, ",");
        char* control = strtok(NULL, ",");
        char* cost = strtok(NULL, ",");

        if(no == NULL || date == NULL || id == NULL || diagnose == NULL || control == NULL || cost == NULL){
            continue;;
        }

        patient_record[total_records].number = atoi(no);
        strncpy(patient_record[total_records].tanggal, date, sizeof(patient_record[total_records].tanggal));
        strncpy(patient_record[total_records].idPasien, id, sizeof(patient_record[total_records].idPasien));
        strncpy(patient_record[total_records].diagnosis, diagnose, sizeof(patient_record[total_records].diagnosis));
        strncpy(patient_record[total_records].tindakan, act, sizeof(patient_record[total_records].tindakan));
        strncpy(patient_record[total_records].kontrol, control, sizeof(patient_record[total_records].kontrol));
        patient_record[total_records].biaya = atoi(cost);
        total_records++;
    }
    fclose(file2);
}

// mencari pasien berdasarkan ID Pasien
DataPasien* cari_ID(const char* id) {
    for (int i = 0; i < total_patients; i++) {
        if (strcmp(patient_data[i].idPasien, id) == 0) {
            return &patient_data[i];
        }
    }
    return NULL;
}

// informasi pasien dan riwayatnya
void informasiRiwayatPatient(const char* id) {
    DataPasien* patient = cari_ID(id);
    if (patient == NULL) {
        printf("Pasien tidak ditemukan.\n");
        return;
    }
    
    // informasi pasien
    printf("\nInformasi Pasien:\n");
    printf("Nama Pasien: %s\n", patient->namaPasien);
    printf("Alamat: %s\n", patient->alamat);
    printf("Kota: %s\n", patient->kota);
    printf("Tempat Lahir: %s\n", patient->tempatLahir);
    printf("Tanggal Lahir: %s\n", patient->tanggalLahir);
    printf("Umur: %d\n", patient->umur);
    printf("No BPJS: %s\n", patient->bpjs);
    printf("ID Pasien: %s\n\n", patient->idPasien);
    
    // riwayat pasien
    printf("Riwayat Pasien:\n");
    int found = 0;
    for (int i = 0; i < total_records; i++) {
        if (strcmp(patient_record[i].idPasien, id) == 0) {
            printf("Tanggal: %s\n", patient_record[i].tanggal);
            printf("Diagnosis: %s\n", patient_record[i].diagnosis);
            printf("Tindakan: %s\n", patient_record[i].tindakan);
            printf("Kontrol: %s\n", patient_record[i].kontrol);
            printf("Biaya: %d\n\n", patient_record[i].biaya);
            found = 1;
        }
    }
    if (!found) {
        printf("Riwayat tidak ditemukan.\n");
    }
}

// pasien yang perlu kembali kontrol
void kontrolPatient() {
    printf("\nPasien yang Perlu Kembali Kontrol:\n");
    int found = 0;
    for (int i = 0; i < total_records; i++) {
        if (strlen(patient_record[i].kontrol) > 0 && strcmp(patient_record[i].kontrol, "-") != 0) {
            DataPasien* patient = cari_ID(patient_record[i].idPasien);
            if (patient != NULL) {
                printf("Nama Pasien: %s\n", patient->namaPasien);
                printf("ID Pasien: %s\n", patient->idPasien);
                printf("Tanggal Kontrol: %s\n\n", patient_record[i].kontrol);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("Tidak ada pasien yang perlu kembali kontrol.\n");
    }
}

// Fungsi utama
int main() {
    parseCSV();
    /*char buffer[512];

    // Membuka file CSV pasien
    FILE *file1 = fopen("data_pasien.csv", "r");
    if (file1 == NULL) {
        printf("file data_pasien.csv tidak ditemukan.\n");
        return 1;
    }

    // Melewati header
    fgets(buffer, sizeof(buffer), file1);

    // Parsing file 1
    while (fgets(buffer, sizeof(buffer), file1)) {
        char* no = strtok(buffer, ",");
        char* name = strtok(NULL, ",");
        char* address = strtok(NULL, ",");
        char* city = strtok(NULL, ",");
        char* place_of_birth = strtok(NULL, ",");
        char* date_of_birth = strtok(NULL, ",");
        char* age = strtok(NULL, ",");
        char* id_bpjs = strtok(NULL, ",");
        char* id = strtok(NULL, "\n");

        if (no == NULL || name == NULL || address == NULL || city == NULL || place_of_birth == NULL
            || date_of_birth == NULL || age == NULL || id_bpjs == NULL || id == NULL) {
            continue;
        }

        patient_data[total_patients].number = atoi(no);
        strncpy(patient_data[total_patients].namaPasien, name, sizeof(patient_data[total_patients].namaPasien));
        strncpy(patient_data[total_patients].alamat, address, sizeof(patient_data[total_patients].alamat));
        strncpy(patient_data[total_patients].kota, city, sizeof(patient_data[total_patients].kota));
        strncpy(patient_data[total_patients].tempatLahir, place_of_birth, sizeof(patient_data[total_patients].tempatLahir));
        strncpy(patient_data[total_patients].tanggalLahir, date_of_birth, sizeof(patient_data[total_patients].tanggalLahir));
        patient_data[total_patients].umur = atoi(age);
        strncpy(patient_data[total_patients].bpjs, id_bpjs, sizeof(patient_data[total_patients].bpjs));
        strncpy(patient_data[total_patients].idPasien, id, sizeof(patient_data[total_patients].idPasien));
        total_patients++;
    }
    fclose(file1);

    // Membuka file CSV riwayat pasien
    FILE *file2 = fopen("riwayat_pasien.csv", "r");
    if (file2 == NULL) {
        printf("file riwayat_pasien.csv tidak ditemukan.\n");
        return 1;
    }

    // Melewati header
    fgets(buffer, sizeof(buffer), file2);

    // Parsing file 2
    while (fgets(buffer, sizeof(buffer), file2)) {
        char* no = strtok(buffer, ",");
        char* date = strtok(NULL, ",");
        char* id = strtok(NULL, ",");
        char* diagnose = strtok(NULL, ",");
        char* act = strtok(NULL, ",");
        char* control = strtok(NULL, ",");
        char* cost = strtok(NULL, "\n");

        if (no == NULL || date == NULL || id == NULL || diagnose == NULL || act == NULL || control == NULL || cost == NULL) {
            continue;
        }

        patient_record[total_records].number = atoi(no);
        strncpy(patient_record[total_records].tanggal, date, sizeof(patient_record[total_records].tanggal));
        strncpy(patient_record[total_records].idPasien, id, sizeof(patient_record[total_records].idPasien));
        strncpy(patient_record[total_records].diagnosis, diagnose, sizeof(patient_record[total_records].diagnosis));
        strncpy(patient_record[total_records].tindakan, act, sizeof(patient_record[total_records].tindakan));
        strncpy(patient_record[total_records].kontrol, control, sizeof(patient_record[total_records].kontrol));
        patient_record[total_records].biaya = atoi(cost);
        total_records++;
    }
    fclose(file2);*/

    int choice;
    do {
        printf("\nSistem Pencatatan Pasien Klinik X\n");
        printf("1. Cari Informasi dan Riwayat Pasien\n");
        printf("2. Lihat Pasien untuk Kontrol\n");
        printf("0. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                char id[MAX_CHAR];
                printf("Masukkan ID Pasien: ");
                fgets(id, MAX_CHAR, stdin);
                strtok(id, "\n");
                informasiRiwayatPatient(id);
                break;
            }
            case 2:
                kontrolPatient();
                break;
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
