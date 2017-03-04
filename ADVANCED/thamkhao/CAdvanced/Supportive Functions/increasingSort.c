////////////////////
//SORT INCREASING //
////////////////////

//Sap xep mot day theo thu tu tang dan
//Luu y: thay doi kieu cua array va temp cho phu hop

void increaseSort(type[], int);

void increaseSort(type array_name[], int array_length)
{
    int i, j;
    type temp;

    for (i = 1; i < array_length; i++)
    {
        for (j = 0; j < array_length - 1; j++)
        {
            if (array_name[j] > array_name[j + 1])
            {
                temp = array_name[j];
                array_name[j] = array_name[j + 1];
                array_name[j + 1] = temp;
            }
        }
    }
}