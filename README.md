Basic C++ threading example using Boost and Qt.
===============================================

Introduction
------------

This package attempts to illustrate the following concepts;

  - How Makefiles can be written in order to build Qt moc files.

  - How to create threads in C++ using both the Boost and Qt libraries.

  - How to implement a new class which subclasses from a Qt class.


How Makefiles can be written in order to build Qt moc files.
------------------------------------------------------------

Of interest is the file ./src/moc/Makefile.am which is listed below;

	# Qt5 library
	# ===========

	QT5_INCLUDE_DIR = -I/usr/local/Qt-5.15.1/include/

	QT5_LIB_DIR     = -L/usr/local/Qt-5.15.1/lib/

	QT5_LIBS        = -lQt5Core -lQt5Gui -lQt5Widgets


	# Miscellaneous
	# =============

	INCLUDE_DIRS    = -I${top_srcdir}/include ${QT5_INCLUDE_DIR}

	MOC_FILES       = TestClass.moc


	# Utilities
	# =========

	# The location of the Qt Meta Object Compiler (moc) which should be used to build the moc files.

	MOC = /usr/local/Qt-5.15.1/bin/moc


	# Search paths
	# ============

	vpath %.hpp     ../../include


	# Suffix rules
	# ============

	.hpp.moc :

		@echo "Makefile   : ./src/moc/Makefile"
		@echo "Target     = $@"
		@echo "Dependency = $<"
		${MOC} ${boost_and_qt_threads_INCLUDES} $< -o $@
		destFile=$$(echo $@ | sed 's/^\(.*\)\.moc$$/\1.cpp/') && cp -vp $@ moc_$${destFile}


	# Targets
	# =======

	all : moc


	moc : ${boost_and_qt_threads_MOC_FILES}


	.PHONY : displaySettings
	displaySettings :

		@echo "srcdir               = ${srcdir}"
		@echo "abs_srcdir           = ${abs_srcdir}"
		@echo "top_srcdir           = ${top_srcdir}"
		@echo "builddir             = ${builddir}"

In particular, pay attention to the one and only suffix rule in this Makefile - that is;

	.hpp.moc :

		@echo "Makefile   : ./src/moc/Makefile"
		@echo "Target     = $@"
		@echo "Dependency = $<"
		${MOC} ${boost_and_qt_threads_INCLUDES} $< -o $@
		destFile=$$(echo $@ | sed 's/^\(.*\)\.moc$$/\1.cpp/') && cp -vp $@ moc_$${destFile}

This suffix rule tells make how to build Qt moc (.moc) files from the corresponding .hpp files. If a particular .moc file is found by make, to be out of
date, then it will use this rule to update it.
#
# make will use the relevant vpath directive to find the correct dependency for this rule.
