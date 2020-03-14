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

	char character, *instructions = malloc(sizeof(char)), allocatedMemory[30000] = {0}, *memoryPtr = allocatedMemory;
	int index = 0, loopsIndex = 0, *whileS = malloc(sizeof(int)), *whileE = malloc(sizeof(int)), it = 0, n = 0;

	while((character = getc(file)) != EOF)
		if(strchr("<>+-.,[]", character))
		{
			if(character == 91)
			{
				whileE[loopsIndex] = 0;
				whileS[loopsIndex++] = index;
				whileS = realloc(whileS, (loopsIndex + 1) * sizeof(int));
				whileE = realloc(whileE, (loopsIndex + 1) * sizeof(int));
			}
			else if(character == 93)
			{
				int k = loopsIndex - 1;
				for(; k >= 0; --k)
				{
					if(!whileE[k])
					{
						whileE[k] = index;
						break;
					}
				}
			}
			instructions[index++] = character;
			instructions = realloc(instructions, (index + 1) * sizeof(char));
		}

	fclose(file);

	for(it = 0; it < index; ++it)
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
					for(n = 0; n < loopsIndex; ++n)
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
					for(n = 0; n < loopsIndex; ++n)
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
	free(instructions); free(whileS); free(whileE);
	return SUCCESS;
}