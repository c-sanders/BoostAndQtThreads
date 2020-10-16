#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.


# Invoke the necessary Autotools initialisation macros.
# -----------------------------------------------------

AC_PREREQ([2.69])

AC_INIT(
	[BoostAndQtThreads],
	[0.1],
	[craig@gravitas-toolworks.com])

# Specify the location into which the auxiliary build tools
# should be placed, that is;
#
#   - compile
#   - config.guess
#   - config.sub
#   - depcomp
#   - install-sh
#   - missing

AC_CONFIG_AUX_DIR([build-aux])

# For more information about the AM_INIT_AUTOMAKE macro, and the options which can be passed to it,
# refer to;
#
#   https://www.gnu.org/software/automake/manual/html_node/List-of-Automake-options.html
#
#   https://www.gnu.org/software/automake/manual/html_node/automake-Invocation.html#automake-Invocation
#
# Example of a strict invocation;
#
#   AM_INIT_AUTOMAKE([-Wall -Werror foreign])
#
#   1.15    : The minimum version number of the instance of Automake which should be used on this
#             package.
#   foreign : Set the Automake mode to 'foreign'. This will eliminate the need for the project to
#             contain certain files (e.g. AUTHORS, ChangeLog, COPYING, NEWS, README, etc).
#   -Wall   : Display all warnings.
#   -Werror : Treat any warnings as errors.


# AM_INIT_AUTOMAKE([-Wno-portability])

AM_INIT_AUTOMAKE([
	1.15
	foreign
	-Wall])

# The invocation of LT_INIT below, means that AC_PROG_RANLIB does not need to be
# invoked, as might be suggested by autoscan.

# LT_INIT()

# Sanity check to make sure the source code is in the
# correct location.

AC_CONFIG_SRCDIR([src/main.cpp])


# Tell Autoconf where certain macros should be loaded from.
# ---------------------------------------------------------
#
# In particular, this file (configure.ac) makes use of the
# following third party Autoconf macros;
#
#   - ax_save_flags_with_prefix.m4
#   - ax_restore_flags_with_prefix.m4
#   - ax_check_gl.m4

AC_CONFIG_MACRO_DIRS([m4])

# m4_include([m4/ax_save_flags_with_prefix.m4])
# m4_include([m4/ax_restore_flags_with_prefix.m4])
# m4_include([m4/ax_check_gl.m4])


# Checks for programs.
# --------------------

# AX_SAVE_FLAGS_WITH_PREFIX([GL],[CFLAGS])

AC_PROG_CXX()

AC_PROG_INSTALL()

AC_PROG_MAKE_SET()

AX_BOOST_BASE(
	["1.0.0"],
	[AC_MSG_NOTICE(["Found Boost libraries - Yippee"])],
	[AC_MSG_ERROR(["Did not find Boost libraries - Doh"])])


AX_HAVE_QT()

# Generate the necessary files.
# -----------------------------

AC_CONFIG_FILES(
	[Makefile
	 src/Makefile
	 src/moc/Makefile])

AC_OUTPUT()
