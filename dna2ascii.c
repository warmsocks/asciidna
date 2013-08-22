// Encoding DNA to/from ASCII
// Per http://www.aleph.se/Trans/Individual/Body/ascii.html (Anders Sandberg)
// Copyright 2013 Shaun Case
//
// This work is licensed under GPL v3.  See file LICENSE for license text.
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 
// 
// First draft/proof of concept.  TODO:
//
// + Debug statements removal
// + Split into library + app files
// + Generalize to handle arbitrary length input.  Currently hardcoded for 8 char Ingress activation codes (original use)
// + Possibly optimize for speed
// + Display alerts if introns or exons are coded
// + Make happy with gcc (remove any lurking C++-isms)
// + Port to JavaScript

#include <stdio.h>
#include <string.h>

typedef struct _encoding { char c; char stringbits[3]; int bits; };

_encoding encoding[4]=
{
	{ 'A', "00", 0},
	{ 'G', "01", 1},
	{ 'C', "10", 2}, 
	{ 'T', "11", 3}
};

int ascii2dna(char activationCode[8])
{

	for (int i=0; activationCode[i]; i++)
	{
		char c = activationCode[i];
		printf("\n%c\n", c);
		for (int j = 0; j < 4; j++)
		{
			int bits = (c & 0xc0) >> 6;
			printf("%s", encoding[bits].stringbits);
			c<<=2;
		}
	}
	printf ("\n");

	for (int i=0; activationCode[i]; i++)
	{
		char c = activationCode[i];
		for (int j = 0; j < 4; j++)
		{
			int bits = (c & 0xc0) >> 6;
			printf("%c", encoding[bits].c);
			c<<=2;
		}
	}
	printf ("\n");
}

int dna2ascii(char *dna)
{

	int len = strlen(dna)/4;
	for (int i=0; i < len ; i++)
	{
		int bits = 0;
		for (int dnaLetterNum = 0; dnaLetterNum < 4; dnaLetterNum++)
		{
			int c = dna[i*4 + dnaLetterNum];
			printf ("[%c]:\n", c);
			for (int j = 0; j < 4; j++) {
				if (c == encoding[ j].c)
				{
					bits <<= 2;
					bits |= (encoding[j].bits);
					printf("%x\n", bits);
				}
			}
		}
		//printf("*%c\n", bits);
	}
	printf ("\n");

}


int main(int argc, char *argv[])
{

	if (argc < 2) 
	{
		printf("Usage: %s activationcode\n", argv[0]);
		return -1;
	}

	char *activationCode = argv[1];

	printf("ActivationCode = %s\n", activationCode);

	ascii2dna(activationCode);
	dna2ascii(activationCode);

	return 0;
}

