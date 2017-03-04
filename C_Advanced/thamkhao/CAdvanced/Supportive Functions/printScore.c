////////////////////////////
//PRINT SCORES OF PLAYERS //
////////////////////////////

//In ket qua thi dau cua tung nguoi
/*
            KET QUA THI DAU
---------------------------------------
    Ho Ten      1   2   3   4   5

     ...        6   6   6   7   8
     ...        6   6   6   7   8
     ...        6   6   6   7   8
 */

void indiem(type, int);

void indiem(type array_name[], int array_length)
{
    int i,j;

    printf("\n");
    printf("%35s\n","KET QUA THI DAU");
    printf("----------------------------------------------------------\n");
    printf("%13s\t\t1\t2\t3\t4\t5\n","Ho Ten");
    printf("\n");
    for(i=0;i<array_length;i++)
    {
        printf("%s\t",array_name[i].name);
        for(j=0;j<numOfTurn;j++)
        {
            printf("%d\t",array_name[i].score[j]);
        }
        printf("\n");
    }
}