/////////////////////////
//STANDARDIZE A STRING //
/////////////////////////

void trimLeft(char []);
void trimRight(char []);
void trimMiddle(char []);


void trimLeft(char string[])
{
    while (string[0] == ' ')
        strcpy(&string[0], &string[1]);
}

void trimRight(char string[])
{
    while (string[strlen(string) - 1] == ' ')
        strcpy(&string[strlen(string) - 1], &string[strlen(string)]);
}

void trimMiddle(char string[])
{
    int i;
    for (i = 0; i < strlen(string) ; i++)
        if ((string[i] == ' ') && (string[i + 1] == ' '))
        {
            strcpy(&string[i], &string[i + 1]);
            i--;
        }
}