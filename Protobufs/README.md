### Protobufs compilation

Install Protobufs for C++ via [this guide.](https://github.com/google/protobuf/tree/master/src)

**Note that** you should configure it with the prefix of the folder `extern_libs` in the base directory  of this project.

######

In order to compile all the `.proto` files in this directory, run:

```bash
# protoc tool installed in extern_libs/bin:
../extern_libs/bin/protoc -I=. --cpp_out=../src *.proto
mv ../src/*.pb.h ../include/
```



##
More on Protobufs [on this link...](https://developers.google.com/protocol-buffers/docs/cpptutorial)
