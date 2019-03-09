################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/stark/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="/home/stark/ccsv8_ws/CC3220SF_Basics/CircularBlink_empty_CC3220SF_LAUNCHXL_tirtos_ccs" --include_path="/home/stark/ti/simplelink_cc32xx_sdk_2_40_02_00/source/ti/posix/ccs" --include_path="/home/stark/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.5.LTS/include" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


