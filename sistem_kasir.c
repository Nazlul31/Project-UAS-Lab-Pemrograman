#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Struktur data untuk menyimpan informasi barang
struct Barang {
    char nama[50];
    float harga;
    int stok;
};
// Login
bool login() {
    char username[20];
    char password[20];
    char input_username[20];
    char input_password[20];
    
    // membuka file untuk membaca user dan pw
    FILE *file = fopen("login.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return false;
    }

    // membaca username dan password
    fscanf(file, "%s", username);
    fscanf(file, "%s", password);

    // tutup file
    fclose(file);

    // meminta input user dan password dari terminal
    printf("Username: ");
    scanf("%s", input_username);

    printf("Password: ");
    scanf("%s", input_password);

    // memastikan user dan password sesuai menggunakan if else
    if (strcmp(username, input_username) == 0 && strcmp(password, input_password) == 0) {
        return true;
    } else {
        printf("Username atau Password salah, Coba lagi!\n");
        return false;
    }
}
// Fungsi untuk menambahkan barang ke toko
void tambah_barang() {
	printf("-----TAMBAH BARANG-----\n");
    FILE *file = fopen("barang_tersedia.txt", "r");
    struct Barang barang;
    char nama_barang_baru[50];
    int found = 0;

    printf("Masukkan nama barang	: ");
    getchar();
    fgets(nama_barang_baru, sizeof(nama_barang_baru), stdin);
    nama_barang_baru[strcspn(nama_barang_baru, "\n")] = '\0';
    // scanf("%s", nama_barang_baru);

    // Memeriksa apakah nama barang sudah ada dalam daftar
    while (fscanf(file, "%s %f %d", barang.nama, &barang.harga, &barang.stok) != EOF) {
        if (strcmp(nama_barang_baru, barang.nama) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);

    // Jika nama barang sudah ada, beri pesan kesalahan
    if (found) {
        printf("Barang sudah terdaftar.\n");
        return;
    }

    // Jika nama barang belum ada, lanjutkan proses penambahan barang
    file = fopen("barang_tersedia.txt", "a");

    printf("Masukkan harga barang	: ");
    scanf("%f", &barang.harga);
    printf("Masukkan stok barang	: ");
    scanf("%d", &barang.stok);

    fprintf(file, "%s %.2f %d\n", nama_barang_baru, barang.harga, barang.stok);
    fclose(file);

    printf("Berhasil\n");
}
// Fungsi untuk mengurangi stok barang
void kurangi_stok() {
	printf("-----KURANGI STOK-----\n");
    char nama_barang[50];
    int jumlah;
    int found = 0;

    printf("Nama barang	: ");
    scanf("%s", nama_barang);
    printf("Jumlah		: ");
    scanf("%d", &jumlah);

    FILE *file = fopen("barang_tersedia.txt", "r");
    FILE *temp_file = fopen("temp_barang_tersedia.txt", "w");

    struct Barang barang;

    while (fscanf(file, "%s %f %d", barang.nama, &barang.harga, &barang.stok) != EOF) {
        if (strcmp(nama_barang, barang.nama) == 0) {
            found = 1;
            if (barang.stok >= jumlah) {
                barang.stok -= jumlah;
            } else {
                printf("Stok barang tidak mencukupi.\n");
                barang.stok = 0;
            }
        }
        fprintf(temp_file, "%s %.2f %d\n", barang.nama, barang.harga, barang.stok);
    }

    fclose(file);
    fclose(temp_file);

    remove("barang_tersedia.txt");
    rename("temp_barang_tersedia.txt", "barang_tersedia.txt");

    if (found)
        printf("Stok barang berhasil dikurangi.\n");
    else
        printf("Barang tidak ditemukan.\n");
}

// Fungsi untuk menambah stok barang
void tambah_stok() {
	printf("-----TAMBAH STOK-----\n");
    char nama_barang[50];
    int jumlah;
    int found = 0;

    printf("Nama barang		: ");
    scanf("%s", nama_barang);

    printf("Jumlah			: ");
    scanf("%d", &jumlah);

    FILE *file = fopen("barang_tersedia.txt", "r");
    FILE *temp_file = fopen("temp_barang_tersedia.txt", "w");

    struct Barang barang;

    while (fscanf(file, "%s %f %d", barang.nama, &barang.harga, &barang.stok) != EOF) {
        if (strcmp(nama_barang, barang.nama) == 0) {
            found = 1;
            barang.stok += jumlah;
        }
        fprintf(temp_file, "%s %.2f %d\n", barang.nama, barang.harga, barang.stok);
    }

    fclose(file);
    fclose(temp_file);

    remove("barang_tersedia.txt");
    rename("temp_barang_tersedia.txt", "barang_tersedia.txt");

    if (found)
        printf("Berhasil\n");
    else
        printf("Barang tidak ditemukan.\n");
}

// Fungsi untuk melihat daftar barang yang tersedia
void lihat_daftar_barang() {
    FILE *file = fopen("barang_tersedia.txt", "r");
    struct Barang barang;

    printf("Daftar Barang:\n");
    printf("|Nama\t\t\t|\tHarga\t\t|\tStok\t|\n");
    while (fscanf(file, "%s %f %d", barang.nama, &barang.harga, &barang.stok) != EOF) {
        printf("|%s    \t\t|\t%.2f \t|\t%d\t|\n", barang.nama, barang.harga, barang.stok);
    }
    fclose(file);
}

// Fungsi untuk melakukan pembayaran
void pembayaran() {
    FILE *file = fopen("barang_tersedia.txt", "r");
    FILE *temp_file = fopen("temp_barang_tersedia.txt", "w");
    struct Barang barang;
    float total_pembelian = 0;
    float bayar;
    char nama_barang[50];
    int jumlah_beli;
    int found = 0;

    printf("Nama barang	: ");
    scanf("%s", nama_barang);
    printf("Jumlah		: ");
    scanf("%d", &jumlah_beli);

    while (fscanf(file, "%s %f %d", barang.nama, &barang.harga, &barang.stok) != EOF) {
        if (strcmp(nama_barang, barang.nama) == 0) {
            found = 1;
            if (barang.stok >= jumlah_beli) {
                barang.stok -= jumlah_beli;
                total_pembelian = barang.harga * jumlah_beli;
            } else {
                printf("Stok barang tidak mencukupi.\n");
            }
        }
        fprintf(temp_file, "%s %.2f %d\n", barang.nama, barang.harga, barang.stok);
    }

    fclose(file);
    fclose(temp_file);

    remove("barang_tersedia.txt");
    rename("temp_barang_tersedia.txt", "barang_tersedia.txt");

    if (found) {
        printf("Amount		: %.2f\n", total_pembelian);
        printf("Tunai		: ");
        scanf("%f", &bayar);

        if (bayar >= total_pembelian) {
            float kembalian = bayar - total_pembelian;
            printf("Kembalian: %.2f\n", kembalian);
        } else {
            printf("Jumlah uang kurang.\n");
        }
    } else {
        printf("Barang tidak tersedia.\n");
    }
}

   // Fungsi untuk menghapus barang dari daftar
void hapus_barang() {
    printf("-----HAPUS BARANG-----\n");
    char nama_barang[50];
    int found = 0;

    printf("Nama barang: ");
    getchar();
    fgets(nama_barang, sizeof(nama_barang), stdin);
    nama_barang[strcspn(nama_barang, "\n")] ='\0';
    // scanf("%s", nama_barang);

    FILE *file = fopen("barang_tersedia.txt", "r");
    FILE *temp_file = fopen("temp_barang_tersedia.txt", "w");
    

    struct Barang barang;

    while (fscanf(file, "%s %f %d", barang.nama, &barang.harga, &barang.stok) != EOF) {
        if (strcmp(nama_barang, barang.nama) == 0) {
            found = 1;
            printf("Barang \"%s\" telah dihapus.\n", nama_barang);
        } else {
            fprintf(temp_file, "%s %.2f %d\n", barang.nama, barang.harga, barang.stok);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove("barang_tersedia.txt");
    rename("temp_barang_tersedia.txt", "barang_tersedia.txt");

    if (!found)
        printf("Barang tidak ditemukan.\n");
}
   
int main() {
	int login_berhasil = false; // Variabel untuk menandakan apakah login berhasil
    
    do {
        if (login()) {
            login_berhasil = true;
        }
    } while (!login_berhasil); // Melakukan loop selama login belum berhasil
    
	int pilihan;

    do {
		printf("\n\n------------------------");
        printf("\n	  MENU\n");
		printf("------------------------\n");
        printf("|1. Tambah Barang	|\n");
        printf("|2. Kurangi Stok Barang	|\n");
		printf("|3. Tambah Stok Barang	|\n");
        printf("|4. Lihat Daftar Barang	|\n");
        printf("|5. Pembayaran		|\n");
        printf("|6. Hapus Barang	|\n");
        printf("|7. Keluar		|\n");
        printf("------------------------\n");
        printf("Pilihan MENU: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambah_barang();
                break;
            case 2:
                kurangi_stok();
                break;
			case 3:
				tambah_stok();
				break;
            case 4:
                lihat_daftar_barang();
                break;
            case 5:
                pembayaran();
                break;
            case 6:
                hapus_barang();
                break;
			case 7:
				break;
            default:
                printf("Silakan coba lagi.\n");
                break;
        }
    } while (pilihan != 7);

    return 0;
}
