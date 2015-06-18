#############################################################################
# Makefile for building: qml-test.app/Contents/MacOS/qml-test
# Generated by qmake (3.0) (Qt 5.4.1)
# Project:  qml-test.pro
# Template: app
# Command: /Users/remurd/Qt/5.4/clang_64/bin/qmake -o build.mak qml-test.pro
#############################################################################

MAKEFILE      = build.mak

####### Compiler, tools and options

CC            = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
CXX           = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++
DEFINES       = -DQT5 -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_QUICK_LIB -DQT_GUI_LIB -DQT_QML_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -O2 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk -mmacosx-version-min=10.7 -Wall -W -fPIE $(DEFINES)
CXXFLAGS      = -pipe -O2 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk -mmacosx-version-min=10.7 -Wall -W -fPIE $(DEFINES)
INCPATH       = -I. -Iinclude -I/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers -I/Users/remurd/Qt/5.4/clang_64/lib/QtQuick.framework/Versions/5/Headers -I/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers -I/Users/remurd/Qt/5.4/clang_64/lib/QtQml.framework/Versions/5/Headers -I/Users/remurd/Qt/5.4/clang_64/lib/QtNetwork.framework/Versions/5/Headers -I/Users/remurd/Qt/5.4/clang_64/lib/QtCore.framework/Versions/5/Headers -I. -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/System/Library/Frameworks/AGL.framework/Headers -I/Users/remurd/Qt/5.4/clang_64/mkspecs/macx-clang -F/Users/remurd/Qt/5.4/clang_64/lib
QMAKE         = /Users/remurd/Qt/5.4/clang_64/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = $(COPY_FILE)
INSTALL_PROGRAM = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = qml-test1.0.0
DISTDIR = /Volumes/DATA/ramdisks/dicom/qml-test/.tmp/qml-test1.0.0
LINK          = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++
LFLAGS        = -headerpad_max_install_names -Wl,-syslibroot,/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk -mmacosx-version-min=10.7 -Wl,-rpath,/Users/remurd/Qt/5.4/clang_64/lib
LIBS          = $(SUBLIBS) -F/Users/remurd/Qt/5.4/clang_64/lib -framework QtWidgets -framework QtGui -framework QtCore -framework DiskArbitration -framework IOKit -framework QtQuick -framework QtQml -framework QtNetwork -framework OpenGL -framework AGL 
AR            = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ar cq
RANLIB        = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib -s
SED           = sed
STRIP         = 

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = src/test.cpp \
		src/Gauge.cpp moc_Gauge.cpp
OBJECTS       = test.o \
		Gauge.o \
		moc_Gauge.o
DIST          = /Users/remurd/Qt/5.4/clang_64/mkspecs/features/spec_pre.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/qdevice.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/device_config.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/shell-unix.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/unix.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/mac.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/macx.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/gcc-base.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/gcc-base-mac.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/clang.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/clang-mac.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/qconfig.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_bluetooth.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_bluetooth_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_clucene_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_concurrent.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_concurrent_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_core.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_core_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_dbus.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_dbus_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_declarative.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_declarative_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_designer.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_designer_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_designercomponents_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_enginio.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_enginio_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_gui.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_gui_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_help.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_help_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_location.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_location_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_macextras.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_macextras_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_multimedia.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_multimedia_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_multimediawidgets.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_multimediawidgets_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_network.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_network_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_nfc.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_nfc_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_opengl.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_opengl_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_openglextensions.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_positioning.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_positioning_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_printsupport.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_printsupport_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qml.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qml_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qmltest.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qmltest_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quick.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quick_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quickparticles_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quickwidgets.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_script.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_script_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_scripttools.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_scripttools_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_sensors.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_sensors_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_serialport.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_serialport_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_sql.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_sql_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_svg.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_svg_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_testlib.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_testlib_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_uitools.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_uitools_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webchannel.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webchannel_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webkit.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webkit_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webkitwidgets.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webkitwidgets_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_websockets.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_websockets_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_widgets.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_widgets_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_xml.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_xml_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_xmlpatterns.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/qt_functions.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/qt_config.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/macx-clang/qmake.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/exclusive_builds.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/default_pre.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/default_pre.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/resolve_config.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/default_post.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/sdk.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/default_post.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/objective_c.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/warn_on.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/qt.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/resources.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/moc.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/unix/opengl.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/uic.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/unix/thread.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/rez.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/testcase_targets.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/exceptions.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/yacc.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/lex.prf \
		qml-test.pro include/test.h \
		include/Gauge.h src/test.cpp \
		src/Gauge.cpp
