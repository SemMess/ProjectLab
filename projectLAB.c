#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nama[50];
    int umur;
    float nilai;
} Mahasiswa;
void tambahMahasiswa();
void tampilkanMahasiswa();
void cariMahasiswa();
void urutkanMahasiswa();
int bacaData(Mahasiswa mahasiswa[], int maxSize);
void simpanData(Mahasiswa mahasiswa[], int jumlah);

#define MAX_MAHASISWA 100

int main() {
    int pilihan;

    do {
        printf("\n=== PENGELOLAAN DATA MAHASISWA ===\n");
        printf("1. Tambah Mahasiswa\n");
        printf("2. Tampilkan Semua Mahasiswa\n");
        printf("3. Cari Mahasiswa Berdasarkan Nama\n");
        printf("4. Urutkan Mahasiswa Berdasarkan Nilai\n");
        printf("5. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar(); // Menghapus karakter newline dari input buffer

        switch (pilihan) {
            case 1:
                tambahMahasiswa();
                break;
            case 2:
                tampilkanMahasiswa();
                break;
            case 3:
                cariMahasiswa();
                break;
            case 4:
                urutkanMahasiswa();
                break;
            case 5:
                printf("Terima kasih telah menggunakan program ini.\n");
                break;
            default:
                printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (pilihan != 5);

    return 0;
}
void tambahMahasiswa() {
    FILE *file = fopen("data_mahasiswa.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    Mahasiswa m;
    printf("Masukkan Nama Mahasiswa: ");
    fgets(m.nama, sizeof(m.nama), stdin);
    m.nama[strcspn(m.nama, "\n")] = 0; // Menghapus newline
    printf("Masukkan Umur Mahasiswa: ");
    scanf("%d", &m.umur);
    printf("Masukkan Nilai Mahasiswa: ");
    scanf("%f", &m.nilai);
    getchar();

    fprintf(file, "%s,%d,%.2f\n", m.nama, m.umur, m.nilai);
    fclose(file);

    printf("Mahasiswa berhasil ditambahkan!\n");
}
void tampilkanMahasiswa() {
    FILE *file = fopen("data_mahasiswa.txt", "r");
    if (file == NULL) {
        printf("Tidak ada data mahasiswa.\n");
        return;
    }

    char buffer[100];
    printf("\n=== DATA MAHASISWA ===\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        char nama[50];
        int umur;
        float nilai;
        sscanf(buffer, "%[^,],%d,%f", nama, &umur, &nilai);
        printf("Nama: %s, Umur: %d, Nilai: %.2f\n", nama, umur, nilai);
    }

    fclose(file);
}
void cariMahasiswa() {
    char namaCari[50];
    printf("Masukkan nama yang dicari: ");
    fgets(namaCari, sizeof(namaCari), stdin);
    namaCari[strcspn(namaCari, "\n")] = 0;

    FILE *file = fopen("data_mahasiswa.txt", "r");
    if (file == NULL) {
        printf("Tidak ada data mahasiswa.\n");
        return;
    }

    char buffer[100];
    int ditemukan = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        char nama[50];
        int umur;
        float nilai;
        sscanf(buffer, "%[^,],%d,%f", nama, &umur, &nilai);
        if (strcmp(nama, namaCari) == 0) {
            printf("Mahasiswa ditemukan: Nama: %s, Umur: %d, Nilai: %.2f\n", nama, umur, nilai);
            ditemukan = 1;
            break;
        }
    }

    if (!ditemukan) {
        printf("Mahasiswa dengan nama %s tidak ditemukan.\n", namaCari);
    }

    fclose(file);
}
void urutkanMahasiswa() {
    Mahasiswa mahasiswa[MAX_MAHASISWA];
    int jumlah = bacaData(mahasiswa, MAX_MAHASISWA);

    if (jumlah == 0) {
        printf("Tidak ada data mahasiswa untuk diurutkan.\n");
        return;
    }
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (mahasiswa[j].nilai > mahasiswa[j + 1].nilai) {
                Mahasiswa temp = mahasiswa[j];
                mahasiswa[j] = mahasiswa[j + 1];
                mahasiswa[j + 1] = temp;
            }
        }
    }

    printf("\n=== DATA MAHASISWA (SETELAH DIURUTKAN) ===\n");
    for (int i = 0; i < jumlah; i++) {
        printf("Nama: %s, Umur: %d, Nilai: %.2f\n", mahasiswa[i].nama, mahasiswa[i].umur, mahasiswa[i].nilai);
    }
}
int bacaData(Mahasiswa mahasiswa[], int maxSize) {
    FILE *file = fopen("data_mahasiswa.txt", "r");
    if (file == NULL) {
        return 0;
    }

    int count = 0;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) && count < maxSize) {
        sscanf(buffer, "%[^,],%d,%f", mahasiswa[count].nama, &mahasiswa[count].umur, &mahasiswa[count].nilai);
        count++;
    }

    fclose(file);
    return count;
}
void simpanData(Mahasiswa mahasiswa[], int jumlah) {
    FILE *file = fopen("data_mahasiswa.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        fprintf(file, "%s,%d,%.2f\n", mahasiswa[i].nama, mahasiswa[i].umur, mahasiswa[i].nilai);
    }

    fclose(file);
}
