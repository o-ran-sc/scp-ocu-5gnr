
include ${G_MODULE_CONFIG_F}

M_OBJS_DIR=${G_TARGET_DIR}/app/objs
M_DEPS_DIR=${G_TARGET_DIR}/app/deps

SRC_DIR=$(shell pwd)

M_TARGET  = ${G_TARGET_DIR}/CuUpApp

M_S_LIBS += ${G_TARGET_DIR}/libsdap.a
M_S_LIBS += ${G_TARGET_DIR}/libPdcp.a


M_D_LIBS += -lssl
M_D_LIBS += -lcrypto
#把make_config/Makefile改APP下所有的依赖生成的.a都需要增加在该路径下

#M_SOURCES +=  ${G_ROOT_DIR}/Cu/OamAdp/Src/cuupInit.c
M_SOURCES += $(SRC_DIR)/Src/main.c

include ${G_COMPILE_APP_F}
	
include ${G_COMMON_COMPILE_F}

-include $(M_DEPS)

