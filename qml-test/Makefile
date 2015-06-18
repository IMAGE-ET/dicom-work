.PHONY: all clean compile template add_depend_path add_include_path add_headers add_sources

PROJECT := qml-test

SUBDIRS := include src

MAIN_DIR := .
MAIN_SRCS := test.cpp Gauge.cpp
QT := qt5

all: compile
$(PROJECT).pro: template add_include_path add_headers add_sources

template:
ifeq ($(QT),qt4)
	echo "TEMPLATE = app" > $(PROJECT).pro
	echo TARGET = >> $(PROJECT).pro
	echo "QT += declarative"
else
	echo "TEMPLATE = app" > $(PROJECT).pro
	echo "DEFINES += QT5" >> $(PROJECT).pro
	echo "QT += core" >> $(PROJECT).pro
	echo "QT += widgets" >> $(PROJECT).pro
	echo "QT += quick" >> $(PROJECT).pro
endif

add_depend_path:
	echo DEPENDPATH = $(addprefix $(MAIN_DIR)/, $(SUBDIRS)) >> $(PROJECT).pro

add_include_path:
	echo INCLUDEPATH += $(MAIN_DIR)/include >> $(PROJECT).pro

add_headers:
	echo HEADERS += $(addprefix $(MAIN_DIR)/include/, $(MAIN_SRCS:.cpp=.h)) >> $(PROJECT).pro

add_sources:
	echo SOURCES += $(addprefix $(MAIN_DIR)/src/, $(MAIN_SRCS)) >> $(PROJECT).pro

build.mak: $(PROJECT).pro
	qmake -o $@

compile: build.mak
	make -f build.mak

clean:
	rm -fr *.o $(PROJECT) $(PROJECT).app build.mak $(PROJECT).pro moc_*.cpp
