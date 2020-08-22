#include "Header.h"


int compareIn_Outfiles()
{
	FILE* fptrout;
	FILE* fptroutref;
	fopen_s(&fptrout, "Out.jpg", "rb");
	if (!fptrout)
	{
		printf("Failed to create/open Out.txt");
		return 1;
	}
	fopen_s(&fptroutref, "pic.jpg", "rb");
	if (!fptroutref)
	{
		printf("Failed to create/open Out_ref.txt");
		return 1;
	}

	char o_char, oref_char;
	bool isdiff = 0;
	while(1)							
	{
		o_char  = fgetc(fptrout);
		oref_char = fgetc(fptroutref);
		if (o_char == EOF  && oref_char == EOF)
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

	fopen_s(&fptrin, "pic.jpg", "rb");
	if (!fptrin)
	{
		printf("Failed to create/open In.txt");
		return 1;
	}
	int rc = ExecuteReadWrite("Out.jpg", FiveHundredMB, fptrin);

	if (!rc)
	{
		rc = compareIn_Outfiles();

	}
	if (rc == 0)
		printf("OK");
	else
		printf("Test case failed due to comparison fail");

	return rc;

}