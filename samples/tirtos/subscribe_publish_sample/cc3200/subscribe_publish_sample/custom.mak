## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,em4 linker.cmd package/cfg/subscribe_publish_sample_pem4.oem4

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/subscribe_publish_sample_pem4.xdl
	$(SED) 's"^\"\(package/cfg/subscribe_publish_sample_pem4cfg.cmd\)\"$""\"/home/mdubuntu/Downloads/CC3200MOD-SDK/samples/tirtos/subscribe_publish_sample/cc3200/subscribe_publish_sample/\1\""' package/cfg/subscribe_publish_sample_pem4.xdl > $@
	-$(SETDATE) -r:max package/cfg/subscribe_publish_sample_pem4.h compiler.opt compiler.opt.defs
