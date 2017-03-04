/////////////////////////////////////
//CAPITALIZE FIRST LETTERS IN NAME //
/////////////////////////////////////

//Viet hoa chu cai dau tien cua ten
//Ten phai duoc xoa khoang trang lien nhau truoc khi viet hoa

void capitalize(char[]);

void capitalize(char string[])
{
    int i;
    for (i = 0; i < strlen(string); i++)
    {
        string[i] = tolower(string[i]);
    }
    for (i = 0; i < strlen(string); i++)
    {
        if (i == 0) string[i] = string[i] - 'a' + 'A';
        if (string[i] == ' ') string[i + 1] = string[i + 1] - 'a' + 'A';
    }
}