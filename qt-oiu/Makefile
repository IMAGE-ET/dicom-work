.PHONY: all clean compile template add_depend_path add_include_path add_headers add_sources

PROJECT := qt-oiu1

SUBDIRS := include src

MAIN_DIR := .
MAIN_SRCS := login_window.cpp main.cpp oiu_gui.cpp add_riu.cpp

DC_DIR := ../dicom-common
DC_SRCS := oiu_config.c

C_DIR := ../common
C_SRCS := ini.c

all: compile
#$(PROJECT).pro: template add_depend_path add_include_path add_headers add_sources
$(PROJECT).pro: template add_include_path add_headers add_sources

template:
	echo "TEMPLATE = app" > $@
	echo TARGET = >> $@

add_depend_path:
	echo DEPENDPATH = $(addprefix $(MAIN_DIR)/, $(SUBDIRS)) >> $(PROJECT).pro
	echo DEPENDPATH += $(addprefix $(DC_DIR)/, $(SUBDIRS)) >> $(PROJECT).pro
	echo DEPENDPATH += $(addprefix $(C_DIR)/, $(SUBDIRS)) >> $(PROJECT).pro

add_include_path:
	echo INCLUDEPATH += $(MAIN_DIR)/include >> $(PROJECT).pro
	echo INCLUDEPATH += $(DC_DIR)/include >> $(PROJECT).pro
	echo INCLUDEPATH += $(C_DIR)/include >> $(PROJECT).pro

add_headers:
	echo HEADERS += $(addprefix $(MAIN_DIR)/include/, $(MAIN_SRCS:.cpp=.h)) >> $(PROJECT).pro
	echo HEADERS += $(addprefix $(DC_DIR)/include/, $(DC_SRCS:.c=.h)) >> $(PROJECT).pro
	echo HEADERS += $(addprefix $(C_DIR)/include/, $(C_SRCS:.c=.h)) >> $(PROJECT).pro

add_sources:
	echo SOURCES += $(addprefix $(MAIN_DIR)/src/, $(MAIN_SRCS)) >> $(PROJECT).pro
	echo SOURCES += $(addprefix $(DC_DIR)/src/, $(DC_SRCS)) >> $(PROJECT).pro
	echo SOURCES += $(addprefix $(C_DIR)/src/, $(C_SRCS)) >> $(PROJECT).pro

build.mak: $(PROJECT).pro
	qmake -o $@

compile: build.mak
	make -f build.mak

clean:
	rm -fr *.o $(PROJECT) build.mak $(PROJECT).pro moc_*.cpp
