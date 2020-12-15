CC := gcc
OBJDUMP := objdump
OBJCOPY := objcopy
BIN := hello

BUILD_DIR := build

FREERTOS_DIR_REL := ../../rtos/FreeRTOS/FreeRTOS
FREERTOS_DIR := $(abspath $(FREERTOS_DIR_REL))

INCLUDE_DIRS := -I.
INCLUDE_DIRS += -I${FREERTOS_DIR}/Source/include
INCLUDE_DIRS += -I${FREERTOS_DIR}/Source/portable/ThirdParty/GCC/Posix
INCLUDE_DIRS += -I${FREERTOS_DIR}/Soumrce/portable/ThirdParty/GCC/Posix/utils

SOURCE_FILES := $(wildcard *.c)
SOURCE_FILES += $(wildcard ${FREERTOS_DIR}/Source/*.c)
# Memory manager (use malloc() / free() )
SOURCE_FILES += ${FREERTOS_DIR}/Source/portable/MemMang/heap_4.c
# posix port
SOURCE_FILES += ${FREERTOS_DIR}/Source/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
SOURCE_FILES += ${FREERTOS_DIR}/Source/portable/ThirdParty/GCC/Posix/port.c

CFLAGS :=  -fno-common -Wall -pedantic -ggdb3 -Os -D_WINDOWS_ -ffunction-sections -fdata-sections -Wl,-M=$(BUILD_DIR)/$(BIN).map
#CFLAGS := -fno-common -Wall -pedantic -ggdb3 -O0 -D_WINDOWS_  
LDFLAGS := -pthread


OBJ_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)

DEP_FILE = $(OBJ_FILES:%.o=%.d)

${BIN} : $(BUILD_DIR)/$(BIN) $(BIN).lst size 

${BUILD_DIR}/${BIN} : ${OBJ_FILES}
	-mkdir -p ${@D}
	$(CC) $^ $(CFLAGS) $(INCLUDE_DIRS) ${LDFLAGS} -o $@


-include ${DEP_FILE}

${BUILD_DIR}/%.o : %.c
	-mkdir -p $(@D)
	$(CC) $(CFLAGS) ${INCLUDE_DIRS} -MMD -c $< -o $@

.PHONY: clean

clean:
	-rm -rf $(BUILD_DIR)


%.lst: 
	$(OBJDUMP) -x -S $(BUILD_DIR)/$(BIN) > $(BUILD_DIR)/$@

# size rule
size: 
	size $(BUILD_DIR)/$(BIN)
