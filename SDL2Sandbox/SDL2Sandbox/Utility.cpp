#include "Utility.h"
#include <stdlib.h>

int Utility::GenerateRandomFromRange(int minimum, int maximum)
{
	return rand() % (maximum - minimum + 1) + minimum;
}
