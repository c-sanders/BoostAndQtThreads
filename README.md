Basic C++ threading example using Boost and Qt.
===============================================

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

	# SUFFIXES : .hpp

	vpath %.hpp     ../../include
	

	# Suffix rules
	# ============

	# Pay particular attention to the following suffix rule.
	#
	# It tells make how to build Qt moc files from the corresponding .hpp files.

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
		@echo "CFLAGS               = ${CFLAGS}"
		@echo "LIBS                 = ${LIBS}"
		@echo "BOOST_ROOT           = ${BOOST_ROOT}"
		@echo "BOOST_CPPFLAGS       = ${BOOST_CPPFLAGS}"
		@echo "BOOST_LDFLAGS        = ${BOOST_LDFLAGS}"

The Python source code which is contained within this repository, implements a GIMP Plugin which can be used to scale and set the size, i.e. width and height (in
pixels), of one or more image files.

This GIMP Plugin - hereafter referred to simply as a Plugin, is implemented using the Python programming language and is available in 3 different variants. Each of
these three variants is implemented by a different Python function and in turn, these three Python functions are called;

* scale_and_set_size_interactive
* scale_and_set_size_file_noninteractive
* scale_and_set_size_list_noninteractive

Soon, each of these functions will be discussed on an individual basis. But before doing so, let's take a brief look at the relationship between
GIMP and Python.


GIMP and its relationship to Python.
------------------------------------

GIMP can be thought of as having two distinct relationships with Python;

+ Python code can be invoked from within GIMP, by way of GIMP's Python-Fu facility.
+ Python can be used to write Scripts or Plugins for GIMP, by way of the GIMP-Python Python module.


Python-Fu.
----------

Python-Fu is a facility provided by GIMP, which enables Python code to be executed from within GIMP.

