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
