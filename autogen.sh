#!/usr/bin/bash
# Builds the configure script using configure.ac
# To delete old build files, add "clean" as an argument


delete() {
    rm $1 "$2"
    if [ $? -ne 0 ] && [ -n "$3" ]; then
        echo "$3"
    fi
}


clean() {
    echo "Cleaning build location..."
    delete -v aclocal.m4 "Missing aclocal. You must run aclocal before autoconf"
    delete -vr autom4te.cache "No autom4te cache"
    delete -v configure "No configure script found"
    delete -v config.log "Partial build detected"
    delete -v config.status
    delete -vr .deps
    delete -v depcomp
    delete -v install-sh
    delete -v missing
    delete -v Makefile
    delete -v Makefile.in
    delete -v *.o "Deleting *.o files"
}


build() {
    echo "Building configure script..."
    autoreconf --install
    if [ $? -ne 0 ]; then
        echo "Failure :("; exit 1
    fi
    echo "Success! Now you can run ./configure"
}


main() {
    stat configure > /dev/null 2>&1
    if [ "$?" -ne 0 ]; then echo "WARNING: configure script already exists"; fi
    if [ "$1" = "clean-only" ]; then clean; exit; fi
    if [ "$1" = "clean" ]; then clean; fi
    build
}

main "$1"