QMAKE_TARGET  = qml-test
DESTDIR       = #avoid trailing-slash linebreak
TARGET        = qml-test.app/Contents/MacOS/qml-test

####### Custom Compiler Variables
QMAKE_COMP_QMAKE_OBJECTIVE_CFLAGS = -pipe \
		-O2 \
		-isysroot \
		/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk \
		-mmacosx-version-min=10.7 \
		-Wall \
		-W



first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

$(TARGET):  $(OBJECTS)  
	@test -d qml-test.app/Contents/MacOS/ || mkdir -p qml-test.app/Contents/MacOS/
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

build.mak: qml-test.pro /Users/remurd/Qt/5.4/clang_64/mkspecs/macx-clang/qmake.conf /Users/remurd/Qt/5.4/clang_64/mkspecs/features/spec_pre.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/qdevice.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/device_config.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/shell-unix.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/unix.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/mac.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/macx.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/gcc-base.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/gcc-base-mac.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/clang.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/common/clang-mac.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/qconfig.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_bluetooth.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_bluetooth_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_clucene_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_concurrent.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_concurrent_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_core.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_core_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_dbus.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_dbus_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_declarative.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_declarative_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_designer.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_designer_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_designercomponents_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_enginio.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_enginio_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_gui.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_gui_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_help.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_help_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_location.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_location_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_macextras.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_macextras_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_multimedia.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_multimedia_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_multimediawidgets.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_multimediawidgets_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_network.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_network_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_nfc.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_nfc_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_opengl.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_opengl_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_openglextensions.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_positioning.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_positioning_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_printsupport.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_printsupport_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qml.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qml_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qmltest.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qmltest_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quick.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quick_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quickparticles_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quickwidgets.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_script.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_script_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_scripttools.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_scripttools_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_sensors.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_sensors_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_serialport.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_serialport_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_sql.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_sql_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_svg.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_svg_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_testlib.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_testlib_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_uitools.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_uitools_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webchannel.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webchannel_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webkit.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webkit_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webkitwidgets.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webkitwidgets_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_websockets.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_websockets_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_widgets.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_widgets_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_xml.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_xml_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_xmlpatterns.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/qt_functions.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/qt_config.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/macx-clang/qmake.conf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/exclusive_builds.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/default_pre.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/default_pre.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/resolve_config.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/default_post.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/sdk.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/default_post.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/objective_c.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/warn_on.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/qt.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/resources.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/moc.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/unix/opengl.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/uic.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/unix/thread.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/rez.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/testcase_targets.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/exceptions.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/yacc.prf \
		/Users/remurd/Qt/5.4/clang_64/mkspecs/features/lex.prf \
		qml-test.pro \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/QtWidgets.prl \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/QtGui.prl \
		/Users/remurd/Qt/5.4/clang_64/lib/QtCore.framework/QtCore.prl \
		/Users/remurd/Qt/5.4/clang_64/lib/QtQuick.framework/QtQuick.prl \
		/Users/remurd/Qt/5.4/clang_64/lib/QtQml.framework/QtQml.prl \
		/Users/remurd/Qt/5.4/clang_64/lib/QtNetwork.framework/QtNetwork.prl
	$(QMAKE) -o build.mak qml-test.pro
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/spec_pre.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/qdevice.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/device_config.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/common/shell-unix.conf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/common/unix.conf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/common/mac.conf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/common/macx.conf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/common/gcc-base.conf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/common/gcc-base-mac.conf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/common/clang.conf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/common/clang-mac.conf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/qconfig.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_bluetooth.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_bluetooth_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_bootstrap_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_clucene_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_concurrent.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_concurrent_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_core.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_core_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_dbus.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_dbus_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_declarative.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_declarative_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_designer.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_designer_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_designercomponents_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_enginio.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_enginio_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_gui.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_gui_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_help.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_help_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_location.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_location_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_macextras.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_macextras_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_multimedia.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_multimedia_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_multimediawidgets.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_multimediawidgets_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_network.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_network_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_nfc.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_nfc_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_opengl.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_opengl_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_openglextensions.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_openglextensions_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_platformsupport_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_positioning.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_positioning_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_printsupport.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_printsupport_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qml.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qml_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qmldevtools_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qmltest.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qmltest_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quick.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quick_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quickparticles_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quickwidgets.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_quickwidgets_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_script.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_script_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_scripttools.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_scripttools_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_sensors.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_sensors_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_serialport.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_serialport_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_sql.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_sql_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_svg.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_svg_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_testlib.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_testlib_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_uitools.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_uitools_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webchannel.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webchannel_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webkit.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webkit_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webkitwidgets.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_webkitwidgets_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_websockets.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_websockets_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_widgets.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_widgets_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_xml.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_xml_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_xmlpatterns.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/modules/qt_lib_xmlpatterns_private.pri:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/qt_functions.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/qt_config.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/macx-clang/qmake.conf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/spec_post.prf:
.qmake.stash:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/exclusive_builds.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/default_pre.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/default_pre.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/resolve_config.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/default_post.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/sdk.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/default_post.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/objective_c.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/warn_on.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/qt.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/resources.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/moc.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/unix/opengl.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/uic.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/unix/thread.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/mac/rez.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/testcase_targets.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/exceptions.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/yacc.prf:
/Users/remurd/Qt/5.4/clang_64/mkspecs/features/lex.prf:
qml-test.pro:
/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/QtWidgets.prl:
/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/QtGui.prl:
/Users/remurd/Qt/5.4/clang_64/lib/QtCore.framework/QtCore.prl:
/Users/remurd/Qt/5.4/clang_64/lib/QtQuick.framework/QtQuick.prl:
/Users/remurd/Qt/5.4/clang_64/lib/QtQml.framework/QtQml.prl:
/Users/remurd/Qt/5.4/clang_64/lib/QtNetwork.framework/QtNetwork.prl:
qmake: FORCE
	@$(QMAKE) -o build.mak qml-test.pro

