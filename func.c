/* EL2008 Pemecahan Masalah dengan C 2003/2024
 * Tugas Besar PMC
 * Kelompok  : 9
 * Kelas     : 01
 * File      : func.c
 * Deskripsi : File berisi algoritma fungsi yang digunakan
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

#define MAX_Char 100
#define MAX_Data 500
#define MAX_DIAGNOSIS 50

// Deklarasi array global untuk menyimpan data
DataPasien patient_data[MAX_Data];
RiwayatPasien patient_record[MAX_Data];
int total_patients = 0;
int total_records = 0;

// Fungsi parsing CSV
void parseCSV(){
    // Deklarasi variabel yang dibutuhkan
    char buffer[512];

    // Membuka file CSV
    FILE *file1 = fopen("data_pasien.csv", "r"); // open file external data_pasien.csv
    if (file1 == NULL){
        printf("file 1 not found.");
    }

    // Bagian parsing file CSV
    fgets(buffer, sizeof(buffer), file1); // Membaca baris pertama teks dari file1


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
        char* id = strtok(NULL, "\n");

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

        
    FILE *file2 = fopen("riwayat_pasien.csv", "r"); // open file external riwayat_pasien.csv
        if (file2 == NULL){
        printf("file 2 not found.");
    }

    
    fgets(buffer, sizeof(buffer), file2); // Membaca baris pertama teks dari file2 
    
    // Parsing file 2
    while(fgets(buffer, sizeof(buffer), file2)){
        char* no = strtok(buffer, ",");
        char* date = strtok(NULL, ",");
        char* id = strtok(NULL, ",");
        char* diagnose = strtok(NULL, ",");
        char* act = strtok(NULL, ",");
        char* control = strtok(NULL, ",");
        char* cost = strtok(NULL, "\n");

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

/*Fitur nomor 1*/
void writePatient() {
    FILE *file1 = fopen("data_pasien.csv", "w");
    if (file1 == NULL) {
        printf("File 1 not found.\n");
        return;
    }
    fprintf(file1, "No,Nama Lengkap,Alamat,Kota,Tempat Lahir,Tanggal Lahir,Umur (th),No BPJS,ID Pasien\n");
    for (int i = 0; i < total_patients; i++) {
        fprintf(file1, "%d,%s,%s,%s,%s,%s,%d,%s,%s\n", patient_data[i].number, patient_data[i].namaPasien,
                patient_data[i].alamat, patient_data[i].kota, patient_data[i].tempatLahir,
                patient_data[i].tanggalLahir, patient_data[i].umur, patient_data[i].bpjs, patient_data[i].idPasien);
    }
    fclose(file1);
}

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
        writePatient();
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
            writePatient();
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
            writePatient();
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


/*Fitur nomor 2*/
// Fungsi menambahkan data pada daftar riwayat pasien (add, update, delete)
void writeRecords() {
    FILE *file2 = fopen("riwayat_pasien.csv", "w");
    if (file2 == NULL) {
        printf("File 2 not found.\n");
        return;
    }
    fprintf(file2, "No,Tanggal,ID,Diagnosis,Tindakan,Kontrol,Biaya\n");
    for (int i = 0; i < total_records; i++) {
        fprintf(file2, "%d,%s,%s,%s,%s,%s,%d\n", patient_record[i].number, patient_record[i].tanggal,
                patient_record[i].idPasien, patient_record[i].diagnosis, patient_record[i].tindakan,
                patient_record[i].kontrol, patient_record[i].biaya);
    }
    fclose(file2);
}

// Fungsi untuk menampilkan daftar diagnosis dan mendapatkan pilihan dari user
void getDiagnosis(char *diagnosis) {
    int choice;
    printf("Pilih Diagnosis:\n");
    printf("1. Masuk Angin\n");
    printf("2. Dehidrasi\n");
    printf("3. Keseleo\n");
    printf("4. Pusing\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            strcpy(diagnosis, "Masuk Angin");
            break;
        case 2:
            strcpy(diagnosis, "Dehidrasi");
            break;
        case 3:
            strcpy(diagnosis, "Keseleo");
            break;
        case 4:
            strcpy(diagnosis, "Pusing");
            break;
        default:
            printf("Pilihan tidak valid. Diagnosis diatur ke 'Tidak Diketahui'.\n");
            strcpy(diagnosis, "Tidak Diketahui");
            break;
    }
}

