/////////////////
//CLEAR BUFFER //
/////////////////

//Xoa bo nho dem de tranh troi lenh gets()
//Luu y: dung truoc vong lap for

void clear_buffer();

void clear_buffer ()
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}