qmake_all: FORCE

qml-test.app/Contents/PkgInfo: 
	@test -d qml-test.app/Contents || mkdir -p qml-test.app/Contents
	@$(DEL_FILE) qml-test.app/Contents/PkgInfo
	@echo "APPL????" >qml-test.app/Contents/PkgInfo
qml-test.app/Contents/Resources/empty.lproj: 
	@test -d qml-test.app/Contents/Resources || mkdir -p qml-test.app/Contents/Resources
	@touch qml-test.app/Contents/Resources/empty.lproj
	
qml-test.app/Contents/Info.plist: 
	@test -d qml-test.app/Contents || mkdir -p qml-test.app/Contents
	@$(DEL_FILE) qml-test.app/Contents/Info.plist
	@sed -e "s,@SHORT_VERSION@,1.0,g" -e "s,@FULL_VERSION@,1.0.0,g" -e "s,@TYPEINFO@,????,g" -e "s,@BUNDLEIDENTIFIER@,com.yourcompany.qml-test,g" -e "s,@ICON@,,g" -e "s,@EXECUTABLE@,qml-test,g" -e "s,@TYPEINFO@,????,g" /Users/remurd/Qt/5.4/clang_64/mkspecs/macx-clang/Info.plist.app >qml-test.app/Contents/Info.plist

