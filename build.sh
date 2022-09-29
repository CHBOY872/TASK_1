#!/bin/sh

if [ -z "$1" ]
then
    cd src
    make all
    cd ..
    mv src/main .
    chmod +x main
else
    case "$1" in
        test)
            cd src
            make runtest
	    if [ "0" -eq "$?" ]
	    then
                cd ..
                mv src/test .
                chmod +x test
                ./test
	    fi
            ;;
    esac
fi

