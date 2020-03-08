#include "library.h"
#include "functions.h"
char home[1500];  
char prompt[1500];
char pwd[1500]; 
char* commands[26];
int drama_Check(char **args){
	int flago=0, redirect=0, argument = 0, zero = 0; // Number of Arguments

	while (args[argument] != NULL){
		if (strcmp(args[argument], "<")==zero || strcmp(args[argument], ">")== zero || strcmp(args[argument], ">>")== zero ){
			redirect = argument;
		}
		argument = argument + 1;
	}

	if (strcmp(args[argument - 1], "&")== zero){
		flago = 1;
		argument = argument - 1;
		args[argument] = NULL; 
	}

	if (argument == zero){
		printf("\n");
		return 1;
	}

	return drama_Execute(argument, args, flago);

}
