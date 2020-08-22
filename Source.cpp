//C Program to read  arbitrary data from standard input and writes it to a file.

#include "Header.h"
#include "Test.h"

int getdirfrompath(const char* filepath, char dir[4])
{

	int len = strlen(filepath);
	//for (int i = 0; i < len; i++)
	//{
	int i = 0;
		if (filepath[i] >= 'A' && filepath[i] <= 'Z')
		{
			if (filepath[i + 1] == ':' && filepath[i + 2] == '\\')
			{
				dir[0] = filepath[i];
				dir[1] = filepath[i + 1];
				dir[2] = filepath[i + 2];
				dir[3] = '\0';
				return 0;
			}
			return 1;
		}
	//}
	return 1;
}


char* allocateBuffer(unsigned int sizelimit, size_t& buffsize)
{
	char* buffer = NULL;
	int currBuffSize = sizelimit;
	while (currBuffSize > 0)
	{
		buffer = (char*)malloc(FiveHundredMB);
		if (buffer)
		{
			buffsize = currBuffSize;
			break;
		}
		else
			currBuffSize = currBuffSize / 2;
	}
	return buffer;


}

int ExecuteReadWrite(const char* outFilePath, unsigned int sizelimit, FILE* inputStream)
{

	::ULARGE_INTEGER lpFreeBytesAvailableToCaller{};
	::ULARGE_INTEGER lpTotalNumberOfBytes{};
	::ULARGE_INTEGER lpTotalNumberOfFreeBytes{};

	FILE* fptr;
	
	_setmode(_fileno(inputStream), _O_BINARY);  

	fopen_s(&fptr, outFilePath, "wb");
	if (!fptr)
	{
		printf("Failed to create/open file");
		return 1;
	}
	_setmode(_fileno(fptr), _O_BINARY);

	// Checking available disk space Start
	char dir[4];
	int rc;
	unsigned int* xyz;
	if (!getdirfrompath(outFilePath, dir))
		rc = GetDiskFreeSpaceExA(dir, &lpFreeBytesAvailableToCaller, &lpTotalNumberOfBytes, &lpTotalNumberOfFreeBytes);
	else
		rc = GetDiskFreeSpaceExA(NULL, &lpFreeBytesAvailableToCaller, &lpTotalNumberOfBytes, &lpTotalNumberOfFreeBytes);
	sizelimit = (sizelimit < lpTotalNumberOfFreeBytes.QuadPart) ? sizelimit : lpTotalNumberOfFreeBytes.QuadPart;  // Updating file size with min(2GB , available disk size) , size 2GB is max size that a file editor can read.
	// Checking available disk space End

	int count = 0;
	char* buffer;
	size_t buffsize = 1;
	buffer = allocateBuffer(sizelimit, buffsize);	// Allocating maximum buffer size possible 
	
	if (!buffer)
	{
		printf("Failed to allocate buffer memory \n");
		return 1;
	}
	
	int wcount;
	while ((count = fread(buffer, 1, buffsize, inputStream)) != 0)
	{
		wcount = fwrite(buffer, 1, count, fptr);
		if (wcount != count)
		{
			//error while writing 
			if (ferror(fptr))
			{
				printf("Error Writing to myfile.txt ,check disk space available \n");
				break;
			}
		}

	}

	free(buffer);
	fclose(fptr);
	return 0;
}
