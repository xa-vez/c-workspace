#!/bin/bash
 
#information 
#https://www.freertos.org/FreeRTOS-simulator-for-Linux.html

#                               ----demo
#                               |---hello 
#             --- application ------... 
#             |                 |---xxxxx
# workspace ---
#             |
#             |--------- rtos --- FreeRTOS (github repo)
#             |
#             | 
#             |
#             |---------- tcp (todo)   
               

FREERTOS_PATH='../rtos/FreeRTOS'

# Download FreeRTOS from github repository
git clone https://github.com/FreeRTOS/FreeRTOS.git ${FREERTOS_PATH}
cd ${FREERTOS_PATH}
git submodule update --init --recursive

