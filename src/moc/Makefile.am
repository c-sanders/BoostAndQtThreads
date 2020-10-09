# ACLOCAL_AMFLAGS(-I m4)


# Binary
# ======

# bin_PROGRAMS              = boost_and_qt_threads


# Qt5 library
# ===========

QT5_INCLUDE_DIR           = -I/usr/local/Qt-5.15.1/include/

QT5_LIB_DIR               = -L/usr/local/Qt-5.15.1/lib/

QT5_LIBS                  = -lQt5Core -lQt5Gui -lQt5Widgets

# The -std=c++11 Compiler option is required in order;
#
#   - to use the nullptr keyword
#   - to use the noexcept keyword 


# Binary
# ======
#
# Qt5 needs -fPIC

boost_and_qt_threads_INCLUDES         = -I${top_srcdir}/include ${QT5_INCLUDE_DIR}

# boost_and_qt_threads_MOC_HEADER_FILES = TestClass.hpp

boost_and_qt_threads_MOC_FILES        = TestClass.moc

# boost_and_qt_threads_MOC_CPP_FILES    = moc_TestClass.cpp

# boost_and_qt_threads_SOURCES          = main.cpp \
#                                         TestClass.cpp \
#                                         ${boost_and_qt_threads_MOC_CPP_FILES}

# boost_and_qt_threads_CPPFLAGS         = ${boost_and_qt_threads_INCLUDES} \
#                                         ${BOOST_CPPFLAGS}

# boost_and_qt_threads_CXXFLAGS         = -std=c++11 \
#                                         -fPIC

# boost_and_qt_threads_LDFLAGS          = ${QT5_LIB_DIR} \
#                                         ${OPENGL_LIB_DIR} \
#                                         ${BOOST_LDFLAGS} \
#                                         -L/home/craig/local/source/boost_1_74_0/stage/lib \
#                                         -L/usr/lib/x86_64-linux-gnu

# boost_and_qt_threads_LDADD            = ${QT5_LIBS} \
#                                         ${OPENGL_LIBS} \
#                                         -lboost_thread \
#                                         -lpthread


MOC = /usr/local/Qt-5.15.1/bin/moc


SUFFIXES : .hpp

vpath %.hpp     ../../include
# vpath moc_%.cpp ./moc


all : moc


moc : ${boost_and_qt_threads_MOC_FILES}


# ${MOC} ${boost_and_qt_threads_INCLUDES} $< -o ./moc/moc_$@
	

# The following rule works.
#

# .hpp.cpp :

#	/usr/local/Qt-5.15.1/bin/moc ${boost_and_qt_threads_INCLUDES} $< -o ./moc/$@


# HelloWorldWindow.hpp -> HelloWorldWindow.moc -> moc_HelloWorldWindow.cpp
#
# Target - ultimate     : moc_HelloWorldWindow.cpp
# Target - intermediate : HelloWorldWindow.moc
# Prerequisite          : HelloWorldWindow.hpp
#
# Problem : How to convert intermediate target name into ultimate target name?
#
#   HelloWorldWindow.moc -> moc_HelloWorldWindow.cpp
#
# sed 's/^\(.*\)\.moc$/moc_\1.cpp/'
#
#	cp -vp $@ $$(echo $@ | sed 's/^\(.*\)\.moc$$/moc_\1.cpp/')
#
# Why doesn't invocation of the following;
#
#   make moc/HelloWorldWindow.moc
#
# cause make to match it to the .hpp.moc suffix rule?
#
# vpath directives are used by make to search for target files, so this can't be causing the
# problem - see the following for confirmation;
#
#   https://www.gnu.org/software/make/manual/html_node/General-Search.html
#
# My suspicion is that if the target file doesn't yet exist in the moc subdirectory, then the make
# vpath mechanism won't be able to correctly ascertain the location or status of the target file.
# This in turn, will cause make to complain, with a message which is similar to the following;
#
#   make: *** No rule to make target 'moc/HelloWorldWindow.moc'.  Stop.
#
# How to overcome this? make doesn't complain in the same way if the following command is invoked;
#
#   make HelloWorldWindow.moc
#
# even if HelloWorldWindow.moc doesn't exist in the current directory. Why is this so?
#
# Further thoughts
# ================
#
# If initially, HelloWorldWindow.moc doesn't exist, and I just invoke;
#
#   make HelloWorldWindow.moc
#
# then it will build this file in the moc directory. If I don't touch this file's prerequisite and
# then I invoke the same make command again, then make will tell me;
#
#   make: './moc/HelloWorldWindow.moc' is up to date.
#
# Interesting.
#
# destFile=$$(echo $@ | sed 's/^\(.*\)\.cpp$$/moc_\1.cpp/') && cp -vp $@ $${destFile}

.hpp.moc :

	@echo "Makefile   : ./src/moc/Makefile"
	@echo "Target     = $@"
	@echo "Dependency = $<"
	${MOC} ${boost_and_qt_threads_INCLUDES} $< -o $@
	destFile=$$(echo $@ | sed 's/^\(.*\)\.moc$$/\1.cpp/') && cp -vp $@ moc_$${destFile}


# When it comes time for make to process TestClass.cpp, make incorrectly assumes that TestClass.cpp
# depends on TestClass.moc. Due to this incorrect assumption, it will notice that TestClass.moc is
# newer than TestClass.cpp, and as a result it will update TestClass.cpp using the following rule.
# The trouble is, this rule will overwrite the moc_TestClass.cpp file with the TestClass.cpp file;
# however, this is not what is desired!

# .moc.cpp :
#
# 	@echo "Target     = $@"
# 	@echo "Dependency = $<"
# 	destFile=$$(echo $@ | sed 's/^\(.*\)\.moc$$/\1.cpp/') && cp -vp $@ moc_$${destFile}	


.PHONY: displaySettings
displaySettings:

	@echo "srcdir               = ${srcdir}"
	@echo "abs_srcdir           = ${abs_srcdir}"
	@echo "top_srcdir           = ${top_srcdir}"
	@echo "builddir             = ${builddir}"
	@echo "CFLAGS               = ${CFLAGS}"
	@echo "LIBS                 = ${LIBS}"
	@echo "BOOST_ROOT           = ${BOOST_ROOT}"
	@echo "BOOST_CPPFLAGS       = ${BOOST_CPPFLAGS}"
	@echo "BOOST_LDFLAGS        = ${BOOST_LDFLAGS}"
