void hapus_barang() {
    printf("-----HAPUS BARANG-----\n");
    char nama_barang[50];
    int found = 0;

    printf("Nama barang: ");
    getchar();
    fgets(nama_barang, sizeof(nama_barang), stdin);
    nama_barang[strcspn(nama_barang, "\n")] ='\0';
    
    FILE *file = fopen("barang_tersedia.txt", "r");
    FILE *temp_file = fopen("temp_barang_tersedia.txt", "w");
    

    struct Barang barang;

    while (fscanf(file, "%s %f %d", barang.nama, &barang.harga, &barang.stok) != EOF) {
        if (strcmp(nama_barang, barang.nama) == 0) {
            found = 1;
            printf("Berhasil!! \"%s\" telah dihapus\n", nama_barang);
        } else {
            fprintf(temp_file, "%s %.2f %d\n", barang.nama, barang.harga, barang.stok);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove("barang_tersedia.txt");
    rename("temp_barang_tersedia.txt", "barang_tersedia.txt");

    if (!found)
        printf("Barang tidak ditemukan\n");
}