///////////////////////////////////////////
//CREATE MENU AND STRUCTURE OF A PROGRAM //
///////////////////////////////////////////


//prototype
char getMenu();

//declare in main()
char choice;

while (1)
{
    choice = getMenu();

    switch (choice)
    {
    case '1':
    {
        break;
    }
    case '2':
    {
        break;
    }
    case '3':
    {
        break;
    }
    case '4'://Exit
    {
        return 0;
        break;
    }
    default:
    {
        printf("Khong hop le!\n");
        break;
    }
    }
}

//function body
char getMenu()
{
    char choice;

    printf("----------------------------------------------------------\n");
    printf("\t.================================.\n");
    printf("\t*    1.Task 1                    *\n");
    printf("\t*    2.Task 2                    *\n");
    printf("\t*    3.Task 3                    *\n");
    printf("\t*    4.Thoat                      *\n");
    printf("\t*================================*\n");

    printf("\t\tNhap lua chon: ");
    scanf("%c",&choice);
    printf("----------------------------------------------------------\n");

    return choice;
}

