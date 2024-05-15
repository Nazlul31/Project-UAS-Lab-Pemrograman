int login() {
    char username[] = "kelompok2";
    char password[] = "informatika";
    char input_username[20];
    char input_password[20];
    
    printf("Username	: ");
    scanf("%s", input_username);
    
    printf("Password	: ");
    scanf("%s", input_password);
    
    
    if (strcmp(username, input_username) == 0 && strcmp(password, input_password) == 0) {
        return true;
    } else {
        printf("Username atau Password salah, Coba lagi!\n");
        return false;
    }
}
