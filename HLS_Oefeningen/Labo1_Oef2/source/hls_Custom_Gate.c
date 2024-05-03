#include "stdbool.h"
#include "hls_Custom_gate.h"

void CombLogic_Custom(bool BTN1, bool BTN2, bool BTN3, bool  *LED3)
{
#pragma HLS INTERFACE ap_ctrl_none port = return
#pragma HLS INTERFACE ap_none port = BTN1
#pragma HLS INTERFACE ap_none port = BTN2
#pragma HLS INTERFACE ap_none port = BTN3
#pragma HLS INTERFACE ap_none port = LED3

		*LED3 = (BTN1 && BTN2) || (BTN2 && BTN3);
}
