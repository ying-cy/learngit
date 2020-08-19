cmake_minimum_required( VERSION 2.6.3 )
set(CMAKE_SYSTEM_NAME Linux )
 
SET (CMAKE_C_COMPILER             "/usr/bin/clang")
SET (CMAKE_C_FLAGS                "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
 
SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
SET (CMAKE_CXX_FLAGS                "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
 
SET (CMAKE_AR      "/usr/bin/llvm-ar")
SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
SET (CMAKE_NM      "/usr/bin/llvm-nm")
SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")

/usr/local/bin/cmake -E cmake_link_script CMakeFiles/hello-world.dir/link.txt --verbose=1
/usr/bin/clang++ -Wall CMakeFiles/hello-world.dir/main.c.o -o hello-world  
/usr/lib/llvm-6.0/lib/libLLVMSupport.a 
/usr/lib/llvm-6.0/lib/libLLVMCore.a 
/usr/lib/llvm-6.0/lib/libLLVMIRReader.a 
/usr/lib/llvm-6.0/lib/libLLVMAsmParser.a 
/usr/lib/llvm-6.0/lib/libLLVMBitReader.a 
/usr/lib/llvm-6.0/lib/libLLVMCore.a 
/usr/lib/llvm-6.0/lib/libLLVMBinaryFormat.a 
/usr/lib/llvm-6.0/lib/libLLVMSupport.a -lz -lrt -ldl -ltinfo -lpthread -lm 
/usr/lib/llvm-6.0/lib/libLLVMDemangle.a 

