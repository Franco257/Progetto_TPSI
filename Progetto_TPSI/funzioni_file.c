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

#define MAX_PATH_LENGTH 256  //lunghezza per i pecorsi dei file
#define MAX_FILENAME_LENGTH 100   //lunghezza per i nomi dei file
#define BUFFER_SIZE 1024   //dimensione del buffer per leggere i file

// Dimensione del buffer per gli eventi inotify
#define INOTIFY_EVENT_BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

// Funzione per creare un file
void create_file() {
    char filename[MAX_FILENAME_LENGTH];
    printf("Inserisci il nome del file da creare: ");
    scanf("%s", filename);
    getchar(); // Consuma il newline

    FILE *fp = fopen(filename, "w");
    if (fp != NULL) {
        printf("File '%s' creato con successo.\n", filename);
        fclose(fp);
    } else {
        perror("Errore nella creazione del file");
    }
}

// Funzione per scrivere/modificare un file
void write_file() {
    char filename[MAX_FILENAME_LENGTH];
    char content[BUFFER_SIZE];
    printf("Inserisci il nome del file da scrivere/modificare: ");
    scanf("%s", filename);
    getchar(); // Consuma il newline

    printf("Inserisci il contenuto da scrivere nel file (CTRL+D per terminare):\n");

    FILE *fp = fopen(filename, "w");
    if (fp != NULL) {
        while (fgets(content, sizeof(content), stdin) != NULL) {
            fputs(content, fp);
        }
        printf("Contenuto scritto nel file '%s' con successo.\n", filename);
        fclose(fp);
    } else {
        perror("Errore nell'apertura del file per la scrittura");
    }
}

// Funzione per visualizzare il contenuto di un file
void view_file() {
    char filename[MAX_FILENAME_LENGTH];
    char buffer[BUFFER_SIZE];
    printf("Inserisci il nome del file da visualizzare: ");
    scanf("%s", filename);
    getchar(); // Consuma il newline

    FILE *fp = fopen(filename, "r");
    if (fp != NULL) {
        printf("\n--- Contenuto di '%s' ---\n", filename);
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }
        printf("--------------------------\n");
        fclose(fp);
    } else {
        perror("Errore nell'apertura del file per la lettura");
    }
}

