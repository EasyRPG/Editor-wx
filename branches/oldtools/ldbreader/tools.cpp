/* tools.cpp, miscellaneous shared routines.
   Copyright (C) 2007 EasyRPG Project <http://easyrpg.sourceforge.net/>.
   se encarga de la laectura de enteros con comprecion Ber
   La carga y creacin de superficies

  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tools.h"

unsigned long ReadCompressedInteger(FILE * FileStream)
{
	unsigned long Value = 0;
	unsigned char Temporal = 0;
	
	// int i = 0;
	do
	{		
		if (feof(FileStream))
		{
		  // printf("Error: ReadCompressedInteger: Unexpected end of file\n");
		   return Value;
		} 
		
		Value <<= 7;
		
		// Get byte's value
		fread(&Temporal, sizeof(char), 1, FileStream);
		
		// Check if it's a BER integer
		Value |= Temporal&0x7F;
		
	} while (Temporal&0x80);
	
	return Value;
}

std::string ReadString(FILE * FileStream)
{
	unsigned char Length;
	char		* Characters;
	std::string		String;
	
	// Read string lenght's
	fread(&Length, sizeof(char), 1, FileStream);
	if (Length == 0) return std::string("");
	
	// Allocate string buffer
	Characters = new char[Length+1];
	memset(Characters, 0, Length+1);
	fread(Characters, sizeof(char), Length, FileStream);
// we create an array of cell_count cells
//my_type my_array[cell_count];
// and we explicitly fill cell_count cells with a copy of
// a default-constructed object.
//std::fill(my_array, my_array + cell_count, my_type());	
	// Get string and free characters buffer
	String = std::string(Characters);
	delete Characters;
	
	return String;
}

std::string ReadString(FILE * FileStream, unsigned char Length)
{
	char		* Characters;
	std::string		String;
	
	// Allocate string buffer
	Characters = new char[Length+1];
	memset(Characters, 0, Length+1);
	fread(Characters, sizeof(char), Length, FileStream);
	
	// Get string and free characters buffer
	String = std::string(Characters);
	delete Characters;
	
	return String;
}

