# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_control {
centerX { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 16
	offset_end 23
}
centerY { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 24
	offset_end 31
}
ap_start { }
ap_done { }
ap_ready { }
ap_idle { }
interrupt {
}
}
dict set axilite_register_dict control $port_control


set port_control_r {
imageRGBA { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 16
	offset_end 27
}
output_r_offset { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 28
	offset_end 39
}
}
dict set axilite_register_dict control_r $port_control_r


