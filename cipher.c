/*
 * CIPHER.C
 * David Stafford
 *
 * Slightly modified and compiled for OS/2 by David Eagen
 * using Borland C++ for OS/2 (July 11, 1993)
 */

#include<stdio.h>
#include<stdlib.h>

#define MULTIPLIER 0x015A4E35L
#define INCREMENT 1

long RandomSeed;

int GetRandomNumber(int Range)
{
	RandomSeed = MULTIPLIER*RandomSeed+INCREMENT;
	return (RandomSeed % Range);
}

/*
 * Does the actual enciphering.
 *
 * In:InFile Input file
 *    OutFile Output File
 *
 * Out: Nothing
 */

void Cipher(FILE*InFile, FILE*OutFile)
{
	int Ch;

	while((Ch=getc(InFile))!=EOF)
	{
		fputc(Ch^GetRandomNumber(256), OutFile);
	}
}

/*
 * Opens the input and output files.
 *
 * In:Key  the key used to encrypt/decrypt the file
 *    InFileName Input file name
 *    OutFileName Output file name
 *
 * Out: Nothing
 */

void Supervisor(long Key, char *InFileName, char *OutFileName)
{
	FILE *InFile, *OutFile;

	if((InFile = fopen(InFileName, "rb"))!=NULL)
	{
		if((OutFile = fopen(OutFileName, "wb"))!=NULL)
		{
			RandomSeed = Key;

			Cipher(InFile, OutFile);

			fclose(OutFile);
		}
		else
		{
			printf("Can't open output file %s\n", OutFileName);
		}
		fclose(InFile);
	}
	else
	{
		printf("Can't open input file %s\n", InFileName);
	}
}

/*
 * Entry point. Gets the command-line args.
 * Provides usage information.
 *
 * IN:Argc Count of command line arguments
 *    Argv Strings(commands)
 *
 * Out: Nothing
 */

void main(int Argc, char *Argv[])
{
	if(Argc==4)
	{
		Supervisor(atol(Argv[1]), Argv[2], Argv[3]);
	}
	else
	{
		puts("Cipher - File encryption/decryption\n");
		puts("Usage: cipher_key input_file output_file\n");
		puts("       cipher_key is a string of integers and/or characters");
		puts("       input_file & output_file are the file names\n");
		puts("For example: \"CIPHER 5275 README.TXT README.CPH\"");
		puts("    This would encrypt the file README.TXT and store it");
		puts("    in README.CPH. You must use the key 5275 to decrypt it.");
		puts("To decrypt a file, simply reverse the file names....");
		puts("             \"CIPHER 5275 README.CPH README.TXT\"");
	}
}

