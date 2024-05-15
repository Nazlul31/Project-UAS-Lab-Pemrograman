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