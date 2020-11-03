############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project hls4
set_top dft
add_files coefficients256.h
add_files dft.cpp
add_files dft.h
add_files -tb dft_test.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb out.gold.dat -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution14"
set_part {xc7z020-clg484-1}
create_clock -period 10 -name default
#source "./hls4/solution14/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog