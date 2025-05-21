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
#define MAX_FILENAME_LENGTH 100   //lunghezza per i nomi dei file
#define BUFFER_SIZE 1024   //dimensione del buffer per leggere i file

// Dimensione del buffer per gli eventi inotify
#define INOTIFY_EVENT_BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))



// Funzione per eliminare un file o una directory vuota
void delete_item() {
    char item_name[MAX_FILENAME_LENGTH];
    printf("Inserisci il nome del file o della directory vuota da eliminare: ");
    scanf("%s", item_name);
    getchar(); // Consuma il newline

    struct stat st;
    if (stat(item_name, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            if (rmdir(item_name) == 0) {
                printf("Directory '%s' eliminata con successo.\n", item_name);
            } else {
                perror("Errore nell'eliminazione della directory (assicurati che sia vuota)");
            }
        } else if (S_ISREG(st.st_mode)) {
            if (unlink(item_name) == 0) {
                printf("File '%s' eliminato con successo.\n", item_name);
            } else {
                perror("Errore nell'eliminazione del file");
            }
        } else {
            printf("L'elemento '%s' non è un file o una directory eliminabile.\n", item_name);
        }
    } else {
        perror("L'elemento non esiste");
    }
}

// Funzione per visualizzare informazioni su file/directory
void show_file_info() {
    char item_name[MAX_FILENAME_LENGTH];
    printf("Inserisci il nome del file o della directory: ");
    scanf("%s", item_name);
    getchar(); // Consuma il newline

    struct stat file_stat;
    if (stat(item_name, &file_stat) == 0) {
        printf("Informazioni su '%s':\n", item_name);
        printf("  Dimensione: %ld bytes\n", file_stat.st_size);
        printf("  Tipo: ");
        if (S_ISREG(file_stat.st_mode)) {
            printf("File regolare\n");
        } else if (S_ISDIR(file_stat.st_mode)) {
            printf("Directory\n");
        } else {
            printf("Altro\n");
        }
        printf("  Permessi: %o\n", file_stat.st_mode & 0777); // Solo i permessi
        printf("  Ultimo accesso: %s", ctime(&file_stat.st_atime));
        printf("  Ultima modifica: %s", ctime(&file_stat.st_mtime));
        printf("  Ultimo cambio stato: %s", ctime(&file_stat.st_ctime));
    } else {
        perror("Errore nell'ottenere informazioni sul file/directory");
    }
}