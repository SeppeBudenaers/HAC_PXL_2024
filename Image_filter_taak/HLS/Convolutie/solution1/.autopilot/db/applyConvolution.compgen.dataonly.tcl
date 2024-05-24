# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_control {
height { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 16
	offset_end 23
}
width { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 24
	offset_end 31
}
channels { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 32
	offset_end 39
}
}
dict set axilite_register_dict control $port_control


set port_control_r {
ap_start { }
ap_done { }
ap_ready { }
ap_idle { }
interrupt {
}
}
dict set axilite_register_dict control_r $port_control_r


