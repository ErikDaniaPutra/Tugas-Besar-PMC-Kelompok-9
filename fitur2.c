/** EL2208 Pemecahan Masalah dengan C 2023/2024
 *   Kelas               : K01
 *   Nama (NIM)          : Laura Anggelina Shaad (18322016)
 *   Nama File           : fitur2.c
 *   Deskripsi           : TUBES (Fitur 2)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_Char 100
#define MAX_Data 500

typedef struct {
    int number;
    char tanggal[MAX_Char];
    char idPasien[MAX_Char];
    char diagnosis[MAX_Char];
    char tindakan[MAX_Char];
    char kontrol[MAX_Char];
    int biaya;
} RiwayatPasien;

// Deklarasi global variabel
RiwayatPasien patient_record[MAX_Data];
int j = 0; // recordCount

// Fungsi menambahkan data pada daftar riwayat pasien (add, update, delete)
void writeRecords() {
    FILE *file2 = fopen("riwayat_pasien.csv", "w");
    if (file2 == NULL) {
        printf("File 2 not found.\n");
        return;
    }
    fprintf(file2, "No,Tanggal,ID,Diagnosis,Tindakan,Kontrol,Biaya\n");
    for (int i = 0; i < j; i++) {
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
    patient_record[j].number = j + 1; // Atur nomor berdasarkan hitungan saat ini
    printf("Tanggal: ");
    scanf(" %[^\n]", patient_record[j].tanggal);
    printf("ID Pasien: ");
    scanf(" %[^\n]", patient_record[j].idPasien);
    
    getDiagnosis(patient_record[j].diagnosis);
    int biaya_tindakan = getTindakan(patient_record[j].tindakan);
    
    printf("Kontrol: ");
    scanf(" %[^\n]", patient_record[j].kontrol);
    patient_record[j].biaya = 15000 + 125000 + biaya_tindakan; // Pendaftaran + Pemeriksaan + Tindakan
    j++;

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
    for (int i = 0; i < j; i++) {
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
    if (k < 1 || k > j) {
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
    for (int i = 0; i < j; i++) {
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
    if (k < 1 || k > j) {
        printf("Nomor urut rekam medis tidak valid.\n");
        return;
    }

    // Geser indeks nomor urut dan mengubah indeks
    for (int i = k - 1; i < j - 1; i++) {
        patient_record[i] = patient_record[i + 1];
        patient_record[i].number = i + 1; // Ubah nomor urutan dengan geser indeks
    }
    j--;

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
    for (int i = 0; i < j; i++) {
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

// Program Utama
int main() {
    char buffer[512];
    FILE *file2 = fopen("riwayat_pasien.csv", "r");
    if (file2 == NULL) {
        printf("File 2 not found.\n");
        return 1;
    }
    // Parsing
    fgets(buffer, sizeof(buffer), file2); // Read header line
    while (fgets(buffer, sizeof(buffer), file2)) {
        char *no = strtok(buffer, ",");
        char *date = strtok(NULL, ",");
        char *id = strtok(NULL, ",");
        char *diagnose = strtok(NULL, ",");
        char *act = strtok(NULL, ",");
        char *control = strtok(NULL, ",");
        char *cost = strtok(NULL, ",");

        if (no == NULL || date == NULL || id == NULL || diagnose == NULL || control == NULL || cost == NULL) {
            continue;
        }

        patient_record[j].number = atoi(no);
        strncpy(patient_record[j].tanggal, date, sizeof(patient_record[j].tanggal) - 1);
        strncpy(patient_record[j].idPasien, id, sizeof(patient_record[j].idPasien) - 1);
        strncpy(patient_record[j].diagnosis, diagnose, sizeof(patient_record[j].diagnosis) - 1);
        strncpy(patient_record[j].tindakan, act, sizeof(patient_record[j].tindakan) - 1);
        strncpy(patient_record[j].kontrol, control, sizeof(patient_record[j].kontrol) - 1);
        patient_record[j].biaya = atoi(cost);
        j++;
    }
    fclose(file2);

    // Command menu program fitur 2
    int choice;
    do {
        printf("\nKlinik X Patient Management System\n");
        printf("1. Tambahkan Data Riwayat Pasien\n");
        printf("2. Ubah Data Riwayat Pasien\n");
        printf("3. Hapus Data Riwayat Pasien\n");
        printf("4. Pencarian Data Riwayat Pasien\n");
        printf("5. Keluar\n");
        printf("Masukkan pilihan anda: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRiwayatPasien();
                break;
            case 2:
                updateRiwayatPasien();
                break;
            case 3:
                deleteRiwayatPasien();
                break;
            case 4:
                searchRiwayatPasien();
                break;
            case 5:
                printf("Terimakasih!\n");
                break;
            default:
                printf("Pilihan tidak tersedia.\n");
        }
    } while (choice != 5);

    return 0;
}