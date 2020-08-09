#include "Header.h"


int compareIn_Outfiles()
{
	FILE* fptrout;
	FILE* fptroutref;
	_wfopen_s(&fptrout, L"Out.txt", L"r");
	if (!fptrout)
	{
		printf("Failed to create/open Out.txt");
		return 1;
	}
	_wfopen_s(&fptroutref, L"Out_ref.txt", L"r");
	if (!fptroutref)
	{
		printf("Failed to create/open Out_ref.txt");
		return 1;
	}

	wchar_t o_char, oref_char;
	bool isdiff = 0;
	while(1)							
	{
		o_char  = fgetwc(fptrout);
		oref_char = fgetwc(fptroutref);
		if (o_char == WEOF  && oref_char == WEOF)
			break;
		

		if (o_char != oref_char)
		{
			isdiff = 1;
			break;
		}
		
	} 

	return isdiff;
}


int main()
{
	FILE* fptrin;

	_wfopen_s(&fptrin, L"in.txt", L"r");
	if (!fptrin)
	{
		printf("Failed to create/open In.txt");
		return 1;
	}
	int rc = ExecuteReadWrite(fptrin);

	if (!rc)
	{
		rc = compareIn_Outfiles();

	}
	if(rc == 0)
		printf("OK");
	else
		printf("Test case failed due to comparison fail");
		
	return rc;

}