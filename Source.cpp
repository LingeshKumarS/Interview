//C Program to read  arbitrary data from standard input and writes it to a file.

#include <stdio.h>
#include <wchar.h>
#include <io.h> 
#include <fcntl.h> 
#include <stdlib.h>


int main()
{
	wchar_t ofilepath[1000];
	wchar_t currchar;
	FILE* fptr;

	_setmode(_fileno(stdin), _O_U16TEXT);  // Enable unicode string support
	printf("Enter the output file path \n");
	wscanf_s(L"%s", ofilepath, _countof(ofilepath));
	 fflush(stdin);

	_wfopen_s(&fptr, ofilepath, L"w");
	if (!fptr)
	{
		printf("Failed to create/open file");
		return 1;
	}
	_setmode(_fileno(fptr), _O_U16TEXT);
	
	printf("Enter the string to save to file. Hit Ctrl+Z to quit the console \n");
	
	while(1)
	{
		currchar = fgetwc(stdin);
		if (currchar == WEOF)
			break;
		putwc(currchar, fptr);
	} 

 	fclose(fptr);
	return 0;
}