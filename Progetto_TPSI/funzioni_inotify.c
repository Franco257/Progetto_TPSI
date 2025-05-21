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
#define MAX_FILENAME_LENGTH 100 //lunghezza per i nomi dei file
#define BUFFER_SIZE 1024   //dimensione del buffer per leggere i file

// Dimensione del buffer per gli eventi inotify 
#define INOTIFY_EVENT_BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))


// Funzione per monitorare modifiche di una directory usando inotify
void monitor_changes() {
    char dirname[MAX_PATH_LENGTH];
    printf("Inserisci il nome della directory da monitorare: ");
    scanf("%s", dirname);
    getchar(); // Consuma il newline

    int fd; // File descriptor per inotify
    int wd; // Watch descriptor per la directory monitorata
    char buffer[INOTIFY_EVENT_BUF_LEN];
    ssize_t length;
    struct inotify_event *event;

    // Inizializza inotify
    fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
        return;
    }

    // Aggiunge la directory alla lista di monitoraggio
    wd = inotify_add_watch(fd, dirname, IN_CREATE | IN_DELETE | IN_MODIFY | IN_MOVED_FROM | IN_MOVED_TO | IN_ISDIR);
    
    if (wd < 0) {
        perror("inotify_add_watch");
        close(fd);
        return;
    }

    printf("Monitorando la directory '%s'. Premi Ctrl+C per fermare.\n", dirname);

    while (1) {
        length = read(fd, buffer, INOTIFY_EVENT_BUF_LEN);
        if (length < 0) {
            if (errno == EINTR) { // Interrotto da un segnale (es. Ctrl+C)
                printf("\nMonitoraggio interrotto.\n");
                break;
            }
            perror("read");
            break;
        }

        // Processa gli eventi
        for (char *ptr = buffer; ptr < buffer + length; ptr += sizeof(struct inotify_event) + event->len) {
            event = (struct inotify_event *)ptr;

            printf("Evento su: %s", (event->len > 0) ? event->name : "");
            if (event->mask & IN_CREATE) {
                printf(" (CREATO)\n");
            }
            if (event->mask & IN_DELETE) {
                printf(" (ELIMINATO)\n");
            }
            if (event->mask & IN_MODIFY) {
                printf(" (MODIFICATO)\n");
            }
            if (event->mask & IN_MOVED_FROM) {
                printf(" (SPOSTATO DA)\n");
            }
            if (event->mask & IN_MOVED_TO) {
                printf(" (SPOSTATO A)\n");
            }
            if (event->mask & IN_ISDIR) {
                printf(" (DIRETTORIO)\n");
            }
        }
    }

    // Rimuove il monitoraggio e chiude il file descriptor
    inotify_rm_watch(fd, wd);
    close(fd);
}