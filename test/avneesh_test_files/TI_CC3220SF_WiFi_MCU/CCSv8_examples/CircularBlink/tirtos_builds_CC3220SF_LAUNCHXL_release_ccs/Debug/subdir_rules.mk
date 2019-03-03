################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
build-1948194527:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-1948194527-inproc

build-1948194527-inproc: ../release.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"/home/stark/ti/xdctools_3_51_01_18_core/xs" --xdcpath="/home/stark/ti/simplelink_cc32xx_sdk_2_40_02_00/source;/home/stark/ti/simplelink_cc32xx_sdk_2_40_02_00/kernel/tirtos/packages;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4 -p ti.platforms.simplelink:CC3220SF -r release -c "/home/stark/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.5.LTS" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-1948194527 ../release.cfg
configPkg/compiler.opt: build-1948194527
configPkg/: build-1948194527


