# Makefile
# Allows the project to be build from outside the Arduino IDE.

BOARD_TAG = mega
BOARD_SUB = atmega2560

# Point ARDMK_DIR to a clone of https://github.com/sudar/Arduino-Makefile.
include $(ARDMK_DIR)/Arduino.mk
