# define_trace.h needs to know how to find our header
CFLAGS_trace.o				:= -I$(src)

ccflags-$(CONFIG_USB_DWC3_DEBUG)	:= -DDEBUG
ccflags-$(CONFIG_USB_DWC3_VERBOSE)	+= -DVERBOSE_DEBUG
ccflags-y += -Idrivers/usb/host -Idrivers/base/power

obj-$(CONFIG_USB_DWC3)			+= dwc3.o

dwc3-y					:= core.o

ifdef CONFIG_DEBUG_KERNEL
dwc3-y					+= debug.o trace.o
endif

ifneq ($(filter y,$(CONFIG_USB_DWC3_HOST) $(CONFIG_USB_DWC3_DUAL_ROLE)),)
	dwc3-y				+= host.o
endif

ifneq ($(filter y,$(CONFIG_USB_DWC3_GADGET) $(CONFIG_USB_DWC3_DUAL_ROLE)),)
	dwc3-y				+= gadget.o ep0.o
endif

ifneq ($(CONFIG_DEBUG_FS),)
	dwc3-y				+= debugfs.o
endif

##
# Platform-specific glue layers go here
#
# NOTICE: Make sure your glue layer doesn't depend on anything
# which is arch-specific and that it compiles on all situations.
#
# We want to keep this requirement in order to be able to compile
# the entire driver (with all its glue layers) on several architectures
# and make sure it compiles fine. This will also help with allmodconfig
# and allyesconfig builds.
##

obj-$(CONFIG_USB_DWC3_OMAP)		+= dwc3-omap.o
obj-$(CONFIG_USB_DWC3_EXYNOS)		+= dwc3-exynos.o
obj-$(CONFIG_USB_DWC3_PCI)		+= dwc3-pci.o
obj-$(CONFIG_USB_DWC3_KEYSTONE)		+= dwc3-keystone.o
obj-$(CONFIG_USB_DWC3_QCOM)		+= dwc3-qcom.o
obj-$(CONFIG_USB_DWC3_MSM)		+= dwc3-msm.o dbm.o
obj-$(CONFIG_USB_DWC3_ST)		+= dwc3-st.o
