# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\david\workspace\no-rtos\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\david\workspace\no-rtos\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {no-rtos}\
-hw {C:\Xilinx\Vitis\2023.2\data\embeddedsw\lib\fixed_hwplatforms\zed.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/Users/david/workspace}

platform write
platform generate -domains 
platform active {no-rtos}
domain active {zynq_fsbl}
bsp reload
domain active {standalone_domain}
bsp reload
bsp setlib -name xilffs -ver 5.1
bsp setlib -name xiltimer -ver 1.3
bsp config stdin "ps7_coresight_comp_0"
bsp config stdout "ps7_coresight_comp_0"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
bsp reload
bsp reload
platform generate
