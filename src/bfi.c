// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"stack.h"

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Not enough arguments. Usage: ./bfi <path-to-bf-file>\n");
		return -1;
	}

	FILE *file;

	if(!(file = fopen(argv[1], "r")))
	{
		printf("Invalid file name: %s\n", argv[1]);
		return -1;
	}

	char character, *instructions = malloc(sizeof(char)), allocatedMemory[30000] = {0}, *memoryPtr = allocatedMemory;
	int instructionsLength = 0;
	int braces;
	stack s;

	while((character = getc(file)) != EOF)
	{
		if(strchr("<>+-.,[]", character))
		{
			instructions[instructionsLength++] = character;
			instructions = realloc(instructions, (instructionsLength + 1) * sizeof(char));
		}
	}

	fclose(file);

	for(int i = 0; i < instructionsLength; ++i)
	{
		switch(instructions[i])
		{
			case 62: ++memoryPtr;             break;
			case 60: --memoryPtr;             break;
			case 43: ++*memoryPtr;            break;
			case 45: --*memoryPtr;            break;
			case 46: putchar(*memoryPtr);     break;
			case 44: *memoryPtr = getchar();  break;
			case 91:
				if(!*memoryPtr)
				{
					braces = 0;
					for(;;)
					{
						++i;
						if(instructions[i] == 91)
						{
							++braces;
						}
						else if(instructions[i] == 93)
						{
							if(braces-- == 0)
							{
								break;
							}
						}
					}
				}
				else
				{
					push(&s, i);
				}
				break;
			case 93:
				if(*memoryPtr)
				{
					i = top(&s);
				}
				else
				{
					pop(&s);
				}
				break;
		}
	}
	freeStack(&s);
	free(instructions);
	return 0;
}