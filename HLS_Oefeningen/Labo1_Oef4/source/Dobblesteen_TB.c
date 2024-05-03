#include "stdio.h"
#include "stdbool.h"
#include "Dobblesteen.h"

int main()
{
	int status = 0;

	bool BTN1_TB, BTN2_TB,BTN3_TB, LED4_TB[8], LED3_TB[8], LED2_TB[8], LED1_TB[8]; 	// Array of 4 because we have 4 rows in our truth table

	bool TB_GOLDEN_RESULT1[8] = {0,0,1,1,1,1,0,0}; 	// Truth table results of BTN1 and BTN2 function
	bool TB_GOLDEN_RESULT2[8] = {0,1,0,1,1,1,0,0};
	bool TB_GOLDEN_RESULT3[8] = {0,0,0,0,0,1,0,0};
	bool TB_GOLDEN_RESULT4[8] = {1,0,1,0,1,0,0,0};

	int i=0;
	for(int iBTN1=0; iBTN1<2; iBTN1++)
	{
		for(int iBTN2=0; iBTN2<2; iBTN2++)
		{
			for(int iBTN3=0; iBTN3<2; iBTN3++)
			{
				BTN1_TB = (bool) iBTN1;
				BTN2_TB = (bool) iBTN2;
				BTN3_TB = (bool) iBTN3;
				Dobblesteen(BTN1_TB, BTN2_TB,BTN3_TB, &LED4_TB[i], &LED3_TB[i], &LED2_TB[i], &LED1_TB[i]);
				i++;
			}
		}
	}

	for(int j = 0; j < 8; j++)
	{
		if(LED4_TB[j]!=TB_GOLDEN_RESULT4[j])
		{
			printf("Error at row %d of truth table \n\r",j);
			status = 1; //something wrong
		}

		if(LED3_TB[j]!=TB_GOLDEN_RESULT3[j])
		{
			printf("Error at row %d of truth table \n\r",j);
			status = 1; //something wrong
		}
		if(LED2_TB[j]!=TB_GOLDEN_RESULT2[j])
		{
			printf("Error at row %d of truth table \n\r",j);
			status = 1; //something wrong
		}
		if(LED1_TB[j]!=TB_GOLDEN_RESULT1[j])
		{
			printf("Error at row %d of truth table \n\r",j);
			status = 1; //something wrong
		}

		printf("d[%d] = %d = TB_GOLDEN_RESULT[%d] = %d \n\r",j,LED3_TB[j],j,TB_GOLDEN_RESULT4[j]);
		printf("d[%d] = %d = TB_GOLDEN_RESULT[%d] = %d \n\r",j,LED3_TB[j],j,TB_GOLDEN_RESULT3[j]);
		printf("d[%d] = %d = TB_GOLDEN_RESULT[%d] = %d \n\r",j,LED3_TB[j],j,TB_GOLDEN_RESULT2[j]);
		printf("d[%d] = %d = TB_GOLDEN_RESULT[%d] = %d \n\r",j,LED3_TB[j],j,TB_GOLDEN_RESULT1[j]);
	}

	if(status == 0)
		printf("Testbench Success!\n\r");
	else
		printf("Testbench Failure!\n\r");


	return status;
}
