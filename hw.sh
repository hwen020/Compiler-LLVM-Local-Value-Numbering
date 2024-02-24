# I put everything here though something would need to be commented out from the second test.

# everything included:

# rebuild pass
cd llvm-tutor/HelloWorld/build/
# cmake ..
make clean
cmake -DLT_LLVM_INSTALL_DIR=$LLVM_DIR ..
make
cd 

# recompile bitcode
clang -c -emit-llvm -O1 demo.cpp -odemo.bc
clang -S -fno-discard-value-names -emit-llvm test1.c -o test1.ll
clang -S -fno-discard-value-names -emit-llvm test2.c -o test2.ll
clang -S -fno-discard-value-names -emit-llvm test3.c -o test3.ll
clang -S -fno-discard-value-names -emit-llvm test4.c -o test4.ll
clang -S -fno-discard-value-names -emit-llvm test5.c -o test5.ll
clang -S -fno-discard-value-names -emit-llvm test6.c -o test6.ll

# echo a couple new lines
echo ""
echo ""

# run opt
      # opt -load-pass-plugin ./llvm-tutor-main/build/lib/libHelloWorld.so -passes=hello-world -disable-output demo.bc
      # not the following path for .so
      #opt -load-pass-plugin ./llvm-tutor/build/lib/libHelloWorld.so -passes=hello-world -disable-output test.ll

# but the following path for .so
opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test.ll

echo ""
echo ""

# opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test1.ll

# echo ""
# echo ""

# opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test2.ll

# echo ""
# echo ""

# opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test3.ll

# echo ""
# echo ""

# opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test4.ll

# echo ""
# echo ""

# opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test5.ll

# echo ""
# echo ""

# opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test6.ll

# echo ""
# echo ""



# # From the second test:
# # rebuild pass
# cd llvm-tutor/HelloWorld/build/
# # cmake ..
# make clean
# cmake -DLT_LLVM_INSTALL_DIR=$LLVM_DIR ..
# make
# # cd ../..
# cd 

# # recompile bitcode
# # clang -c -emit-llvm -O1 demo.cpp -odemo.bc
# # clang -S -fno-discard-value-names -emit-llvm test1.c -o test1.ll
# # clang -S -fno-discard-value-names -emit-llvm test2.c -o test2.ll
# # clang -S -fno-discard-value-names -emit-llvm test3.c -o test3.ll
# # clang -S -fno-discard-value-names -emit-llvm test4.c -o test4.ll
# # clang -S -fno-discard-value-names -emit-llvm test5.c -o test5.ll
# # clang -S -fno-discard-value-names -emit-llvm test6.c -o test6.ll

# # echo a couple new lines
# echo ""
# echo ""

# # run opt
#       # opt -load-pass-plugin ./llvm-tutor-main/build/lib/libHelloWorld.so -passes=hello-world -disable-output demo.bc
#       # not the following path for .so
#       #opt -load-pass-plugin ./llvm-tutor/build/lib/libHelloWorld.so -passes=hello-world -disable-output test.ll

# # but the following path for .so
# opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test.ll

# echo ""
# echo ""

# # opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test1.ll

# # echo ""
# # echo ""

# # opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test2.ll

# # echo ""
# # echo ""

# # opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test3.ll

# # echo ""
# # echo ""

# # opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test4.ll

# # echo ""
# # echo ""

# # opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test5.ll

# # echo ""
# # echo ""

# # opt -load-pass-plugin ./llvm-tutor/HelloWorld/build/libHelloWorld.so -passes=hello-world -disable-output test6.ll

# # echo ""
# # echo ""