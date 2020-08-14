#pragma once

#include <stdio.h>
#include <wchar.h>
#include <io.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include "windows.h"
#include "fileapi.h"

#define TwoGB 2147483648

int ExecuteReadWrite(unsigned int sizelimit = TwoGB, FILE* inputStream = stdin);


