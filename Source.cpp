//C Program to read  arbitrary data from standard input and writes it to a file.

#include "Header.h"
#include "Test.h"

int getdirfrompath(wchar_t* filepath, wchar_t dir[4])
{
	
	int len = wcslen(filepath);
		for(int i = 0; i < len; i++)
		{
			if (filepath[i] >= 'A' && filepath[i] <= 'Z')
			{
				if (filepath[i + 1] == ':' && filepath[i + 2] == '\\')
				{
					dir[0] = filepath[i];
					dir[1] = filepath[i + 1];
					dir[2] = filepath[i + 2];
					dir[3] = '\0';
				}
				return 0;
			}
		}
		return 1;
}
int isvalidpath(wchar_t* filepath)
{
	//basic filepath check
	int len = wcslen(filepath);
	if (len <= 0)
		return 1;
	if (filepath[0] == '"' || filepath[len - 1] == '"')
		return 0;

	return 1;
}


int ExecuteReadWrite( unsigned int sizelimit  ,FILE* inputStream  )
{
	
	::ULARGE_INTEGER lpFreeBytesAvailableToCaller{};
	::ULARGE_INTEGER lpTotalNumberOfBytes{};
	::ULARGE_INTEGER lpTotalNumberOfFreeBytes{};
	
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
	wscanf_s(L"%[^\n]%*c", ofilepath, _countof(ofilepath));			// Modified to get the filepath even if it has spaces
	#endif

	if (!isvalidpath(ofilepath))
	{
		printf("filepath starts/ends with a quote, give filepath without quotes");
		return 1;
	}

	fflush(inputStream);
	
	_wfopen_s(&fptr, ofilepath, L"w");
	if (!fptr)
	{
		printf("Failed to create/open file");
		return 1;
	}
	
	// Checking available disk space Start
	wchar_t dir[4];				
	int rc;
	unsigned int *xyz;
	if (!getdirfrompath(ofilepath, dir))
		rc = GetDiskFreeSpaceExW(dir, &lpFreeBytesAvailableToCaller, &lpTotalNumberOfBytes, &lpTotalNumberOfFreeBytes);
	else
		rc = GetDiskFreeSpaceExW(NULL, &lpFreeBytesAvailableToCaller, &lpTotalNumberOfBytes, &lpTotalNumberOfFreeBytes);
	sizelimit = (sizelimit < lpTotalNumberOfFreeBytes.QuadPart)? sizelimit : lpTotalNumberOfFreeBytes.QuadPart;  // Updating file size with min(2GB , available disk size) , size 2GB is max size that a file editor can read.
	// Checking available disk space End

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


