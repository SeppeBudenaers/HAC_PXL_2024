#include "stdbool.h"
#include "BCD.h"

void BCD_to_SEG(char * Segment, char BCD)
{
	switch(BCD)
	{
		case 0:
			Segment[0] = 1;
			Segment[1] = 1;
			Segment[2] = 1;
			Segment[3] = 1;
			Segment[4] = 1;
			Segment[5] = 1;
			Segment[6] = 0;
			break;
		case 1:
			Segment[0] = 0;
			Segment[1] = 1;
			Segment[2] = 1;
			Segment[3] = 0;
			Segment[4] = 0;
			Segment[5] = 0;
			Segment[6] = 0;
			break;
		case 2:
			Segment[0] = 1;
			Segment[1] = 1;
			Segment[2] = 0;
			Segment[3] = 1;
			Segment[4] = 1;
			Segment[5] = 0;
			Segment[6] = 1;
			break;
		case 3:
			Segment[0] = 1;
			Segment[1] = 1;
			Segment[2] = 1;
			Segment[3] = 1;
			Segment[4] = 0;
			Segment[5] = 0;
			Segment[6] = 1;
			break;
		case 4:
			Segment[0] = 0;
			Segment[1] = 1;
			Segment[2] = 1;
			Segment[3] = 0;
			Segment[4] = 0;
			Segment[5] = 1;
			Segment[6] = 1;
			break;
		case 5:
			Segment[0] = 1;
			Segment[1] = 0;
			Segment[2] = 1;
			Segment[3] = 1;
			Segment[4] = 0;
			Segment[5] = 1;
			Segment[6] = 1;
			break;
		case 6:
			Segment[0] = 1;
			Segment[1] = 0;
			Segment[2] = 1;
			Segment[3] = 1;
			Segment[4] = 1;
			Segment[5] = 1;
			Segment[6] = 1;
			break;
		case 7:
			Segment[0] = 1;
			Segment[1] = 1;
			Segment[2] = 1;
			Segment[3] = 0;
			Segment[4] = 0;
			Segment[5] = 0;
			Segment[6] = 0;
			break;
		case 8:
			Segment[0] = 1;
			Segment[1] = 1;
			Segment[2] = 1;
			Segment[3] = 1;
			Segment[4] = 1;
			Segment[5] = 1;
			Segment[6] = 1;
			break;
		case 9:
			Segment[0] = 1;
			Segment[1] = 1;
			Segment[2] = 1;
			Segment[3] = 1;
			Segment[4] = 0;
			Segment[5] = 1;
			Segment[6] = 1;
			break;
		default:
			Segment[0] = 0;
			Segment[1] = 0;
			Segment[2] = 0;
			Segment[3] = 0;
			Segment[4] = 0;
			Segment[5] = 0;
			Segment[6] = 0;
			break;
		}
}