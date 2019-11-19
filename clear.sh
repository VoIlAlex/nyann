#!bin/bash

if test -f  'bin/intermediate/main.o'
then
	rm bin/intermediate/main.o 
fi
if test -f 'bin/intermediate/io_draft.o' 
then 
	rm bin/intermediate/io_draft.o 
fi
if test -f 'bin/main.exe' 
then 
	rm bin/main.exe
fi