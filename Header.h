#pragma once

#include <stdio.h>
#include <wchar.h>
#include <io.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include "windows.h"
#include "fileapi.h"

#define FiveHundredMB 524288000

int ExecuteReadWrite(const char* outFilePath = "OUTFile", unsigned int sizelimit = FiveHundredMB, FILE* inputStream = stdin);


