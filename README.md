Basic C++ threading example using Boost and Qt.
===============================================

Introduction
------------

The main aim of this package is to attempt to illustrate the following concepts;

  - How to write Makefiles so that the can build Qt moc files.

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

In particular, pay attention to the one and only suffix rule in this Makefile; that is;

	.hpp.moc :

		@echo "Makefile   : ./src/moc/Makefile"
		@echo "Target     = $@"
		@echo "Dependency = $<"
		${MOC} ${boost_and_qt_threads_INCLUDES} $< -o $@
		destFile=$$(echo $@ | sed 's/^\(.*\)\.moc$$/\1.cpp/') && cp -vp $@ moc_$${destFile}

This suffix rule tells make how to build a Qt moc (.moc) files from the corresponding .hpp file. If make finds that a particular .moc file is out of date,
then it will use this rule to update it.

When a particular target file is passed to this rule, the first thing the make utility needs to do, is to work out which file is the dependency for the target
file. It does this by consulting the relevant vpath directive, i.e. ../../include in this case. If the dependency file is found to be newer than the target
file - or if the target file doesn't yet exist, then this rule will be invoked in order to update the target file.

make doesn't know how to compile .moc files, so once the .moc file has been built, a copy is then made of it - but with a moc_ filename prefix and a .cpp
filename extension instead of a .moc filename extension. For example;

	TestClass.moc -- becomes --> moc_TestClass.cpp

These two files are effectively created at the same time.
