#!/bin/bash

echo "[*] Compiling Protobufs"

../extern_libs/bin/protoc -I=. --cpp_out=../src *.proto
mv ../src/*.pb.h ../include/

echo "[*] Done!"
