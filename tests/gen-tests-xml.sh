#!/bin/bash

#
# Variables that used as configuration values.
#
DOMAIN="Application Framework"
FEATURE="Direct UI Core"
TYPE="Functional"
LEVEL="Component"
BINARY_DIR="/usr/lib/system-ui-tests"

#
# The code. These lines should not contain configuration values.
#
ALLTESTS=$(ls -1d ut_*/*.pro ft_*/*.pro 2>/dev/null | \
grep -v ut_template | sed 's!/.*!!')

#
# Generates a <case> XML node for the test case and appends it either to the end
# of the unit tests or the end of the functional tests.
# 
# Params:
#  $1: The base name of the directory that holds the test case.
#
function gencase ()
{
	PREF=""
	POST=""

	#
	# If the test program does not exists the directory will be ignored.
	#
	if [ ! -x $1/$1 ]; then
		return 0;
	fi

	#
	# If the test case directory contains a 'deleted' file the test will be
	# commented out from the XML file.
	#
	if [ -e $1/deleted ]; then
		PREF="
        <!-- Test disabled because the $1/deleted file exists."
		POST="
          -->"
	fi

	CASE="
        <case name='$1' 
              requirement=''"

	#
	# If the 'description' file exists in the test directory the test case
	# description will be loaded from that file.
	#
	if [ -e $1/description ]; then
		CASE="${CASE}
              description ='$(cat $1/description)'"
	else
		CASE="${CASE}
              description='$1'"
	fi

	#
	# The test is insignificant if the 'disabled' file exists in the test
	# directory.
	# 
	if [ -e $1/disabled ]; then
		CASE="${CASE}
              insignificant='true'"
	fi

	#
	# If the 'timeout' file exists in the test directory the timeout value
	# will be loaded from that file.
	#
	if [ -e $1/timeout ]; then
		CASE="${CASE}
              timeout='$(cat $1/timeout)'"
	else
		CASE="${CASE}
              timeout='60'"
	fi

	CASE="${CASE}>"

	CASE="${CASE}
            <step expected_result='0'>$BINARY_DIR/$TEST</step>
        </case>"

	#
	# Appending the node to the unit tests or the functional tests.
	#
	if [ -n "`echo $1 | egrep '^u'`" ]; then
		UT_TESTCASES="${UT_TESTCASES}${PREF}${CASE}${POST}"
	else
		FT_TESTCASES="${FT_TESTCASES}${PREF}${CASE}${POST}"
	fi
}

#
# The main program startes here. It goes through all the test directory names
# and adds the generated nodes to the UT_TESTCASES and FT_TESTCASES variables.
# Then the code generates the XML file and prints it to the standard output.
#
for TEST in $ALLTESTS; do
	gencase "$TEST"
done

TESTSUITE_TEMPLATE="<?xml version='1.0' encoding='ISO-8859-1'?>
<testdefinition version='0.1'>
  <!-- 
    This XML file is generated by the $(basename $0). Please do not modify
    this file for it is going to be overwritten the next time the application 
    is built.

    This file was generated using the following rules:
      o If the test case directory contains a 'deleted' file the test will be
	commented out from the XML file. 
      o If the 'description' file exists in the test directory the test case
	description will be loaded from that file.
      o The test is insignificant if the 'disabled' file exists in the test
	directory.
      o If the 'timeout' file exists in the test directory the timeout value
	will be loaded from that file.
    -->
  <suite name='system-ui-tests' domain='$DOMAIN' type='$TYPE' level='$LEVEL'>
    <set name='unit_tests' description='Unit Tests' feature='$FEATURE'>$UT_TESTCASES
      <environments>
        <scratchbox>false</scratchbox>
        <hardware>true</hardware>    
      </environments> 
    </set>
    <set name='functional_tests' description='Functional Tests' feature='$FEATURE'>$FT_TESTCASES
      <environments>
        <scratchbox>false</scratchbox>
        <hardware>true</hardware>    
      </environments> 
    </set>
  </suite>
</testdefinition>"

echo "$TESTSUITE_TEMPLATE"
