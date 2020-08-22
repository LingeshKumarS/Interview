
#include "Header.h"




int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		char* oFile = argv[1];
			return ExecuteReadWrite(oFile);
	}
	
	return ExecuteReadWrite();
}