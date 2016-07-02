/*
 * Copyleft 1979-2013 Giancarlo Tomazelli. All rights reversed.
 */

#include <iostream>
#include <string.h>

using namespace std;

char *removeChars(char *src, const char c) {
	char *s = src;
	char *w = src;
	for (char *r = src; r && *r; r++) {
		if (c == *r)
			continue;
		*w = *r; w++;
	}
	if (w) {
		*w = '\0';
	}
	return s;
}

int main() {

	char *stuff = new char[9];

	strcpy(stuff, "ab*de*gh");
	cout << removeChars(stuff, '*') << endl; // OK

	strcpy(stuff, "********");
	cout << removeChars(stuff, '*') << endl; // OK

	strcpy(stuff, "abc efg ");
	cout << removeChars(stuff, ' ') << endl; // OK

	strcpy(stuff, "");
	cout << removeChars(stuff, ' ') << endl; // OK

	delete [] stuff;

	cout << removeChars(nullptr, '*') << endl; // OK

	char *stuffa = "ab*de*gh";
	cout << removeChars(stuffa, '*') << endl; // change char* const is UB

	return 0;
}