For the curious reader, more information about Python-Fu can be found [here](https://docs.gimp.org/2.10/en/gimp-filters-python-fu.html).


GIMP-Python.
------------

The majority of GIMP's functionality is implemented using the C Programming Language. To be more precise, this functionality is implemented within a C
Library which is called libgimp. GIMP-Python is a Python module which provides a wrapper around this Library and in doing so, provides Python bindings
to the underlying C functionality.

For the curious reader, more information about GIMP-Python can be found [here](http://www.jamesh.id.au/software/pygimp/).


Python function : scale_and_set_size_interactive
------------------------------------------------

This Python function is responsible for implementing the first variant of the Plugin. This version of the Plugin is intended for use in an interactive manner.
It is discussed below in the section which is entitled;

> Invoking the GIMP Plugin Python functions from within GIMP.

This version of the Plugin is implemented by a Python function which is called **scale_and_set_size_interactive**.


Python function : scale_and_set_size_file_noninteractive
--------------------------------------------------------

This Python function is responsible for implementing the second variant of the Plugin. This version of the Plugin is intended for use in a non-interactive manner.

> Invoking the GIMP Plugins non-interactively from the command line. 


Invoking the GIMP Plugin Python functions from within GIMP.
-----------------------------------------------------------

It is possible to directly invoke Python functions from within GIMP. However, it does not appear to be possible to directly invoke Python Plugin functions
from within GIMP. When we state "directly invoking Python functions from within GIMP", we mean invoking Python functions from within the GIMP Python Console Panel.

Consider the following simple Python Plugin;

	#!/usr/bin/env python
	
	
	from gimpfu import register, main, PF_STRING
	
	
	# Define the function which is to be registered with GIMP as a Plugin.
	
	def displayMessage(
	
	  message
	) :
	
		print("Message = %s" % (message))
	
	
	# If GIMP finds this file while it is starting up, it will ask it file to identify itself. This is the
	# reason for the register function.
	#
	# Register the display_message function with GIMP's PDB (Procedure DataBase). If this operation is
	# successful, then the display_message function should be registered with GIMP as a Plugin.
	
	register(
		"displayMessage",      # The name of the command.
		"Display a message.",  # A brief description of the command.
		"Display a message.",  # Help message.
		"Foo Bar",             # Author.
		"Foo Bar",             # Copyright holder.
		"2020",                # Date.
		"Display a message",   # The way the script will be referred to in the menu.
		# "RGB*, GRAY*",       # Image mode
		"",                    # Create a new image, don't work on an existing one.
		[
			(PF_STRING, "message", "Message to display", "Hello, GIMP!"),
		],
		[],
		displayMessage,
		menu="<Image>/Image/Utilities/")
	
	
	# Invocation of the main function below, should in turn cause the gimp_env_init function to be
	# invoked.
	#
	# Apart from this, what else exactly does invoking the main function do? It may be responsible for
	# initialising the Plugin's arguments?
	
	main()

Let us assume that we have this source code stored in a Python source code file which is called;

> "/home/foo/.gimp-2.8/plug-ins/basic_plugin.py";

and that this file's permission bits are set to 755.

As can be seen from this source code, the Plugin itself is rather simple. It is composed of a single function called "displayMessage", which is registered with
GIMP by way of a function which is called "register". The "register" function itself is imported from GIMP by way of the;

	from * import *

statement towards the top of the source code file.

In order to try and directly invoke from within GIMP, the one and only function that this Plugin source code file defines, i.e. "displayMessage", first start up GIMP and then click;

  Filters > Python-Fu > Console

Doing this should cause a Python Console Panel - similar to the one shown immediately below, to be displayed.

![Test image](/images/Panel_Python-Fu.png "GIMP's Python-Fu Console Panel")

Next, from within the Python Console Panel, invoke the following two commands;

	>>> import sys
	>>> print("%s" % (sys.path))

The second command should display a list of those directories which Python will search for modules. If the directory which contains
the Python Script is not shown in this list, then invoke the following command;

	>>> sys.path.insert(0, <Name_of_dir_containing_Python_Script>)

This should prepend the directory which contains the Python Script, to the list of directories that Python searches for modules.

For example, in the case of the basic_plugin Plugin, you should execute the following command;

	>>> sys.path.insert(0, "/home/foo/.gimp-2.8/plug-ins")

Now you should only have to invoke the following two commands in order to get the Python Script to run from within GIMP.

	>>> import basic_plugin
	>>> display_message.displayMessage("Hello, GIMP!")

You should more than likely find that running the import command causes the GIMP Python Console Panel to disappear and that GIMP displays a Panel similar to the
following;

![Test image](/images/Panel_Message_Python-Console_crashed.png "GIMP Message Panel")

The description which is contained within this panel is not all that helpful for trying to figure out what has gone wrong. If you started GIMP from a command line,
terminal, or console, you might find that in addition to displaying this panel, GIMP may have also written out a message to the command line, terminal, or console
from which it was started. This message should state something like the following;

	(/usr/lib/gimp/2.0/plug-ins/python-console.py:17118): LibGimpBase-ERROR **: gimp_env_init() must only be called once!

This is a bit more informative, and it leads the author to believe that the invocation of the "main" function at the bottom of the source code file, is what is causing
the "gimp_env_init" function to be invoked.

One of the things that GIMP does as part of its startup routine, is to read in any Plugins which it finds in its Plugin Search path. During this process, it appears though GIMP must execute the "gimp_env_init" function
whilst it is loading any Plugins which it finds. Then, when we instruct the Python Console to try and import the Python source code file which contains the display_message Plugin,
the presence of the "main" function within this Plugin causes GIMP to try and execute the "gimp_env_init" function again. GIMP realises what it is being instructed to
do, and because it knows that the "gimp_env_init" function should only be invoked once - as we were informed of by the message, it aborts its attempt to run the display_message 
Plugin. This is what the author suspects results in the message being displayed.

If we go back to the Python source code file which implements the Plugin, and we edit it so as to comment out the line of source code which invokes the "main" function,
then we should hopefully prevent GIMP from executing it. If we then try and import the "display_message" Plugin again - using the same sequence of steps as earlier,
then we should be successful as the following image shows.

![Test image](/images/Panel_Python-Console_success.png "GIMP Python Console panel")

The problem however, with commenting out the "main" function, is that GIMP will no longer be able to load the source code in this file as a Plugin during the startup process.

> So to summarise the findings of this section, it is possible to directly invoke Python functions from within GIMP, but it is not possible to directly invoke Python Plugin
> functions from within GIMP. To be more precise, it is not possible to directly invoke from within GIMP, Python functions in source code files which contain
> an invocation of the Python "main" function.

Invoking the GIMP Plugins interactively from within GIMP.
---------------------------------------------------------

To invoke the GIMP Plugin interactively, start up GIMP and then use it to open the image which is to be operated on by the Plugin. Once this is done, select;

  Image > Craig's Utilities > Scale and set image size

Doing this should cause the following panel to be displayed. 

![Test image](/images/Panel.png "Panel displayed by the Image Overlay Plugin")


Invoking the GIMP Plugins non-interactively from the command line.
------------------------------------------------------------------

To invoke either one of the two non-interactive versions of the Plugin, i.e.;

> python-fu-scale-and-set-size-file-noninteractive
>
> or
>
> python-fu-scale-and-set-size-list-noninteractive

in a non-interactive manner, issue a command from the command line which is similar to either one
the following two commands;

	gimp --no-interface \
		 --verbose \
		 --console-messages \
		 --batch-interpreter="plug-in-script-fu-eval" \
		 --batch '(
		           python-fu-scale-and-set-size-file-noninteractive
		           RUN-NONINTERACTIVE
		           1920
		           1080
		           3
		           "/home/foo/file_list.txt"
		          )' \
		 --batch "(gimp-quit 1)"

or

	gimp --no-interface \
		 --verbose \
		 --console-messages \
		 --batch-interpreter="plug-in-script-fu-eval" \
		 --batch '(
		           python-fu-scale-and-set-size-list-noninteractive
		           RUN-NONINTERACTIVE
		           1920
		           1080
		           3
		           "/home/foo/file_list.txt"
		          )' \
		 --batch "(gimp-quit 1)"

