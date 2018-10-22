#!/bin/bash

function promt_and_abort() 
{
	echo $1
	exit 1
}

function abort_if_last_cmd_fail()
{	
	if [ $? -ne 0 ];then
		promt_and_abort $1
	fi
}

if [ ! -d build ];then
	mkdir build
fi

cd build
cmake ../src
abort_if_last_cmd_fail "generate makefile fail"
make