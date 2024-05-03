#include "stdbool.h"
#include "hls_custom_ex3.h"

void CombLogic_Custom(bool A_in, bool B_in, bool C_in, bool *Out1, bool *Out2)
{
#pragma HLS INTERFACE ap_ctrl_none port = return
#pragma HLS INTERFACE ap_none port = A_in
#pragma HLS INTERFACE ap_none port = B_in
#pragma HLS INTERFACE ap_none port = C_in

		*Out1 = ((!A_in && !B_in) && C_in) || ((!A_in && B_in) && !C_in) || ((A_in && B_in) && !C_in);
        *Out2 = !(((!A_in && !B_in) && !C_in) || ((A_in && !B_in) && !C_in));
}
