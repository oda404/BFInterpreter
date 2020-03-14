// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#define SUCCESS 0
#define ARG_ERR 1
#define INVALID_FILE 2

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Not enough arguments. Usage: ./bfi <path-to-bf-file>\n");
		return ARG_ERR;
	}

	FILE *file;

	if(!(file = fopen(argv[1], "r")))
	{
		printf("Invalid file path\n");
		return INVALID_FILE;
	}

	char character;

	size_t numberOfValidChars = 0, numberOfLoops = 0;

	while((character = getc(file)) != EOF)
		if(strchr("<>+-.,[]", character))
		{
			if(character == 91)
				++numberOfLoops;
			++numberOfValidChars;
		}

	char instructions[numberOfValidChars + 1], allocatedMemory[30000] = {0}, *memoryPtr = allocatedMemory;
	int whileS[numberOfLoops + 1], whileE[numberOfLoops + 1], it = 0, n = 0;
	memset(whileE, 0, numberOfLoops * sizeof(int));
	memset(whileS, 0, numberOfLoops * sizeof(int));
	numberOfLoops = 0;

	fseek(file, 0, SEEK_SET);

	while((character = getc(file)) != EOF)
		if(strchr("<>+-.,[]", character))
		{
			if(character == 91)
			{
				whileS[numberOfLoops++] = it;
			}
			else if(character == 93)
			{
				int k = numberOfLoops - 1;
				for(; k >= 0; --k)
				{
					if(!whileE[k])
					{
						whileE[k] = it;
						break;
					}
				}
			}
			instructions[it++] = character;
		}

	fclose(file);

	for(it = 0; it < sizeof(instructions); ++it)
	{
		switch(instructions[it])
		{
			case 62: ++memoryPtr;  			  	  break;
			case 60: --memoryPtr;  			  	  break;
			case 43: ++*memoryPtr;    		  	  break;
			case 45: --*memoryPtr; 			  	  break;
			case 46: putchar(*memoryPtr); 	  	  break;
			case 44: *memoryPtr = getchar();  	  break;
			case 91:
				if(!*memoryPtr)
				{
					for(n = 0; n < numberOfLoops; ++n)
					{
						if(it == whileS[n])
						{
							it = whileE[n];
							break;
						}
					}
				}
				break;
			case 93:
				if(*memoryPtr)
				{
					for(n = 0; n < numberOfLoops; ++n)
					{
						if(it == whileE[n])
						{
							it = whileS[n];
							break;
						}
					}
				}
				break;
		}
	}
	return SUCCESS;
}