// Fungsi untuk menampilkan daftar tindakan dan mendapatkan pilihan dari user
int getTindakan(char *tindakan) {
    int choice, biaya_tindakan = 0;
    printf("Pilih Tindakan:\n");
    printf("1. Pemeriksaan (Rp125000)\n");
    printf("2. Vaksinasi (Rp100000)\n");
    printf("3. Cek gula darah (Rp25000)\n");
    printf("4. Pemasangan infus (Rp125000)\n");
    printf("5. Pengobatan (Rp150000)\n");
    printf("Masukkan pilihan: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            strcpy(tindakan, "Pemeriksaan");
            biaya_tindakan = 125000;
            break;
        case 2:
            strcpy(tindakan, "Vaksinasi");
            biaya_tindakan = 100000;
            break;
        case 3:
            strcpy(tindakan, "Cek gula darah");
            biaya_tindakan = 25000;
            break;
        case 4:
            strcpy(tindakan, "Pemasangan infus");
            biaya_tindakan = 125000;
            break;
        case 5:
            strcpy(tindakan, "Pengobatan");
            biaya_tindakan = 150000;
            break;
        default:
            printf("Pilihan tidak valid. Tindakan diatur ke 'Tidak Diketahui'.\n");
            strcpy(tindakan, "Tidak Diketahui");
            biaya_tindakan = 0;
            break;
    }
    return biaya_tindakan;
}

// Fungsi add riwayat pasien
void addRiwayatPasien() {
    printf("Masukkan detail riwayat pasien:\n");
    patient_record[total_records].number = total_records + 1; // Atur nomor berdasarkan hitungan saat ini
    printf("Tanggal: ");
    scanf(" %[^\n]", patient_record[total_records].tanggal);
    printf("ID Pasien: ");
    scanf(" %[^\n]", patient_record[total_records].idPasien);
    
    getDiagnosis(patient_record[total_records].diagnosis);
    int biaya_tindakan = getTindakan(patient_record[total_records].tindakan);
    
    printf("Kontrol: ");
    scanf(" %[^\n]", patient_record[total_records].kontrol);
    patient_record[total_records].biaya = 15000 + 125000 + biaya_tindakan; // Pendaftaran + Pemeriksaan + Tindakan
    total_records++;

    // Panggil fungsi writeRecords untuk memperbarui file CSV
    writeRecords();
    printf("Data riwayat pasien berhasil ditambahkan.\n");
}

// Fungsi update riwayat pasien dengan akses id pasien
void updateRiwayatPasien() {
    char id[20];
    printf("Masukkan ID pasien: ");
    scanf(" %[^\n]", id);
    int found = 0;
    printf("Pilih nomor urut rekam medis pasien:\n");
    for (int i = 0; i < total_records; i++) {
        if (strcmp(patient_record[i].idPasien, id) == 0) {
            printf("Riwayat pasien %d: Tanggal: %s, Diagnosis: %s, Tindakan: %s, Kontrol: %s, Biaya (Rp): %d\n",
                   i + 1, patient_record[i].tanggal, patient_record[i].diagnosis,
                   patient_record[i].tindakan, patient_record[i].kontrol, patient_record[i].biaya);
            found = 1;
        }
    }
    if (!found) {
        printf("Riwayat pasien berdasarkan ID yang di input tidak dapat ditemukan.\n");
        return;
    }
    printf("Masukkan nomor urut rekam medis pasien: ");
    int k; //recordNumber
    scanf("%d", &k);
    if (k < 1 || k > total_records) {
        printf("Nomor urut rekam medis tidak valid.\n");
        return;
    }
    k--; 
    printf("Masukkan detail data riwayat pasien yang baru:\n");
    printf("Tanggal: ");
    scanf(" %[^\n]", patient_record[k].tanggal);
    
    getDiagnosis(patient_record[k].diagnosis);
    int biaya_tindakan = getTindakan(patient_record[k].tindakan);
    
    printf("Kontrol: ");
    scanf(" %[^\n]", patient_record[k].kontrol);
    patient_record[k].biaya = 15000 + 125000 + biaya_tindakan; // Pendaftaran + Pemeriksaan + Tindakan

    writeRecords(); // Memperbarui file CSV setelah melakukan update
    printf("Data riwayat pasien berhasil diubah.\n");
}

