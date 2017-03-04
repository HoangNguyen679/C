////////////////////////////////////////////////////
//FIND THE GREATEST COMMON DIVISOR OF TWO NUMBERS //
////////////////////////////////////////////////////

//Tim uoc chung lon nhat cua hai so
//Lay vao 2 so
//Tra ve Uoc chung lon nhat

int findGCD(int,int);

int findGCD(int argument1,int argument2)
{
	int greater,smaller;

	if(argument1>argument2)
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
	for(i=smaller;i>=1;i--)
	{
		if(smaller%i==0&&greater%i==0)
			return i;
	}
}
