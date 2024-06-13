#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_ENTRIES 1000

typedef struct {
    int no;
    char tanggal[20];
    char id_pasien[20];
    char diagnosis[50];
    char tindakan[50];
    char kontrol[50];
    int biaya;
} RiwayatPasien;

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

    // Melaporkan pendapatan
    laporanPendapatan(riwayat_pasien, count_riwayat_pasien);

    return 0;
}
