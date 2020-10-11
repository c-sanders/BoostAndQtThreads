Basic C++ threading example using Boost and Qt.
===============================================

Introduction
------------

The main aim of this package is to attempt to illustrate the following concepts;

  - How to write Makefiles so that they can build Qt moc files.

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

The .hpp.moc suffix rule.
-------------------------

In particular, pay attention to the one and only suffix rule in this Makefile; that is;

	.hpp.moc :

		@echo "Makefile   : ./src/moc/Makefile"
		@echo "Target     = $@"
		@echo "Dependency = $<"
		${MOC} ${boost_and_qt_threads_INCLUDES} $< -o $@
		destFile=$$(echo $@ | sed 's/^\(.*\)\.moc$$/\1.cpp/') && cp -vp $@ moc_$${destFile}

+ What it does.

This suffix rule tells make how to build a Qt moc (`.moc`) file from the corresponding `.hpp` file. If make finds that a particular `.moc` file is out of date,
then it will use this rule to update it.

+ Ascertaining the name of dependency file.

Once a particular target file has been passed to this suffix rule, the next thing that the make utility needs to do, is to ascertain the name of the dependency
file which the target file depends upon. This task of ascertaining the name of the dependency file, is delegated by the make utility to the suffix rule. One problem with 
this however, is that suffix rules aren't all that powerful - or clever. All this suffix rule does is look for a dependency file whose filename is the same as the target filename, but with
a filename extension of `.hpp` rather than `.moc`. For example, if this suffix rule was passed a target filename of `TestClass.moc`, then it would simply look for
a dependency file whose name is `TestClass.hpp`.

+ Locating the dependency file.

Once the suffix rule has established the name of the dependency file, the next step is to locate it. The task of specifying where the make utility should look for this
dependency file, is handled by one of the vpath directives - in this particular case, the `vpath %.hpp` directive. This directive should list one of more directories
for the make utility to search through whenever it is required to go looking for any `.hpp` files.
If the dependency file is found, and it is found to be newer than the target file - or if the target file doesn't yet exist, then this suffix rule will be
invoked (using the target and dependency files just discussed) in order to update the target file.

+ Problem with this suffix rule and a workaround.

A problem with this Makefile, is that it doesn't tell the make utility how to build `.cpp` suffixed moc files from `.hpp` files. To help compensate for this,
the suffix rule makes a copy of the target `.moc` file. This copy has a similar name to the target file, except that the filename is prefixed by `moc_` and 
the filename extension is changed from `.moc` to `.cpp`. For example;

	TestClass.moc --> moc_TestClass.cpp

Remember, these two files are the same file and are effectivey created at the same time. Furthermore, the file `TestClass.hpp` is the dependency file for both of them.

File `moc_TestClass.cpp` is itself declared as a build dependency in `./src/Makefile.am`. This then raises the question as to why moc_TestClass.cpp isn't simply
generated from a corresponding .hpp dependency file? That is;

	TestClass.hpp --> moc_TestClass.cpp

As per the discussion earlier, the make utility would ascertain that the dependency file for this target should be 

The reason for this is because when make goes looking for consults the directories listed in the appropriate vpath, it will never find a file called;

	moc_TestClass.hpp

Furthermore, and as far as the author is aware, suffix rules aren't powerful enough to allow us to specify such a scenario. Pattern rules can do this, but they are a
GNU extension, and as a result, the GNU Autptools will complain about them.




