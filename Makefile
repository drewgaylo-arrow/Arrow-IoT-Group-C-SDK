# Makefile of project "ArrowConnect C SDK"
#==========================================================

#==========================================================
# The C SDK requires the following variables defined
#
# LIBDIR - Path where the objects are stored
# SDK_PATH - Absolute path to the SDK from the building project
# SDK_IMPL - Location of the platform specific source files
# GCC_BIN  - Location of gcc binary
# GCC_PREFIX - Prefix for the gcc binary
# PLATFORM - Platform we are building for -D__$(PLATFORM)__
# CC_SYMBOLS - Arguments and build params to gcc
# OPT - Optimization level
#
# WOLFSSL = yes - Include WolfSSL
# CJSON = yes - Include the embedded JSON library
#
#==========================================================
SDK_PATH = .
SDK_IMPL = . 
LIBDIR ?= build

WOLFSSL ?= no
CJSON = yes

BUILD_MACHINE = cygwin

GCC_BIN = 
GCC_PREFIX = 
PLATFORM =

OPT ?= -O0 

CC_SYMBOLS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11 -ffunction-sections -fdata-sections

# Bounds checking, default to local dir
####################################################
LIBDIR ?= .
SDK_IMPL ?= .
SDK_PATH ?= .

ifeq ($(BUILD_MACHINE),cygwin)
GCC_BIN =  /cygdrive/c/Program\ Files\ \(x86\)/Atollic/TrueSTUDIO\ for\ STM32\ 9.0.1/ARMTools/bin
GCC_PREFIX = arm-atollic-eabi
cross_abspath = $1
endif

# Include the SDK Makefile
####################################################
-include $(SDK_PATH)/Makefile.sdk

# Workaround for cygwin. Add -I . if there is a -I ./
ifeq ($(SDK_PATH),./)
SDK_INCLUDES += -I .
endif


# Targets
####################################################
default: all

all: $(SDK_TARGET)

info:
	echo $(SDK_SRC)

new: clean all

test:
	echo "Testing"

clean:
	rm -rf $(LIBDIR)/acn-sdk-c
	rm -rf $(LIBDIR)/*.a
