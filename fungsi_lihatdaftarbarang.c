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