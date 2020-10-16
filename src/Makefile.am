SUBDIRS                   = moc

# ACLOCAL_AMFLAGS(-I m4)


# Binary
# ======

bin_PROGRAMS              = boost_and_qt_threads


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

boost_and_qt_threads_INCLUDES         = -I${top_srcdir}/include -I${QT_DIR}/../include

boost_and_qt_threads_MOC_HEADER_FILES = TestClass.hpp

boost_and_qt_threads_MOC_FILES        = TestClass.moc

boost_and_qt_threads_MOC_CPP_FILES    = moc_TestClass.cpp

boost_and_qt_threads_SOURCES          = main.cpp \
                                        TestClass.cpp \
                                        ${boost_and_qt_threads_MOC_CPP_FILES}

boost_and_qt_threads_CPPFLAGS         = ${boost_and_qt_threads_INCLUDES} \
                                        ${BOOST_CPPFLAGS}

# boost_and_qt_threads_CXXFLAGS         = -std=c++11 \
#                                         -fPIC

boost_and_qt_threads_CXXFLAGS         = ${QT_CXXFLAGS}

boost_and_qt_threads_LDFLAGS          = ${BOOST_LDFLAGS} \
                                        -L/home/craig/local/source/boost_1_74_0/stage/lib

#                                         -L/usr/lib/x86_64-linux-gnu

boost_and_qt_threads_LDADD            = ${QT_LIBS} \
                                        -lboost_thread \
                                        -lpthread


SUFFIXES : .hpp

vpath %.hpp     ../include
# vpath %.moc     ./moc
# vpath moc_%.cpp ./moc


.PHONY : moc
moc :

	@echo "Makefile   : ./src/Makefile"
	@echo "Target     = $@"
	${MAKE} -C ./moc


# Pattern rules
# =============

moc_%.cpp : %.hpp

	@echo "Makefile   : ./src/Makefile"
	@echo "Target     = $@"
	@echo "Dependency = $<"
	${QT_MOC} ${boost_and_qt_threads_INCLUDES} $< -o $@


.PHONY: displaySettings
displaySettings:

	@echo "srcdir               = ${srcdir}"
	@echo "abs_srcdir           = ${abs_srcdir}"
	@echo "top_srcdir           = ${top_srcdir}"
	@echo "builddir             = ${builddir}"

