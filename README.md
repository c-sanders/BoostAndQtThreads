Basic C++ threading example using both the Boost and Qt threading libraries.
============================================================================

Introduction
------------

The main aim of this package is to attempt to illustrate the following concepts;

  - How to write a Makefile rule which is capable of building Qt moc files.

  - How to create threads in C++ using both the Boost and Qt threading libraries.

  - How to implement a new class which subclasses from a Qt class.


Configuring the package.
------------------------

+ The configure script.

This packge should be configured using the `configure` script that comes with it. One of the many configuration tasks that this script performs,
is to check for a valid installation of version 5 of the Qt library. It accomplishes this task by invoking a GNU Autoconf macro called `AX_HAVE_QT`. When invoked, this
macro will search for an instance of the Qt make command line utility called `qmake`. Usually, this utility is installed within the `bin` sub-directory of
the directory in which the Qt library is installed. If this macro finds a valid installation of version 5 of the Qt library, then it creates a 
variable called `QT_DIR`, the value of which will be set to the name of the directory in which the valid installation of version 5 of the Qt library is installed.
Keep this `QT_DIR` variable in mind, as it will be mentioned again in the next setion.

+ Invoking the configure script.

At the point in time the `configure` script in invoked, the directory which `qmake` resides in, must be present within the `PATH` environment variable.
If the user who is executing the `configure` script doesn't want to alter their `PATH` environment variable from how it is set within their shell environment, then they should pass an altered version of it in the command which is used to execute
the `configure` script. This altered version should contain the directory which the Qt moc command line utility resides in. An example command, showing
how to invoke the `configure` script, is shown below. It should be noted this command assumes that the directory which the Qt moc command line utility
resides in, isn't already listed within the user's `PATH` environment variable.

	> ./configure --with-boost=/home/foo/local/boost_1_74_0 PATH=/home/foo/Qt-5.15.1/bin:${PATH}

A user should not try and circumvent the `AX_HAVE_QT` macro by passing a value of `QT_DIR` in the previous command, instead of a value of `PATH`. That is, the
following command will not work;

	> ./configure --with-boost=/home/foo/local/boost_1_74_0 QT_DIR=/home/foo/Qt-5.15.1

The `AX_HAVE_QT` macro needs to discover where (if indeed anywhere), a valid installation of version 5 of the Qt library is installed and then set the value of the `QT_DIR`
variable accordingly - itself. A user of the `configure` script cannot circumvent this process by trying to set this variable themselves.


How to write a Makefile rule which is capable of building Qt moc files.
-----------------------------------------------------------------------

An example of a Makefile rule which is capable of building Qt moc files, is contained within the GNU Automake Makefile `./src/Makefile.am`.
The contents of this file are listed immediately below;

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

		@echo "Makefile     : ./src/moc/Makefile"
		@echo "Target       = $@"
		@echo "Prerequisite = $<"
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

The Makefile rule which is capable of building Qt moc files, is implemented as a suffix rule, and can be found in the section of the Makefile which is titled
"Suffix rules".

	.hpp.moc :

		@echo "Makefile     : ./src/moc/Makefile"
		@echo "Target       = $@"
		@echo "Prerequisite = $<"
		${MOC} ${boost_and_qt_threads_INCLUDES} $< -o $@
		destFile=$$(echo $@ | sed 's/^\(.*\)\.moc$$/\1.cpp/') && cp -vp $@ moc_$${destFile}

+ What it does.

This suffix rule tells the make utility - hereafter referred to simply as "make", how to build a Qt moc (`.moc`) file from the corresponding `.hpp` file. If make finds that a particular `.moc` file is out of date,
then it will use this rule to update it.

+ Ascertaining the name of the prerequisite file.

