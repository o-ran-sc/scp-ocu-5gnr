
	include ${G_COMMON_OBJ_DIR_F}


SRC_DIR=$(shell pwd)
M_TARGET=${G_TARGET_DIR}/libsdap.a

M_SOURCES += $(SRC_DIR)/sdap/Src/sdapCore.c
M_SOURCES += $(SRC_DIR)/sdap/Src/sdapDataProc.c



include ${G_COMPILE_S_LIB_F}

include ${G_COMMON_COMPILE_F}

-include $(M_DEPS)

