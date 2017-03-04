#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stddef.h>

void str_to_lower(char *s)
{
	int i = 0;
	for(i = 0; i < strlen(s); i++)
		tolower(s[i]);
}

void str_to_upper(char *s)
{
	int i = 0;
	for(i = 0; i < strlen(s); i++)
		toupper(s[i]);
}

void str_dash_space(char *s)
{
	int i = 0;
	for(i = 0; i < strlen(s); i++)
		if(s[i] == '-')
			s[i] = ' ';
}

// remove white space of char
void str_remove_ws(char *s)
{
	int i = 0;
	int n = 0;
	// remove white spaces in the beginning of string
	for(i = 0; i < strlen(s) - 1; i++)
	{
		if((s[i] == 32) || (s[i] == '\t'))
			for(n = i; i < strlen(s); n++)
				s[n] = s[n+1];
	}
}

void remove_tab(char *s)
{
	int i = 0;
	for(i = 0; i < strlen(s); i++)
	{
		if(s[i] == '\t')
			s[i] = s[i-1];
	}
}

char *strtoken(char *s, char *delim)
{
	register char *spanp;
	register int c, sc;
	char *tok;
	static char *last;


	if (s == NULL && (s = last) == NULL)
		return (NULL);

	/*
	 * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	 */
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
		if (c == sc)
			goto cont;
	}

	if (c == 0) {		/* no non-delimiter characters */
		last = NULL;
		return (NULL);
	}
	tok = s - 1;

	/*
	 * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	 * Note that delim must have one NUL; we stop if we see that, too.
	 */
	for (;;) {
		c = *s++;
		spanp = (char *)delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				last = s;
				return (tok);
			}
		} while (sc != 0);
	}
}


int main() {
  char st[] ="Where there is will, there is a way.";
  char *ch;
 
  printf("Split \"%s\"\n", st);
  ch = strtoken(st, " ");
  while (ch != NULL) {
	  printf("%s\n", ch);
	  ch = strtoken(NULL, " ,");
  }

  return 0;
}