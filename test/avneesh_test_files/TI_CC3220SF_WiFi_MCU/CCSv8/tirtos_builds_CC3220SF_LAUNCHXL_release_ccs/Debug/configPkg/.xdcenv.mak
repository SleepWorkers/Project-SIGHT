#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /home/stark/ti/simplelink_cc32xx_sdk_2_40_02_00/source;/home/stark/ti/simplelink_cc32xx_sdk_2_40_02_00/kernel/tirtos/packages
override XDCROOT = /home/stark/ti/xdctools_3_51_01_18_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /home/stark/ti/simplelink_cc32xx_sdk_2_40_02_00/source;/home/stark/ti/simplelink_cc32xx_sdk_2_40_02_00/kernel/tirtos/packages;/home/stark/ti/xdctools_3_51_01_18_core/packages;..
HOSTOS = Linux
endif
