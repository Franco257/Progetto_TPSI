//librerie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/inotify.h> 
#include <limits.h>  

#define MAX_PATH_LENGTH 256   //lunghezza per i pecorsi dei file 
#define MAX_FILENAME_LENGTH 100    //lunghezza per i nomi dei file
#define BUFFER_SIZE 1024    //dimensione del buffer per leggere i file

// Dimensione del buffer per gli eventi inotify
#define INOTIFY_EVENT_BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))


// Funzione per listare il contenuto della directory
void list_directory(const char *path) {
    DIR *d;
    struct dirent *dir;
    struct stat file_stat;
    char full_path[MAX_PATH_LENGTH];

    d = opendir(path);
    if (d) {
        printf("Contenuto di: %s\n", path);
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                // Costruisci il percorso completo per usare stat()
                snprintf(full_path, sizeof(full_path), "%s/%s", path, dir->d_name);
                if (stat(full_path, &file_stat) == 0) {
                    if (S_ISDIR(file_stat.st_mode)) {
                        printf("  %s/ (Directory)\n", dir->d_name);
                    } else {
                        printf("  %s\n", dir->d_name);
                    }
                } else {
                    perror("Errore in stat");
                    printf("  %s\n", dir->d_name); // Mostra comunque il nome
                }
            }
        }
        closedir(d);
    } else {
        perror("Impossibile aprire la directory");
    }
}

// Funzione per cambiare directory
void change_directory() {
    char dirname[MAX_FILENAME_LENGTH];
    printf("Inserisci il nome della directory (o '..' per risalire): ");
    scanf("%s", dirname);
    getchar(); // Consuma il newline

    if (chdir(dirname) == 0) {
        char current_path[MAX_PATH_LENGTH];
        if (getcwd(current_path, sizeof(current_path)) != NULL) {
            printf("Directory cambiata con successo a: %s\n", current_path);
        }
    } else {
        perror("Errore nel cambiare directory");
    }
}

// Funzione per creare una directory
void create_directory() {
    char dirname[MAX_FILENAME_LENGTH];
    printf("Inserisci il nome della directory da creare: ");
    scanf("%s", dirname);
    getchar(); // Consuma il newline

    if (mkdir(dirname, 0777) == 0) {
        printf("Directory '%s' creata con successo.\n", dirname);
    } else {
        perror("Errore nella creazione della directory");
    }
}