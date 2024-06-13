#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_Char 100
#define MAX_Data 500

typedef struct {
    int number;
    char namaPasien[MAX_Char];
    char alamat[MAX_Char];
    char kota[MAX_Char];
    char tempatLahir[MAX_Char];
    char tanggalLahir[MAX_Char];
    int umur;
    char bpjs[MAX_Char];
    char idPasien[MAX_Char];
} DataPasien;

typedef struct {
    int number;
    char tanggal[MAX_Char];
    char idPasien[MAX_Char];
    char diagnosis[MAX_Char];
    char tindakan[MAX_Char];
    char kontrol[MAX_Char];
    int biaya;
} RiwayatPasien;

DataPasien patient_data[MAX_Data];

void addDataPasien(DataPasien patient_data[], int *count) {
    if (*count < MAX_Data) {
        DataPasien new_data;
        new_data.number = *count + 1;

        printf("Masukkan nama pasien: ");
        fgets(new_data.namaPasien, MAX_Char, stdin);
        strtok(new_data.namaPasien, "\n"); // remove newline character

        printf("Masukkan alamat pasien: ");
        fgets(new_data.alamat, MAX_Char, stdin);
        strtok(new_data.alamat, "\n");

        printf("Masukkan kota pasien: ");
        fgets(new_data.kota, MAX_Char, stdin);
        strtok(new_data.kota, "\n");

        printf("Masukkan tempat lahir pasien: ");
        fgets(new_data.tempatLahir, MAX_Char, stdin);
        strtok(new_data.tempatLahir, "\n");

        printf("Masukkan tanggal lahir pasien: ");
        fgets(new_data.tanggalLahir, MAX_Char, stdin);
        strtok(new_data.tanggalLahir, "\n");

        printf("Masukkan umur pasien: ");
        scanf("%d", &new_data.umur);
        getchar();

        printf("Masukkan BPJS pasien: ");
        fgets(new_data.bpjs, MAX_Char, stdin);
        strtok(new_data.bpjs, "\n");

        printf("Masukkan ID pasien: ");
        fgets(new_data.idPasien, MAX_Char, stdin);
        strtok(new_data.idPasien, "\n");

        patient_data[*count] = new_data;
        (*count)++;
        printf("Data berhasil ditambahkan.\n");
    } else {
        printf("Array data penuh.\n");
    }
}

void changeDataPasien(DataPasien patient_data[], int count) {
    char name[MAX_Char];
    printf("Masukkan nama pasien yang akan diperbarui: ");
    fgets(name, MAX_Char, stdin);
    strtok(name, "\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(patient_data[i].namaPasien, name) == 0) {
            DataPasien updated_data;
            updated_data.number = patient_data[i].number;

            printf("Masukkan nama pasien baru: ");
            fgets(updated_data.namaPasien, MAX_Char, stdin);
            strtok(updated_data.namaPasien, "\n");

            printf("Masukkan alamat pasien baru: ");
            fgets(updated_data.alamat, MAX_Char, stdin);
            strtok(updated_data.alamat, "\n");

            printf("Masukkan kota pasien baru: ");
            fgets(updated_data.kota, MAX_Char, stdin);
            strtok(updated_data.kota, "\n");

            printf("Masukkan tempat lahir pasien baru: ");
            fgets(updated_data.tempatLahir, MAX_Char, stdin);
            strtok(updated_data.tempatLahir, "\n");

            printf("Masukkan tanggal lahir pasien baru: ");
            fgets(updated_data.tanggalLahir, MAX_Char, stdin);
            strtok(updated_data.tanggalLahir, "\n");

            printf("Masukkan umur pasien baru: ");
            scanf("%d", &updated_data.umur);
            getchar();

            printf("Masukkan BPJS pasien baru: ");
            fgets(updated_data.bpjs, MAX_Char, stdin);
            strtok(updated_data.bpjs, "\n");

            printf("Masukkan ID pasien baru: ");
            fgets(updated_data.idPasien, MAX_Char, stdin);
            strtok(updated_data.idPasien, "\n");

            patient_data[i] = updated_data;
            printf("Data berhasil diperbarui.\n");
            return;
        }
    }
    printf("Data tidak ditemukan.\n");
}

void deleteDataPasien(DataPasien patient_data[], int *count) {
    char name[MAX_Char];
    printf("Masukkan nama pasien yang akan dihapus: ");
    fgets(name, MAX_Char, stdin);
    strtok(name, "\n");

    for (int i = 0; i < *count; i++) {
        if (strcmp(patient_data[i].namaPasien, name) == 0) {
            for (int j = i; j < *count - 1; j++) {
                patient_data[j] = patient_data[j + 1];
                patient_data[j].number = j + 1; // update number to reflect new order
            }
            (*count)--;
            printf("Data berhasil dihapus.\n");
            return;
        }
    }
    printf("Data tidak ditemukan.\n");
}

void findDataPasien(DataPasien patient_data[], int count) {
    char name[MAX_Char];
    printf("Masukkan nama pasien yang akan dicari: ");
    fgets(name, MAX_Char, stdin);
    strtok(name, "\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(patient_data[i].namaPasien, name) == 0) {
            printf("Data ditemukan:\n");
            printf("No: %d\n", patient_data[i].number);
            printf("Nama Pasien: %s\n", patient_data[i].namaPasien);
            printf("Alamat: %s\n", patient_data[i].alamat);
            printf("Kota: %s\n", patient_data[i].kota);
            printf("Tempat Lahir: %s\n", patient_data[i].tempatLahir);
            printf("Tanggal Lahir: %s\n", patient_data[i].tanggalLahir);
            printf("Umur: %d\n", patient_data[i].umur);
            printf("BPJS: %s\n", patient_data[i].bpjs);
            printf("ID Pasien: %s\n", patient_data[i].idPasien);
            return;
        }
    }
    printf("Data tidak ditemukan.\n");
}

void writePatient() {
    FILE *file1 = fopen("data_pasien.csv", "w");
    if (file1 == NULL) {
        printf("File 1 not found.\n");
        return;
    }
    fprintf(file1, "No,Nama Lengkap,Alamat,Kota,Tempat Lahir,Tanggal Lahir,Umur (th),No BPJS,ID Pasien\n");
    for (int i = 0; i < total_patient; i++) {
        fprintf(file2, "%d,%s,%s,%s,%s,%s,%d,%s,%s\n", patient_data[i].number, patient_data[i].namaPasien,
                patient_data[i].alamat, patient_data[i].kota, patient_data[i].tempatLahir,
                patient_data[i].tanggalLahir, patient_data[i].umur, patient_data[i].bpjs, patient_data[i].idPasien);
    }
    fclose(file1);
}