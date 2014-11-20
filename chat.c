/*
 * LOYOLA UNIVERSITY CHICAGO
 * COMP 410-001 - OPERATING SYSTEMS - FALL 2014
 *
 * Tiago de Almeida - tdealmeida@luc.edu
 * 1394611
 *
 * Homework #4
 *
 * OSChat - A simple terminal chat implemented using named pipes.
 */

#include <stdlib.h>
#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "almeidamacros.h"

#define USERNAME_LENGTH 100
#define BUFFER_LENGTH 10000

char buffer[BUFFER_LENGTH];
char username[USERNAME_LENGTH];
int npipe, username_len;

void *reading_thread();

int main(){

	char *pipe_address = "/tmp/chat_named_pipe";
	pthread_t thread;
	int bindex;

	// Creating named pipe
	mkfifo(pipe_address, 0666);
	
	// Opening named pipe
	npipe = open(pipe_address, O_RDWR);
	if(npipe < 0){
		perror("Error opening named pipe");
		exit(EXIT_FAILURE);
	}

	// Initializing
	memset(username, 0, USERNAME_LENGTH);
	memset(buffer, 0, BUFFER_LENGTH);
	
	// Welcome messages
	verbose("Welcome to OSChat");
	printf(" - Enter your username: ");
	scanf("%s", username);
	getchar();
	username_len = strlen(username);
	sprintf(buffer, " - %s: ", username);
	verbose("You have entered OSChat as %s. Insert your message and press ENTER to send.", username);
	
	// Creating reading thread
	if(pthread_create(&thread, NULL, reading_thread, NULL) != 0){
		perror("Error creating thread");
		exit(EXIT_FAILURE);
	}
	
	// Reading message from standard input
	while(1){
		printf(" - %s: ", username);
		bindex = username_len + 5;
		while(1){
			buffer[bindex] = getchar();
			fflush(stdin); bindex++;
			if(buffer[bindex-1] == '\n')
				break;
		}
		
		// Exit command
		if(!memcmp(&buffer[username_len+5], "exit", 4))
			break;
		
		// Sending through pipe
		write(npipe, buffer, bindex);
	}
	
	if(pthread_cancel(thread) != 0)
		error("Error canceling thread.");
	if(close(npipe) < 0)
		perror("Error closing named pipe");
}

// Thread for reading input from named pipe
void *reading_thread(){

	char read_buf[BUFFER_LENGTH];
	int bytes_read;

	// Reading from pipe
	while(1){
		memset(read_buf, 0, BUFFER_LENGTH);
		bytes_read = read(npipe, read_buf, BUFFER_LENGTH);

		// If data was from itself, send it back
		if(!memcmp(read_buf, buffer, username_len + 3))
			write(npipe, read_buf, bytes_read);
		// Else print it out
		else{
			printf("\r%s", read_buf);
			printf(" - %s: ", username);
			fflush(stdout);
		}
		usleep(10000);
	}
}
