// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	if(argc < 2){ // if there are no command line arguments for the brainfuck file then return
		printf("Not enough arguments. Usage: ./bfi <path-to-bf-file>\n");
		return 1;
	}

	FILE *file = fopen(argv[1], "r");

	char *allowedChars = malloc(8 * sizeof(char)); 
	allowedChars[0] = '<';
	allowedChars[1] = '>';
	allowedChars[2] = '+';
	allowedChars[3] = '-';
	allowedChars[4] = '.';
	allowedChars[5] = ',';
	allowedChars[6] = '[';
	allowedChars[7] = ']';

	int *character = malloc(sizeof(int));

	size_t numberOfValidChars = 0;

	while((*character = getc(file)) != EOF)
		if(strchr(allowedChars, *character)) //find how many characters are valid
			++numberOfValidChars;

	char instructions[numberOfValidChars + 1];

	fseek(file, 0, SEEK_SET); // 'reset' the file back to the beginning

	int it = 0;

	while((*character = getc(file)) != EOF)
		if(strchr(allowedChars, *character)){ // only add the valid characters to the instructions array
			instructions[it] = *character;
			++it;
		}

	fclose(file);

	free(character); free(allowedChars);

	char allocatedMemory[30000] = {0};
	char *memoryPtr = allocatedMemory;

	it = 0;

	for(; it < sizeof(instructions); ++it){
		switch(instructions[it]){
			case 62:
				++memoryPtr;
				break;
			case 60:
				--memoryPtr;
				break;
			case 43:
				++*memoryPtr;
				break;
			case 45:
				--*memoryPtr;
				break;
			case 46:
				putchar(*memoryPtr);
				break;
			case 44:
				*memoryPtr = getchar();
				break;
			case 91:
				;
				char *ptrToCheck = memoryPtr;
				int whileIt = it;
				int whileStartIt = it;
				while(*ptrToCheck){
					if(instructions[whileIt] == 93){
						it = whileIt;
						whileIt = whileStartIt;
					}
					else{
						switch(instructions[whileIt]){
						case 62:
							++memoryPtr;
							break;
						case 60:
							--memoryPtr;
							break;
						case 43:
							++*memoryPtr;
							break;
						case 45:
							--*memoryPtr;
							break;
						}
						++whileIt;
					}
				}
				break;
		}
	}

	return 0;
}
