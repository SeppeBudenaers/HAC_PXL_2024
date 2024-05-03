#include "stdio.h"
#include "stdbool.h"
#include "hls_custom_ex3.h"


/*
 * 		Logic And Gate
 * 		BTN1	BTN 2	LED3 (=BTN1 AND BTN2)
 * 		0		0		0
 * 		0		1		0
 * 		1		0		0
 * 		1		1		1
 */


int main()
{
	int status = 0;

	bool SW1_TB, SW2_TB,SW3_TB, LED3_TB[8], LED2_TB[8]; 		// Array of 4 because we have 4 rows in our truth table
	bool TB_GOLDEN_RESULT1[8] = {0,1,1,0,0,0,1,0}; 	// Truth table results of BTN1 and BTN2 function
    bool TB_GOLDEN_RESULT2[8] = {0,1,1,1,0,1,1,1}; 	// Truth table results of BTN1 and BTN2 function

	int i=0;
	for(int iBTN1=0; iBTN1<2; iBTN1++)
	{
		for(int iBTN2=0; iBTN2<2; iBTN2++)
		{
			for(int iBTN3=0; iBTN3<2; iBTN3++)
			{
				SW1_TB = (bool) iBTN1;
				SW2_TB = (bool) iBTN2;
				SW3_TB = (bool) iBTN3;
                
				CombLogic_Custom(SW1_TB, SW2_TB,SW3_TB, &LED3_TB[i], &LED2_TB[i]);
                i++;
			}
		}
	}

	for(int j = 0; j < 8; j++)
	{
		if(LED3_TB[j]!=TB_GOLDEN_RESULT1[j])
		{
			printf("Error at row %d of truth table \n\r",j);
			status = 1; //something wrong
		}

        if(LED2_TB[j]!=TB_GOLDEN_RESULT2[j])
        {
            printf("Error at row %d of truth table \n\r",j);
            status = 1; //something wrong
        }
		printf("d[%d] = %d = TB_GOLDEN_RESULT1[%d] = %d \n\r",j,LED3_TB[j],j,TB_GOLDEN_RESULT1[j]);
        printf("d[%d] = %d = TB_GOLDEN_RESULT2[%d] = %d \n\r",j,LED2_TB[j],j,TB_GOLDEN_RESULT2[j]);
	}

	if(status == 0)
		printf("Testbench Success!\n\r");
	else
		printf("Testbench Failure!\n\r");


	return status;
}
