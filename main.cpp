
#include "Header.h"

int main(int argc, char* argv[])
{
	if (argc > 1 )
	{
		int filesize = atoi(argv[1]);
		if(filesize > 0)
			return ExecuteReadWrite(filesize);
	}
	return ExecuteReadWrite();
}