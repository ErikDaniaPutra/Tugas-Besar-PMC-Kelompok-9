#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_ENTRIES 1000
#define MAX_DIAGNOSIS 50

typedef struct {
    int no;
    char tanggal[20];
    char id_pasien[20];
    char diagnosis[50];
    char tindakan[50];
    char kontrol[20];
    int biaya;
} RiwayatPasien;

typedef struct {
    char diagnosis[50];
    int jumlah;
} DiagnosisCount;

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

int main() {
    FILE *fp_riwayat;
    char line[MAX_LINE_LENGTH];
    RiwayatPasien riwayat_pasien[MAX_ENTRIES];
    int count_riwayat_pasien = 0;

    // Membuka file CSV untuk riwayat pasien
    fp_riwayat = fopen("riwayat_pasien.csv", "r");
    if (fp_riwayat == NULL) {
        perror("Tidak dapat membuka file riwayat_pasien.csv");
        return 1;
    }

    // Membaca header
    fgets(line, MAX_LINE_LENGTH, fp_riwayat);

    // Membaca data riwayat pasien
    while (fgets(line, MAX_LINE_LENGTH, fp_riwayat)) {
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d",
               &riwayat_pasien[count_riwayat_pasien].no,
               riwayat_pasien[count_riwayat_pasien].tanggal,
               riwayat_pasien[count_riwayat_pasien].id_pasien,
               riwayat_pasien[count_riwayat_pasien].diagnosis,
               riwayat_pasien[count_riwayat_pasien].tindakan,
               riwayat_pasien[count_riwayat_pasien].kontrol,
               &riwayat_pasien[count_riwayat_pasien].biaya);
        count_riwayat_pasien++;
    }
    fclose(fp_riwayat);

    // Melaporkan pasien
    laporanPasien(riwayat_pasien, count_riwayat_pasien);

    return 0;
}

