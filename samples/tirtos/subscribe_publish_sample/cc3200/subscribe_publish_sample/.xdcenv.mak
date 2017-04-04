#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /home/mdubuntu/ti/tirtos_cc32xx_2_16_01_14/products/ns_1_11_00_10/packages;/home/mdubuntu/ti/tirtos_cc32xx_2_16_01_14/products/bios_6_45_02_31/packages;/home/mdubuntu/ti/tirtos_cc32xx_2_16_01_14/packages;/home/mdubuntu/ti/tirtos_cc32xx_2_16_01_14/products/uia_2_00_05_50/packages;/home/mdubuntu/ti/tirtos_cc32xx_2_16_01_14/products/tidrivers_cc32xx_2_16_01_13/packages
override XDCROOT = /home/mdubuntu/ti/xdctools_3_32_00_06_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /home/mdubuntu/ti/tirtos_cc32xx_2_16_01_14/products/ns_1_11_00_10/packages;/home/mdubuntu/ti/tirtos_cc32xx_2_16_01_14/products/bios_6_45_02_31/packages;/home/mdubuntu/ti/tirtos_cc32xx_2_16_01_14/packages;/home/mdubuntu/ti/tirtos_cc32xx_2_16_01_14/products/uia_2_00_05_50/packages;/home/mdubuntu/ti/tirtos_cc32xx_2_16_01_14/products/tidrivers_cc32xx_2_16_01_13/packages;/home/mdubuntu/ti/xdctools_3_32_00_06_core/packages;..
HOSTOS = Linux
endif
