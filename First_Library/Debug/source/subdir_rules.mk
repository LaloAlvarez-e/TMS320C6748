################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/%.obj: ../source/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.3/bin/cl6x" -mv6740 -O3 --opt_for_speed=5 --include_path="D:/Codigos/CCS 7.2/Propios/TMS320C6748/DSP_Applications_Using_C/First_Library" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.3/include" --define=c6748 -g --c99 --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --gen_profile_info --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/%.obj: ../source/%.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.3/bin/cl6x" -mv6740 -O3 --opt_for_speed=5 --include_path="D:/Codigos/CCS 7.2/Propios/TMS320C6748/DSP_Applications_Using_C/First_Library" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c6000_8.3.3/include" --define=c6748 -g --c99 --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --gen_profile_info --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


