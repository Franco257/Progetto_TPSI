all: main

clean: main main.o funzioni_directory_file.o funzioni_directory.o funzioni_file.o funzioni_inotify.o 
		rm -rf main main.o funzioni_directory_file.o funzioni_directory.o funzioni_file.o funzioni_inotify.o 

main: main.o funzioni_directory_file.o funzioni_directory.o funzioni_file.o funzioni_inotify.o 
		gcc -o main main.o funzioni_directory_file.o funzioni_directory.o funzioni_file.o funzioni_inotify.o

main.o: main.c funzioni_directory_file.h funzioni_directory.h funzioni_file.h funzioni_inotify.h		
		gcc -c -o main.o main.c 

funzioni_directory_file.o: funzioni_directory_file.c funzioni_directory_file.h
		gcc -c -o funzioni_directory_file.o funzioni_directory_file.c 

funzioni_directory.o: funzioni_directory.c funzioni_directory.h
		gcc -c -o funzioni_directory.o funzioni_directory.c 

funzioni_file.o: funzioni_file.c funzioni_file.h
		gcc -c -o funzioni_file.o funzioni_file.c 

funzioni_inotify.o: funzioni_inotify.c funzioni_inotify.h
		gcc -c -o funzioni_inotify.o funzioni_inotify.c 

