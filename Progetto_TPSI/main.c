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

//librerie create
#include "funzioni_directory_file.h"
#include "funzioni_directory.h"
#include "funzioni_file.h"
#include "funzioni_inotify.h"

#define MAX_PATH_LENGTH 256  //lunghezza per i pecorsi dei file
#define MAX_FILENAME_LENGTH 100  //lunghezza per i nomi dei file
#define BUFFER_SIZE 1024  //dimensione del buffer per leggere i file

// Dimensione del buffer per gli eventi inotify
#define INOTIFY_EVENT_BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))


// Funzione per stampare il menu
void print_menu() {
    printf("\n--- Gestore File ---\n");
    printf("1.  Lista Contenuto \n");
    printf("2.  Cambia Directory \n");
    printf("3.  Crea File \n");
    printf("4.  Scrivi/Modifica File \n");
    printf("5.  Visualizza Contenuto File \n");
    printf("6.  Elimina File/Directory Vuota \n");
    printf("7.  Crea Directory \n");
    printf("8.  Informazioni File/Directory \n");
    printf("9.  Monitora Modifiche \n"); 
    printf("10. Pulisci Schermo\n");
    printf("0.  Esci\n");
    printf("-----------------------------\n");
}

// Funzione per pulire lo schermo
void clear_screen() {
    printf("\033[2J\033[H"); // Sequenza di escape ANSI per pulire lo schermo e muovere il cursore all'inizio
}

int main() {
    int choice; //scelta menu

    //buffer per memorizare il percorso della directory iniziale di lavoro 
    char initial_path[MAX_PATH_LENGTH]; 

    //ottine la directory corrente 
    if (getcwd(initial_path, sizeof(initial_path)) == NULL) {
        perror("Errore nell'ottenere la directory iniziale");
        return 1; //errore
    }

    //stampa la directory iniziale 
    printf("Programma avviato nella directory: %s\n", initial_path);

    do {
        print_menu(); //stampa menu
        printf("Scegli un'opzione: "); //aquisizione scelta
        if (scanf("%d", &choice) != 1) { //controlla se la scelta va bene
            printf("Input non valido. Per favore, inserisci un numero.\n");
            // Pulisce il buffer di input da eventuali caratteri non validi
            while (getchar() != '\n'); //pulisce il buffer d'input
            continue; //ristampa il menu se l'input è sbagliato
        }
        // Nota: non è necessario un getchar() qui perché le successive funzioni
        // che leggono stringhe includono già il loro getchar() o usano fgets.

        switch (choice) {
            case 1:
                list_directory("."); //lista contenuto directory
                break;
            case 2:
                change_directory(); //cambia la directory
                break;
            case 3:
                create_file(); //crea un file vuoto
                break;
            case 4:
                write_file(); //scrive o modifica il contenuto di un file
                break;
            case 5:
                view_file(); //visualizza il contenuto di un file
                break;
            case 6:
                delete_item(); //elimine file o una directory (vuota)
                break;
            case 7:
                create_directory(); //crea una directory
                break;
            case 8:
                show_file_info(); //informazioni file o directory
                break;
            case 9:
                monitor_changes(); //modifiche 
                break;
            case 10:
                clear_screen(); //pulisce lo schermo
                break;
            case 0:
                printf("Uscita dal programma.\n"); //uscire dal programa
                break;
            default:
                printf("Opzione non valida. Riprova.\n"); //inserimento non valido
                break;
        }
    } while (choice != 0); //il ciclo si ripette finche l'utente non digita 0

    return 0;
}