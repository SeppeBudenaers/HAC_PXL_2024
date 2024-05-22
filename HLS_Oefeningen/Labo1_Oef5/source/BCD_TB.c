#include "stdio.h"
#include "stdbool.h"
#include "Dobblesteen.h"

int main()
{
	int status = 0;

	char BCD;
	bool LED1_TB[8]; 	// Array of 4 because we have 4 rows in our truth table

	

	int i=0;
	for(int Character =0; Character <2; Character ++)
	{
		BTN1_TB = (int) Character;
		Dobblesteen(BTN1_TB, &LED1_TB[Character]);
		i++;
	}

	for(int j = 0; j < 8; j++)
	{
		if(LED4_TB[j]!=TB_GOLDEN_RESULT4[j])
		{
			printf("Error at row %d of truth table \n\r",j);
			status = 1; //something wrong
		}


		printf("d[%d] = %d = TB_GOLDEN_RESULT[%d] = %d \n\r",j,LED3_TB[j],j,TB_GOLDEN_RESULT4[j]);
	}

	if(status == 0)
		printf("Testbench Success!\n\r");
	else
		printf("Testbench Failure!\n\r");


	return status;
}
