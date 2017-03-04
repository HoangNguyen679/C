/////////////////////////////////////////////////////
//FIND THE SMALLEST COMMON MULTIPLE OF TWO NUMBERS //
/////////////////////////////////////////////////////

//Tim boi chung nho nhat cua hai so
//Lay vao 2 so
//Tra ve Boi chung nho nhat

int findSCM(int, int);

int findSCM(int argument1, int argument2)
{
    int greater, smaller;

    if (argument1 > argument2)
    {
        greater = argument1;
        smaller = argument2;
    }
    else
    {
        greater = argument2;
        smaller = argument1;
    }

    int i;
    for(i=greater; i<=greater*smaller; i++)
    {
        if(i%greater==0&&i%smaller==0)
            return i;
    }
}