all: build.mak \
		qml-test.app/Contents/PkgInfo \
		qml-test.app/Contents/Resources/empty.lproj \
		qml-test.app/Contents/Info.plist $(TARGET)

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents include/test.h include/Gauge.h $(DISTDIR)/
	$(COPY_FILE) --parents src/test.cpp src/Gauge.cpp $(DISTDIR)/


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) -r qml-test.app
	-$(DEL_FILE) .qmake.stash
	-$(DEL_FILE) build.mak


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

check: first

compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_header_make_all: moc_Gauge.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_Gauge.cpp
moc_Gauge.cpp: /Users/remurd/Qt/5.4/clang_64/lib/QtQuick.framework/Versions/5/Headers/QQuickPaintedItem \
		/Users/remurd/Qt/5.4/clang_64/lib/QtQuick.framework/Versions/5/Headers/qquickpainteditem.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/QPainter \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/qpainter.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/QWidget \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/qwidget.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/QColor \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/qcolor.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/QStyleOptionGraphicsItem \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/qstyleoption.h \
		include/Gauge.h
	/Users/remurd/Qt/5.4/clang_64/bin/moc $(DEFINES) -D__APPLE__ -D__GNUC__=4 -I/Users/remurd/Qt/5.4/clang_64/mkspecs/macx-clang -I/Volumes/DATA/ramdisks/dicom/qml-test -I/Volumes/DATA/ramdisks/dicom/qml-test/include -I/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Headers -I/Users/remurd/Qt/5.4/clang_64/lib/QtQuick.framework/Headers -I/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Headers -I/Users/remurd/Qt/5.4/clang_64/lib/QtQml.framework/Headers -I/Users/remurd/Qt/5.4/clang_64/lib/QtNetwork.framework/Headers -I/Users/remurd/Qt/5.4/clang_64/lib/QtCore.framework/Headers -F/Users/remurd/Qt/5.4/clang_64/lib include/Gauge.h -o moc_Gauge.cpp

compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

test.o: src/test.cpp /Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/QGuiApplication \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/qguiapplication.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtQuick.framework/Versions/5/Headers/QQuickView \
		/Users/remurd/Qt/5.4/clang_64/lib/QtQuick.framework/Versions/5/Headers/qquickview.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtQml.framework/Versions/5/Headers/QQmlEngine \
		/Users/remurd/Qt/5.4/clang_64/lib/QtQml.framework/Versions/5/Headers/qqmlengine.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/QApplication \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/qapplication.h \
		include/Gauge.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtQuick.framework/Versions/5/Headers/QQuickPaintedItem \
		/Users/remurd/Qt/5.4/clang_64/lib/QtQuick.framework/Versions/5/Headers/qquickpainteditem.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/QPainter \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/qpainter.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/QWidget \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/qwidget.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/QColor \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/qcolor.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/QStyleOptionGraphicsItem \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/qstyleoption.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o test.o src/test.cpp

Gauge.o: src/Gauge.cpp include/Gauge.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtQuick.framework/Versions/5/Headers/QQuickPaintedItem \
		/Users/remurd/Qt/5.4/clang_64/lib/QtQuick.framework/Versions/5/Headers/qquickpainteditem.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/QPainter \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/qpainter.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/QWidget \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/qwidget.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/QColor \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/qcolor.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/QStyleOptionGraphicsItem \
		/Users/remurd/Qt/5.4/clang_64/lib/QtWidgets.framework/Versions/5/Headers/qstyleoption.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/QPen \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/qpen.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/QBrush \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/qbrush.h \
		/Users/remurd/Qt/5.4/clang_64/lib/QtGui.framework/Versions/5/Headers/QLinearGradient \
		/Users/remurd/Qt/5.4/clang_64/lib/QtCore.framework/Versions/5/Headers/QRectF \
		/Users/remurd/Qt/5.4/clang_64/lib/QtCore.framework/Versions/5/Headers/qrect.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Gauge.o src/Gauge.cpp

moc_Gauge.o: moc_Gauge.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Gauge.o moc_Gauge.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
