/**
 * wordvalue - print the word value of a file
 * Copyright (C) 2013  Sebastian Buchwald <Sebastian.Buchwald@kit.edu>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

int main(int argc, char **argv)
{
	if (argc > 2) {
		fprintf(stderr, "Usage: %s [input_file]\n", argv[0]);
		return EXIT_FAILURE;
	}

	if (!setlocale(LC_CTYPE, "")) {
		fprintf(stderr, "Cannot set the specified locale. "
				"Check LANG, LC_CTYPE, LC_ALL.\n");
		return EXIT_FAILURE;
	}

	FILE *input_file;

	if (argc == 2) {
		input_file = fopen(argv[1], "r");
		if (input_file == NULL) {
			fprintf(stderr, "Cannot open input file %s\n", argv[1]);
			return EXIT_FAILURE;
		}
	} else {
		input_file = stdin;
	}

	unsigned bww = 0;
	wint_t   character;
	while ((character = fgetwc(input_file)) != WEOF) {
		if (character >= L'0' && character <= L'9') {
			bww += character - L'0';
		} else if (character >= L'A' && character <= L'Z') {
			bww += character - L'A' + 1;
		} else if (character >= L'a' && character <= L'z') {
			bww += character - L'a' + 1;
		} else switch (character) {
			case L'Ä':
			case L'ä':
				bww += 27;
				break;
			case L'Ö':
			case L'ö':
				bww += 28;
				break;
			case L'Ü':
			case L'ü':
				bww += 29;
				break;
			case L'ß':
				bww += 30;
				break;
		}
	}

	printf("%u\n", bww);

	return EXIT_SUCCESS;
}
