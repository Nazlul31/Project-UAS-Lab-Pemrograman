void tambah_barang() {
	printf("-----TAMBAH BARANG-----\n");
    FILE *file = fopen("daftar_barang.txt", "r");
    struct Barang barang;
    char nama_barang_baru[50];
    int found = 0;

    printf("Masukkan nama barang	: ");
    scanf("%s", nama_barang_baru);