// Fungsi delete riwayat pasien dengan akses id pasien
void deleteRiwayatPasien() {
    char id[20];
    printf("Masukkan ID pasien: ");
    scanf(" %[^\n]", id);
    int found = 0;
    printf("Pilih nomor urut rekam medis pasien:\n");
    for (int i = 0; i < total_records; i++) {
        if (strcmp(patient_record[i].idPasien, id) == 0) {
            printf("Rekam medis %d: Tanggal: %s, Diagnosis: %s, Tindakan: %s, Kontrol: %s, Biaya (Rp): %d\n",
                   i + 1, patient_record[i].tanggal, patient_record[i].diagnosis,
                   patient_record[i].tindakan, patient_record[i].kontrol, patient_record[i].biaya);
            found = 1;
        }
    }
    if (!found) {
        printf("Riwayat pasien berdasarkan ID yang di input tidak dapat ditemukan.\n");
        return;
    }
    printf("Masukkan nomor urut rekam medis pasien: ");
    int k; //recordNumber
    scanf("%d", &k);
    if (k < 1 || k > total_records) {
        printf("Nomor urut rekam medis tidak valid.\n");
        return;
    }

    // Geser indeks nomor urut dan mengubah indeks
    for (int i = k - 1; i < total_records - 1; i++) {
        patient_record[i] = patient_record[i + 1];
        patient_record[i].number = i + 1; // Ubah nomor urutan dengan geser indeks
    }
    total_records--;

    writeRecords(); // Menulis kembali ke file setelah melakukan delete
    printf("Data riwayat pasien berhasil dihapus.\n");
}

// Fungsi search riwayat pasien dengan akses id pasien
void searchRiwayatPasien() {
    char id[20];
    printf("Masukkan ID pasien: ");
    scanf(" %[^\n]", id);
    int found = 0;
    printf("\nHasil Pencarian:\n");
    printf("+------+----------------------+------------------+----------------------+---------------------+---------------------+------------+\n");
    printf("|  No  |       Tanggal        |        ID        |       Diagnosis      |       Tindakan      |       Kontrol       |    Biaya   |\n");
    printf("+------+----------------------+------------------+----------------------+---------------------+---------------------+------------+\n");
    for (int i = 0; i < total_records; i++) {
        if (strcmp(patient_record[i].idPasien, id) == 0) {
            printf("| %4d | %-20s | %-16s | %-20s | %-19s | %-19s | Rp %-7d |\n",
                patient_record[i].number, patient_record[i].tanggal, patient_record[i].idPasien,
                patient_record[i].diagnosis, patient_record[i].tindakan, patient_record[i].kontrol,
                patient_record[i].biaya);
            found = 1;
        }
    }
    printf("+------+----------------------+------------------+----------------------+---------------------+---------------------+------------+\n");

    if (!found) {
        printf("Riwayat pasien berdasarkan ID yang di input tidak dapat ditemukan.\n");
    }
}


/*Fitur nomor 3*/
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


/*Fitur nomor 4*/
void laporanPendapatan(RiwayatPasien riwayat[], int count) {
    int pendapatan_bulanan[12] = {0};
    int pendapatan_tahunan[10] = {0};
    int tahun_terkecil = 9999, tahun_terbesar = 0;

    for (int i = 0; i < count; i++) {
        int tahun, bulan;
        sscanf(riwayat[i].tanggal, "%d-%d", &tahun, &bulan);
        pendapatan_bulanan[bulan - 1] += riwayat[i].biaya;

        int tahun_idx = tahun - 2020;
        if (tahun_idx >= 0 && tahun_idx < 10) {
            pendapatan_tahunan[tahun_idx] += riwayat[i].biaya;
        }

        if (tahun < tahun_terkecil) tahun_terkecil = tahun;
        if (tahun > tahun_terbesar) tahun_terbesar = tahun;
    }

    printf("Laporan Pendapatan Bulanan:\n");
    for (int i = 0; i < 12; i++) {
        printf("Bulan %d: Rp %d\n", i + 1, pendapatan_bulanan[i]);
    }

    printf("\nLaporan Pendapatan Tahunan:\n");
    for (int i = tahun_terkecil; i <= tahun_terbesar; i++) {
        int tahun_idx = i - 2020;
        printf("Tahun %d: Rp %d\n", i, pendapatan_tahunan[tahun_idx]);
    }

    printf("\nRata-rata Pendapatan Tahunan:\n");
    for (int i = tahun_terkecil; i <= tahun_terbesar; i++) {
        int tahun_idx = i - 2020;
        printf("Tahun %d: Rp %d\n", i, pendapatan_tahunan[tahun_idx] / 12);
    }
}

