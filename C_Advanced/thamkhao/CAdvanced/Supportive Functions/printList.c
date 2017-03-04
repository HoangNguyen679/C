////////////////////////////
//PRINT A LIST OF PLAYERS //
////////////////////////////

//In ra danh sach nguoi choi co danh so thu tu
/*
		DANH SACH THI DAU
	-----------------------
	   STT		 Ho ten
	     1         ...
	     2         ...
 */

void indanhsach(type, int);

void indanhsach(type array_name[], int array_length)
{
    int i;
    printf("\t\n%32s\n","DANH SACH THI DAU");
    printf("\t----------------------------------\n");
    printf("\t%5s%20s\n","STT","Ho ten");
    printf("\n");
    for (i = 0; i < array_length; i++)
    {
        trimLeft(array_name[i].name);
        trimRight(array_name[i].name);
        trimMiddle(array_name[i].name);
        capitalize(array_name[i].name);

        printf("\t%5d%25s\n", i + 1, array_name[i].name);
    }
    printf("\n");
}