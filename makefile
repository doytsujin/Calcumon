# ----------------------------
# Makefile Options
# ----------------------------

NAME = CALCUMON
ICON = icon.png
DESCRIPTION = "L'experience CALCUMON unique !"
COMPRESSED = YES
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