/*Fitur nomor 5*/
void laporanPasien(RiwayatPasien riwayat_pasien[], int count) {
    int pasien_bulanan[12] = {0};
    int pasien_tahunan[10] = {0};  // Asumsi data dari tahun 2020 hingga 2029
    DiagnosisCount diagnosis_bulanan[12][MAX_DIAGNOSIS] = {{{0}}};
    DiagnosisCount diagnosis_tahunan[10][MAX_DIAGNOSIS] = {{{0}}};
    int tahun;
    int bulan;
    int diagnosis_bulan_count[12] = {0};
    int diagnosis_tahun_count[10] = {0};
    int tahun_terkecil = 2029, tahun_terbesar = 2020;

    for (int i = 0; i < count; i++) {
        sscanf(riwayat_pasien[i].tanggal, "%d-%*s-%d", &bulan, &tahun);

        if (tahun < tahun_terkecil) tahun_terkecil = tahun;
        if (tahun > tahun_terbesar) tahun_terbesar = tahun;

        pasien_bulanan[bulan - 1]++;
        pasien_tahunan[tahun - 2020]++;

        int bulan_idx = bulan - 1;
        int tahun_idx = tahun - 2020;

        // Update diagnosis bulanan
        int found = 0;
        for (int j = 0; j < diagnosis_bulan_count[bulan_idx]; j++) {
            if (strcmp(diagnosis_bulanan[bulan_idx][j].diagnosis, riwayat_pasien[i].diagnosis) == 0) {
                diagnosis_bulanan[bulan_idx][j].jumlah++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(diagnosis_bulanan[bulan_idx][diagnosis_bulan_count[bulan_idx]].diagnosis, riwayat_pasien[i].diagnosis);
            diagnosis_bulanan[bulan_idx][diagnosis_bulan_count[bulan_idx]].jumlah = 1;
            diagnosis_bulan_count[bulan_idx]++;
        }

        // Update diagnosis tahunan
        found = 0;
        for (int j = 0; j < diagnosis_tahun_count[tahun_idx]; j++) {
            if (strcmp(diagnosis_tahunan[tahun_idx][j].diagnosis, riwayat_pasien[i].diagnosis) == 0) {
                diagnosis_tahunan[tahun_idx][j].jumlah++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(diagnosis_tahunan[tahun_idx][diagnosis_tahun_count[tahun_idx]].diagnosis, riwayat_pasien[i].diagnosis);
            diagnosis_tahunan[tahun_idx][diagnosis_tahun_count[tahun_idx]].jumlah = 1;
            diagnosis_tahun_count[tahun_idx]++;
        }
    }

    printf("Laporan Jumlah Pasien Bulanan:\n");
    for (int i = 0; i < 12; i++) {
        printf("Bulan %d: %d pasien\n", i + 1, pasien_bulanan[i]);
        printf("Penyakit:\n");
        for (int j = 0; j < diagnosis_bulan_count[i]; j++) {
            printf("  %s: %d kasus\n", diagnosis_bulanan[i][j].diagnosis, diagnosis_bulanan[i][j].jumlah);
        }
    }

    printf("\nLaporan Jumlah Pasien Tahunan:\n");
    for (int i = tahun_terkecil; i <= tahun_terbesar; i++) {
        printf("Tahun %d: %d pasien\n", i, pasien_tahunan[i - 2020]);
        printf("Penyakit:\n");
        for (int j = 0; j < diagnosis_tahun_count[i - 2020]; j++) {
            printf("  %s: %d kasus\n", diagnosis_tahunan[i - 2020][j].diagnosis, diagnosis_tahunan[i - 2020][j].jumlah);
        }
    }
}

/*Fitur nomor 6*/
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
