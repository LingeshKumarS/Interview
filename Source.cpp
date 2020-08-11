//C Program to read  arbitrary data from standard input and writes it to a file.

#include "Header.h"
#include "Test.h"

int ExecuteReadWrite(FILE* inputStream, int sizelimit  )
{
	wchar_t ofilepath[1000];
	//wchar_t currchar;
	wchar_t line[1000];
	FILE* fptr;

	_setmode(_fileno(inputStream), _O_U16TEXT);  // Enable Unicode string support
	printf("Enter the output file path \n");
	#ifdef UnitTest
	//ofilepath = L"Out.txt";
	wcscpy_s(ofilepath, L"Out.txt");
	#else
	wscanf_s(L"%s", ofilepath, _countof(ofilepath));
	#endif

	fflush(inputStream);

	_wfopen_s(&fptr, ofilepath, L"w");
	if (!fptr)
	{
		printf("Failed to create/open file");
		return 1;
	}
	_setmode(_fileno(fptr), _O_U16TEXT);

	printf("Enter the string to save to file. Hit Ctrl+Z to quit the console \n");

	//while(1)							// OLD code
	//{
	//	currchar = fgetwc(stdin);
	//	if (currchar == WEOF)
	//		break;
	//	putwc(currchar, fptr);
	//} 
	int currlen = 0;
	int lineLenLimit = sizelimit / sizeof(wchar_t);
	while (fgetws(line, lineLenLimit, inputStream) != NULL) {		// New optimized code, which reads line by line from stdin
															// instead of old implementation which reads char by char and writes to file.
		int linelen = wcslen(line);
		int totlen = currlen + linelen;
		
		if (totlen > lineLenLimit)
		{
			int diff = lineLenLimit - currlen;
			int i = 0;
			while (i < diff)
			{
				fputwc(line[i], fptr);
				i++;
			}
			printf("Size of file limit exceeded, Ignored few characters at the end to fit file size \n");
			break;
		}
		currlen += linelen;
		fputws(line, fptr);
	}

	fclose(fptr);
	return 0;

}


