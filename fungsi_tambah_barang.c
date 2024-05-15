void tambah_barang() {
	printf("-----TAMBAH BARANG-----\n");
    FILE *file = fopen("daftar_barang.txt", "r");
    struct Barang barang;
    char nama_barang_baru[50];
    int found = 0;

    printf("Masukkan nama barang	: ");
    scanf("%s", nama_barang_baru);

// Memeriksa apakah nama barang sudah ada dalam daftar
    while (fscanf(file, "%s %f %d", barang.nama, &barang.harga, &barang.stok) != EOF) {
        if (strcmp(nama_barang_baru, barang.nama) == 0) {
            found = 1;
            break;
        }
    }
    fclose(file);

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
