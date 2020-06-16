
include ${G_COMMON_OBJ_DIR_F}


SRC_DIR_UP=$(shell pwd)/PdcpUp/Src
SRC_DIR_CM=$(shell pwd)/Common/Src
M_TARGET=${G_TARGET_DIR}/libPdcp.a
M_SOURCES += $(wildcard *.c $(SRC_DIR_UP)/*.c)
M_SOURCES += $(wildcard *.c $(SRC_DIR_CM)/*.c)

# todo


include ${G_COMPILE_S_LIB_F}

include ${G_COMMON_COMPILE_F}

-include $(M_DEPS)