Once a particular target filename has been passed to this suffix rule, the next thing that make needs to do, is ascertain the name of the prerequisite
file which the target file depends upon. This task is delegated by make to the suffix rule. One problem with 
this however, is that suffix rules aren't all that powerful - or clever. When it comes to ascertaining the name of the prerequisite file, all this suffix rule does is 
look for a prerequisite file whose filename is the same as the target filename, but with a filename extension of `.hpp` rather than `.moc`. For example, if
this suffix rule was passed a target filename of `TestClass.moc`, then all it would do is simply ascertain that it needs to look for a prerequisite file whose
name is `TestClass.hpp`.

+ Locating the prerequisite file.

Once the suffix rule has established the name of the prerequisite file, the next step is to locate it. The task of specifying where make should look for this
prerequisite file, is handled by one of the vpath directives which is defined within in the Makefile - in this particular case, the `vpath %.hpp` directive. This directive should list one of more directories
for make to search through whenever it is required to go looking for any `.hpp` files.
If the prerequisite file is found, and it is found to be newer than the target file - or if the target file doesn't yet exist, then this suffix rule will be
invoked (using the target and prerequisite filenames just discussed) in order to update the target file.

+ Problem with this suffix rule and a workaround.

There is a problem with this Makefile, and that is that it doesn't tell make how to build `.cpp` suffixed moc files from `.hpp` files. To help compensate for this,
once the suffix rule has built its `.moc` target file, it then makes a copy of it. This copy has a similar name to the target file, except that the filename is prefixed by `moc_` and 
the filename extension is changed from `.moc` to `.cpp`. For example;

	TestClass.moc --> moc_TestClass.cpp

Remember, these two files are the same file and are effectivey created at the same time. Furthermore, the file `TestClass.hpp` is the prerequisite file for both of them.

It is worth pointing out that the `moc_*.cpp` files which are built by this suffix rule, are treated as prerequisites by the Makefile `./src/Makefile.am`'. This
then raises the question of why these files aren't simply generated from a corresponding .hpp prerequisite file? For example;

	TestClass.hpp --> moc_TestClass.cpp

Taking into account what was stated earlier, we can see that make would ascertain that the prerequisite file for this target should be `moc_TestClass.hpp`.
make would then go searching for a prerequisite file with this name, but would be unable to find it. This is one of the reasons why suffix rules were described earlier
as not being all that powerful - or clever.

+ Can a pattern rule be used instead?

This now raises the question of why a pattern rule can't be used instead. Afterall - and as was mentioned earlier, they are more powerful and more clever than sffix rules.
Therefore, couldn't the suffix rule from above be replaced with a pattern rule such as the following;

	%.hpp : moc_%.cpp
	
		@echo "Makefile     : ./src/moc/Makefile"
		@echo "Target       = $@"
		@echo "Prerequisite = $<"
		${MOC} ${boost_and_qt_threads_INCLUDES} $< -o $@

As can be seen, this rule is both shorter and simpler. Furthermore, it doesn't need to copy the resulting file. This pattern rule will work, however the
GNU Autotools project which it is a part of, needs to be configured correctly so as to allow the project to use pattern rules.

The previous paragraph implies that there is problem using pattern rules in GNU Autotools projects - and this is indeed the case. The problem with pattern rules is,
they are GNU extension to Makefiles, and as a consequence, the GNU Autotools (Automake in particular in this case), might complain when they come across a pattern
rule while processing a `Makefile.am`. In response to seeing one, the Autotools might generate a message which is similar to the following;

	automake: warnings are treated as errors
	src/Makefile.am:xxx: warning: '%'-style pattern rules are a GNU make extension
	autoreconf: automake failed with exit status: 1

+ Configuring a GNU Autotools project to use pattern rules.

It was stated above that the GNU Autotools might generate a message similar to this. The word 'might' is used, because it depends upon how the `AM_INIT_AUTOMAKE`
macro is invoked from within a GNU Autotools project's `configure.ac` file. If it is invoked as follows, then the GNU Autotools should generate the warning/error
message shown above.

	AM_INIT_AUTOMAKE([-Wall -Werror foreign])



