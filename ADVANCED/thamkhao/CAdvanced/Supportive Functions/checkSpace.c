///////////////////////////
//CHECK SPACES IN A NAME //
///////////////////////////

//Kiem tra ten nhap vao co chua khoang trang hay khong

int checkSpace(char[]);

int checkSpace(char string[])
{
    int i;
    for (i = 0; i < strlen(string); i++)
    {
        if (string[i] == ' ') return 1;
    }
    return 0;
}