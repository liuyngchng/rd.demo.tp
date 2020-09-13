# 1. build log4c
```
mkdir build
cd build
../configure --without-expat  // very important
make
```
# 2. error troubleshoot
if you see
```
Undefined symbols for architecture x86_64:
  "_XML_ErrorString", referenced from:
      _sd_domnode_fread in liblog4c.a(domnode-expat.o)
      _sd_domnode_read in liblog4c.a(domnode-expat.o)
```
then retry to do 
```
 ../configure --without-expat
```
the argument --without-expat is very important.
