## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,em4 linker.cmd package/cfg/certflasher_pem4.oem4

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/certflasher_pem4.xdl
	$(SED) 's"^\"\(package/cfg/certflasher_pem4cfg.cmd\)\"$""\"/home/mdubuntu/Downloads/aws-iot-device-sdk-embedded-c-hanged-CC3200MOD_Test_with_install_file/samples/tirtos/certs/cc3200/certflasher/\1\""' package/cfg/certflasher_pem4.xdl > $@
	-$(SETDATE) -r:max package/cfg/certflasher_pem4.h compiler.opt compiler.opt.defs