> A quick note about the syntax of these two commands.
>
> The arguments to a batch sub-command should be placed within the batch sub-command's parentheses. These arguments seem to get passed directly to
> GIMP, therefore they should not contain any shell special or control characters. For example, if the arguments contained one or more instances of the "\\"
> character, then GIMP might not know how to interpret them, and this could cause an error such as;
>
> batch command experienced an execution error:
> Error: ( : 1) eval: unbound variable: \

**scale-and-set-size-file-noninteractive**

This version of the Plugin will operate on a list of files, where the list of files should itself be stored in a text file. This text file in turn should be passed as the
fifth and final argument to the Plugin. In the example invocation of the Plugin above, it is assumed that the file "/home/foo/file_list.txt" exists, and
that it contains the list of files.

The command which was just presented, might seem a little overwhelming. So to try and help explain what it is doing, here is the same command but with comments added.

	gimp --no-interface \                                                  # Instruct GIMP to operate without using its (graphical user) interface. This causes GIMP to execute in a non-interactive manner.
	     --verbose \                                                       # Instruct GIMP to operate in a verbose manner.
	     --console-messages \                                              # Instruct GIMP to process console messages.
	     --batch-interpreter="plug-in-script-fu-eval" \                    # Instruct GIMP to use Python-Fu to interpret the following batch sub-commands.
	     --batch '(                                                        # Start a batch sub-command.
	               python-fu-scale-and-set-size-file-noninteractive        # Name of the Plugin the batch sub-command should execute.
	               RUN-NONINTERACTIVE                                      # Instruct the Plugin to operate in a non-interactive manner.
	               1920                                                    # Desired width of the image.
	               1080                                                    # Desired height of the image.
	               3                                                       # Image interpolation method.
	               "/home/foo/file_list.txt"                               # Filename of the text file which contains the list of files to operate on.
	              )' \                                                     # End the current batch sub-command.
	     --batch '(gimp-quit 0)'                                           # Instruct GIMP to quit, and in doing so, return a value of 0 to the program which invoked it.

**scale-and-set-size-list-noninteractive**

This version of the Plugin will operate on a list of files, where the list of files should be passed to this Plugin via stdin.

Registering the Plugin with GIMP.
---------------------------------

The Plugin is implemented in Python by a function which is called "runPlugin_multiple_fromList".

Since this function is responsible for implementing the Plugin, it is this function which must therefore be registered with GIMP. As part of the registration
process, GIMP also needs to know some other information about the Plugin which is being registered, such as;

- a short description which is to be associated with the Plugin,
- a short Help message which is to be assocaited with the Plugin,
- whereabouts within its Menu system GIMP should place a menu entry for this Plugin,
- how the GUI Panel which is associated with the Plugin should be laid out.


How the Plugin is implemented.
------------------------------

	scale_and_set_size_file_noninteractive
	 |
	 |- scale_and_set_size_interactive
	     |
	     |- ScaleAndSetSizeObject Ctor
	     |
	     |- ScaleAndSetSizeObject.__run
	         |
	         |- ScaleAndSetSizeObject.computeResizingFactor
	         |
	         |- ScaleAndSetSizeObject.scale
	         |   |
	       	 |   |- pdb.gimp_image_scale_full
	         |
	         |- ScaleAndSetSizeObject.resizeAndCrop
	         |   |
	         |   |- pdb.gimp_image_resize
	         |   |
	         |   |- pdb.gimp_image_crop
	         |
	         |- ScaleAndSetSizeObject.offset
	         |   |
	         |   |- pdb.gimp_drawable_offset
	         |
	         |- ScaleAndSetSizeObject.save
	             |
	             |- pdb.gimp_image_flatten

