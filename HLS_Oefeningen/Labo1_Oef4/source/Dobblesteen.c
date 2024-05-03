#include "stdbool.h"
#include "Dobblesteen.h"

void Dobblesteen(bool BTN1, bool BTN2, bool BTN3, bool *LED4, bool *LED3, bool *LED2, bool *LED1)
{
#pragma HLS INTERFACE ap_ctrl_none port = return
#pragma HLS INTERFACE ap_none port = BTN1
#pragma HLS INTERFACE ap_none port = BTN2
#pragma HLS INTERFACE ap_none port = BTN3

#pragma HLS INTERFACE ap_none port = LED4
#pragma HLS INTERFACE ap_none port = LED3
#pragma HLS INTERFACE ap_none port = LED2
#pragma HLS INTERFACE ap_none port = LED1

		*LED4 = ((!BTN1&&!BTN2)&&!BTN3) || ((!BTN1&&BTN2)&&!BTN3) || ((BTN1&&!BTN2)&&!BTN3);
		*LED3 = ((BTN1&&!BTN2)&&BTN3);
		*LED2 = ((!BTN1&&!BTN2)&&BTN3) || ((!BTN1&&BTN2)&&BTN3) || ((BTN1&&!BTN2)&&!BTN3) || ((BTN1&&!BTN2)&&BTN3);
		*LED1 = ((!BTN1&&BTN2)&&!BTN3) || ((!BTN1&&BTN2)&&BTN3) || ((BTN1&&!BTN2)&&!BTN3) || ((BTN1&&!BTN2)&&BTN3);

}
