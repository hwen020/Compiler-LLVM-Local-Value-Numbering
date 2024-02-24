// // // // //=============================================================================
// // // // // FILE:
// // // // //    HelloWorld.cpp
// // // // //
// // // // // DESCRIPTION:
// // // // //    Visits all functions in a module, prints their names and the number of
// // // // //    arguments via stderr. Strictly speaking, this is an analysis pass (i.e.
// // // // //    the functions are not modified). However, in order to keep things simple
// // // // //    there's no 'print' method here (every analysis pass should implement it).
// // // // //
// // // // // USAGE:
// // // // //    New PM
// // // // //      opt -load-pass-plugin=libHelloWorld.dylib -passes="hello-world" `\`
// // // // //        -disable-output <input-llvm-file>
// // // // //
// // // // //
// // // // // License: MIT
// // // // //=============================================================================
// // // // #include "llvm/IR/LegacyPassManager.h"
// // // // #include "llvm/Passes/PassBuilder.h"
// // // // #include "llvm/Passes/PassPlugin.h"
// // // // #include "llvm/Support/raw_ostream.h"

// // // // #include <map> // std::map
// // // // #include <set> // std::set
// // // // #include <tuple> // std::tuple
// // // // #include <string> // std::string

// // // // #include "llvm/IR/InstrTypes.h"


// // // // using namespace llvm;

// // // // struct OpNum { //ppt page 27, not sure if ";" should be after this paragraph
// // // //   int opCode, left, right;
// // // //   bool operator < (const OpNum& rhs) const{
// // // //     return opCode < rhs.opCode || left < rhs.left || right > rhs.right;
// // // //   }
// // // // };// no ";" would err
// // // // bool isBinaryOperation(Instruction &inst) {
// // // //     return inst.isBinaryOp() && !inst.getType()->isVectorTy();
// // // // }
// // // // // ppt page 27
// // // // std::map<Value *, int> ValueNumbers; //don't know where to put these two lines of code
// // // // std::map<OpNum, int> OpNumbers;  //don't know where to put these two lines of code

// // // // std::string getOpSymbol(int opCode) {
// // // //     switch (opCode) {
// // // //         case Instruction::Add:
// // // //         case Instruction::FAdd:
// // // //             return "add";
// // // //         case Instruction::Sub:
// // // //             return "sub";
// // // //         case Instruction::Mul:
// // // //         case Instruction::FMul:
// // // //             return "mul";
// // // //         case Instruction::UDiv:
// // // //         case Instruction::SDiv:
// // // //         case Instruction::FDiv:
// // // //             return "div";
// // // //         // 可以继续添加其他操作码的情况
// // // //         default:
// // // //             return "unknown";
// // // //     }
// // // // }

// // // // // using namespace std; //for the former version of llvm?

// // // // //-----------------------------------------------------------------------------
// // // // // HelloWorld implementation
// // // // //-----------------------------------------------------------------------------
// // // // // No need to expose the internals of the pass to the outside world - keep
// // // // // everything in an anonymous namespace.
// // // // namespace {

// // // // // This method implements what the pass does
// // // // void visitor(Function &fn) {
// // // //     // 5. getOpcode,getOperand,getName (ppt page 25).Grab the operands(ppt page 26)
    
// // // // //     auto fuctionName = fn.getName();
// // // // //     auto argCount = fn.arg_size();
// // // // //     for (BasicBlock &basicBlock : fn) {
// // // // //         for (Instruction &inst : basicBlock) {
// // // // //             if (isBinaryOperation(inst)) {
// // // // //                 OpNum opInfo;
// // // // //                 opInfo.opCode = inst.getOpcode();
// // // // //                 opInfo.left = getOperandNumber(inst.getOperand(0));
// // // // //                 opInfo.right = getOperandNumber(inst.getOperand(1));

// // // // //                 int opNumber = OpNumbers[opInfo];
// // // // //                 if (opNumber == 0) {
// // // // //                     opNumber = NextOpNumber++;
// // // // //                     OpNumbers[opInfo] = opNumber;
// // // // //                 }

// // // // //                 errs() << formatv("{0,-40}", inst);
// // // // //                 errs() << "   " << opNumber << " = " << opInfo.left << " "
// // // // //                        << getOpSymbol(opInfo.opCode) << " " << opInfo.right;

// // // // //                 // Check for redundancy
// // // // //                 if (isRedundant(opInfo)) {
// // // // //                     errs() << " (redundant)";
// // // // //                 }

// // // // //                 errs() << "\n";
// // // // //             } else if (inst.getOpcode() == Instruction::Load) {
// // // // //                 // Handle load instructions
// // // // //                 //        dst               src
// // // // //                 errs() << &inst << " = " << inst.getOperand(0) << "\n";
// // // // //             } else if (inst.getOpcode() == Instruction::Store) {
// // // // //                 // Handle store instructions
// // // // //                 //                    src                               dst
// // // // //                 errs() << "store " << inst.getOperand(0) << " into " << inst.getOperand(1) << "\n";
// // // // //             } else if (inst.getOpcode() == Instruction::Alloca) {
// // // // //                 errs() << "alloca " << &inst << "\n";
// // // // //             }
// // // // //         }
// // // // //     }
// // // // // }//end of visitor


// // // // //     for (BasicBlock &basicBlock : fn) {
// // // // //         for (Instruction &inst : basicBlock) {
// // // // //             if (Instruction::Alloca == inst.getOpcode()) {
// // // // //                 continue;
// // // // //             }

// // // // //             if (Instruction::Ret == inst.getOpcode()) {
// // // // //                 continue;
// // // // //             }

// // // // //             errs() << formatv("{0,-40}", inst);

// // // // //             if (Instruction::Add == inst.getOpcode() ||
// // // // //                 Instruction::FAdd == inst.getOpcode() ||
// // // // //                 Instruction::Sub == inst.getOpcode() ||
// // // // //                 Instruction::Mul == inst.getOpcode() ||
// // // // //                 Instruction::FMul == inst.getOpcode() ||
// // // // //                 Instruction::UDiv == inst.getOpcode() ||
// // // // //                 Instruction::SDiv == inst.getOpcode() ||
// // // // //                 Instruction::FDiv == inst.getOpcode()) {
// // // // //                 // Identify the binary operation
// // // // //                 errs() << inst << "\n";

// // // // //                 Value *op0 = inst.getOperand(0);
// // // // //                 Value *op1 = inst.getOperand(1);

// // // // //                 errs() << &inst << " = " << op0 << " "
// // // // //                        << inst.getOpcodeName() << " " << op1;

// // // // //                 OpNum currentOpNum{
// // // // //                     inst.getOpcode(),
// // // // //                     reinterpret_cast<std::intptr_t>(op0),
// // // // //                     reinterpret_cast<std::intptr_t>(op1)};

// // // // //                 if (OpNumbers.count(currentOpNum) > 0) {
// // // // //                     errs() << " (redundant)";
// // // // //                 }

// // // // //                 errs() << "\n";

// // // // //                 OpNumbers[currentOpNum] = 1;
// // // // //             } else if (Instruction::Load == inst.getOpcode()) {
// // // // //                 // Load instruction
// // // // //                 errs() << &inst << " = " << inst.getOperand(0) << "\n";
// // // // //             } else if (Instruction::Store == inst.getOpcode()) {
// // // // //                 // Store instruction
// // // // //                 errs() << "store " << inst.getOperand(0) << " into "
// // // // //                        << inst.getOperand(1) << "\n";
// // // // //             }
// // // // //         }
// // // // //     }
// // // // // }//end of visitor


// // // // int NextValueNumber = 1;
// // // //     for (BasicBlock &basicBlock : fn) {
// // // //         for (Instruction &inst : basicBlock) {
// // // //             if (Instruction::Alloca == inst.getOpcode()) {
// // // //                 ValueNumbers[&inst] = NextValueNumber++;
// // // //                 errs() << inst << "    " << ValueNumbers[&inst] << " = " << ValueNumbers[&inst] << "\n";
// // // //             } else if (Instruction::Store == inst.getOpcode()) {
// // // //                 Value *op = inst.getOperand(0);
// // // //                 errs() << inst << "    " << ValueNumbers[&inst] << " = " << ValueNumbers[op] << "\n";
// // // //             } else if (Instruction::Load == inst.getOpcode()) {
// // // //                 Value *op = inst.getOperand(0);
// // // //                 errs() << inst << "    " << ValueNumbers[&inst] << " = " << ValueNumbers[op] << "\n";
// // // //             } else if (isBinaryOperation(inst)) {
// // // //                 Value *op0 = inst.getOperand(0);
// // // //                 Value *op1 = inst.getOperand(1);

// // // //                 OpNum opInfo{
// // // //                     inst.getOpcode(),
// // // //                     ValueNumbers[op0],
// // // //                     ValueNumbers[op1]};

// // // //                 int opNumber = OpNumbers[opInfo];
// // // //                 if (opNumber == 0) {
// // // //                     opNumber = NextValueNumber++;
// // // //                     OpNumbers[opInfo] = opNumber;
// // // //                 }

// // // //                 errs() << inst << "    " << opNumber << " = " << ValueNumbers[op0] << " "
// // // //                        << getOpSymbol(opInfo.opCode) << " " << ValueNumbers[op1];

// // // //                 // Check for redundancy
// // // //                 if (isRedundant(opInfo)) {
// // // //                     errs() << " (redundant)";
// // // //                 }

// // // //                 errs() << "\n";
// // // //             }
// // // //         }
// // // //     }
// // // // }//end of visitor


// // // // // New PM implementation
// // // // struct HelloWorld : PassInfoMixin<HelloWorld> {
// // // //   // Main entry point, takes IR unit to run the pass on (&F) and the
// // // //   // corresponding pass manager (to be queried if need be)
// // // //   PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
// // // //     visitor(F);
// // // //     return PreservedAnalyses::all();
// // // //   }

// // // //   // Without isRequired returning true, this pass will be skipped for functions
// // // //   // decorated with the optnone LLVM attribute. Note that clang -O0 decorates
// // // //   // all functions with optnone.
// // // //   static bool isRequired() { return true; }
// // // // }; // If no ";" here would err.
// // // // // struct OpNum { //ppt page 27, not sure if ";" should be after this paragraph
// // // // //   int opCode, left, right;
// // // // //   bool operator < (const OpNum& rhs) const{
// // // // //     return opCode < rhs.opCode || left < rhs.left || right > rhs.right;
// // // // //   }
// // // // // }; // not 
// // // // }// end of namespace

// // // // //-----------------------------------------------------------------------------
// // // // // New PM Registration
// // // // //-----------------------------------------------------------------------------
// // // // llvm::PassPluginLibraryInfo getHelloWorldPluginInfo() {
// // // //   return {LLVM_PLUGIN_API_VERSION, "HelloWorld", LLVM_VERSION_STRING,
// // // //           [](PassBuilder &PB) {
// // // //             PB.registerPipelineParsingCallback(
// // // //                 [](StringRef Name, FunctionPassManager &FPM,
// // // //                    ArrayRef<PassBuilder::PipelineElement>) {
// // // //                   if (Name == "hello-world") {
// // // //                     FPM.addPass(HelloWorld());
// // // //                     return true;
// // // //                   }
// // // //                   return false;
// // // //                 });
// // // //           }};
// // // // }

// // // // // This is the core interface for pass plugins. It guarantees that 'opt' will
// // // // // be able to recognize HelloWorld when added to the pass pipeline on the
// // // // // command line, i.e. via '-passes=hello-world'
// // // // extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
// // // // llvmGetPassPluginInfo() {
// // // //   return getHelloWorldPluginInfo();
// // // // }










// // // #include "llvm/IR/LegacyPassManager.h"
// // // #include "llvm/Passes/PassBuilder.h"
// // // #include "llvm/Passes/PassPlugin.h"
// // // #include "llvm/Support/raw_ostream.h"

// // // #include <map>   // std::map
// // // #include <set>   // std::set
// // // #include <tuple> // std::tuple
// // // #include <string> // std::string

// // // using namespace llvm;

// // // struct OpNum {
// // //   int opCode, left, right;
// // //   bool operator<(const OpNum &rhs) const {
// // //     return opCode < rhs.opCode || left < rhs.left || right > rhs.right;
// // //   }
// // // };

// // // std::map<Value *, int> ValueNumbers;
// // // std::map<OpNum, int> OpNumbers;

// // // namespace {

// // // void visitor(Function &fn) {
// // //   int NextOpNumber = 1;

// // //   auto getOpSymbol = [](int opcode) -> StringRef {
// // //     switch (opcode) {
// // //     case Instruction::Add:
// // //       return "add";
// // //     case Instruction::Sub:
// // //       return "sub";
// // //     case Instruction::Mul:
// // //       return "mul";
// // //     case Instruction::UDiv:
// // //     case Instruction::SDiv:
// // //     case Instruction::FDiv:
// // //       return "div";
// // //     // Add more cases as needed
// // //     default:
// // //       return "unknown";
// // //     }
// // //   };

// // //   auto isBinaryOperation = [](Instruction &inst) {
// // //     return inst.isBinaryOp() && !inst.getType()->isVectorTy();
// // //   };

// // //   auto isRedundant = [&OpNumbers](OpNum opInfo) -> bool {
// // //     return OpNumbers[opInfo] > 1;
// // //   };

// // //   for (BasicBlock &basicBlock : fn) {
// // //     for (Instruction &inst : basicBlock) {
// // //       if (Instruction::Alloca == inst.getOpcode() || Instruction::Ret == inst.getOpcode()) {
// // //         continue;
// // //       }

// // //       errs() << formatv("{0,-40}", inst);

// // //       if (isBinaryOperation(inst)) {
// // //         OpNum opInfo;
// // //         opInfo.opCode = inst.getOpcode();
// // //         opInfo.left = reinterpret_cast<std::intptr_t>(inst.getOperand(0));
// // //         opInfo.right = reinterpret_cast<std::intptr_t>(inst.getOperand(1));

// // //         int opNumber = OpNumbers[opInfo];
// // //         if (opNumber == 0) {
// // //           opNumber = NextOpNumber++;
// // //           OpNumbers[opInfo] = opNumber;
// // //         }

// // //         errs() << "   " << opNumber << " = " << opInfo.left << " " << getOpSymbol(opInfo.opCode) << " " << opInfo.right;

// // //         // Check for redundancy
// // //         if (isRedundant(opInfo)) {
// // //           errs() << " (redundant)";
// // //         }

// // //         errs() << "\n";
// // //       } else if (Instruction::Load == inst.getOpcode() || Instruction::Store == inst.getOpcode()) {
// // //         Value *operand = inst.getOperand(0);
// // //         int valueNumber = ValueNumbers[operand];
// // //         if (valueNumber == 0) {
// // //           valueNumber = NextOpNumber++;
// // //           ValueNumbers[operand] = valueNumber;
// // //         }

// // //         errs() << valueNumber << " = " << valueNumber << "\n";
// // //       }
// // //     }
// // //   }
// // // }

// // // struct HelloWorld : PassInfoMixin<HelloWorld> {
// // //   PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
// // //     visitor(F);
// // //     return PreservedAnalyses::all();
// // //   }

// // //   static bool isRequired() { return true; }
// // // };

// // // } // end of namespace

// // // llvm::PassPluginLibraryInfo getHelloWorldPluginInfo() {
// // //   return {LLVM_PLUGIN_API_VERSION, "HelloWorld", LLVM_VERSION_STRING,
// // //           [](PassBuilder &PB) {
// // //             PB.registerPipelineParsingCallback(
// // //                 [](StringRef Name, FunctionPassManager &FPM, ArrayRef<PassBuilder::PipelineElement>) {
// // //                   if (Name == "hello-world") {
// // //                     FPM.addPass(HelloWorld());
// // //                     return true;
// // //                   }
// // //                   return false;
// // //                 });
// // //           }};
// // // }

// // // extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
// // //   return getHelloWorldPluginInfo();
// // // }












// // //这个可以用来作为修改的基础。到
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include <map>
#include <tuple>
#include <string>

using namespace llvm;

struct OpNum {
  int opCode, left, right;
  bool operator<(const OpNum &rhs) const {
    return std::tie(opCode, left, right) < std::tie(rhs.opCode, rhs.left, rhs.right);
  }
};

std::map<Value *, int> ValueNumbers;
std::map<OpNum, int> OpNumbers;

static int NextValueNumber = 1;//
    
// Helper function to get or assign a unique number to each value
int getValueNumber(Value *v) {
  if (ValueNumbers.count(v) == 0) {
    // static int NextValueNumber = 1;
    ValueNumbers[v] = NextValueNumber++;
  }
  return ValueNumbers[v];
}

void visitor(Function &fn) {
  for (BasicBlock &basicBlock : fn) {
    for (Instruction &inst : basicBlock) {
      if (inst.getOpcode() == Instruction::Alloca || Instruction::Ret == inst.getOpcode()) {
        // Skip printing alloca
        continue;
      }

      errs() << formatv("{0,-40}", inst);

      if (inst.getOpcode() == Instruction::Load) {
        Value *op0 = inst.getOperand(0);//this is for the new addr, not what we want.
        // errs() << op0 << getValueNumber(op0) << " = " << getValueNumber(op0) << "\n";
        Value *loadedValue = cast<LoadInst>(&inst)->getOperand(0);
        ValueNumbers[op0] = getValueNumber(loadedValue);//
        errs() << getValueNumber(loadedValue) << " = " << getValueNumber(loadedValue) << "\n";
        // errs() << getValueNumber(loadedValue) << " = " << getValueNumber(loadedValue) << " = " << getValueNumber(op0) << "\n";
      } else if (inst.getOpcode() == Instruction::Store) {
        //it should be op1, the pointer. op0 is the value.
        Value *op1 = inst.getOperand(1);
        Value *op0 = inst.getOperand(0);
        ValueNumbers[op0] = getValueNumber(op1);//
        errs() << getValueNumber(op1) << " = " << getValueNumber(op1) << "\n";
        // errs() << getValueNumber(op0) << " = " << getValueNumber(op0) << "\n";
      } else if (inst.isBinaryOp() && !inst.getType()->isVectorTy()) {
        // Binary operation
        Value *op0 = inst.getOperand(0);
        Value *op1 = inst.getOperand(1);

        // errs() << " = " << getValueNumber(op0) << " " << inst.getOpcodeName() << " "
        //        << getValueNumber(op1);

        OpNum currentOpNum{
            inst.getOpcode(),
            getValueNumber(op0),
            getValueNumber(op1)};

        int opNumber = OpNumbers[currentOpNum];
        if (opNumber == 0) {
          opNumber = NextValueNumber++;
          // opNumber = OpNumbers.size() + 1;
          OpNumbers[currentOpNum] = opNumber;
        }

        errs() << opNumber << " = " << getValueNumber(op0) << " " << inst.getOpcodeName() << " "
               << getValueNumber(op1);

        // Check for redundancy
        if (OpNumbers.count(currentOpNum) > 1) {
          errs() << " (redundant)";
        }

        errs() << "\n";
      }
    }
  }
}

struct HelloWorld : PassInfoMixin<HelloWorld> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
    visitor(F);
    return PreservedAnalyses::all();
  }

  static bool isRequired() { return true; }
};

llvm::PassPluginLibraryInfo getHelloWorldPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "HelloWorld", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM, ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "hello-world") {
                    FPM.addPass(HelloWorld());
                    return true;
                  }
                  return false;
                });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getHelloWorldPluginInfo();
}










// #include "llvm/IR/LegacyPassManager.h"
// #include "llvm/Passes/PassBuilder.h"
// #include "llvm/Passes/PassPlugin.h"
// #include "llvm/Support/raw_ostream.h"

// #include <map>
// #include <tuple>
// #include <string>

// using namespace llvm;

// struct OpNum {
//   int opCode, left, right;
//   bool operator<(const OpNum &rhs) const {
//     return std::tie(opCode, left, right) < std::tie(rhs.opCode, rhs.left, rhs.right);
//   }
// };

// std::map<Value *, int> ValueNumbers;
// std::map<OpNum, int> OpNumbers;

// static int NextValueNumber = 1; //

// // Helper function to get or assign a unique number to each value
// int getValueNumber(Value *v) {
//   if (ValueNumbers.count(v) == 0) {
//     // static int NextValueNumber = 1;
//     ValueNumbers[v] = NextValueNumber++;
//   }
//   return ValueNumbers[v];
// }

// void printModifiedOutput(Instruction &inst) {
//   std::map<Value *, int> tempValueNumbers;
//   std::map<OpNum, int> tempOpNumbers;
//   int tempNextValueNumber = 1;

//   errs() << formatv("{0,-40}", inst);

//   if (inst.getOpcode() == Instruction::Load) {
//     Value *op0 = inst.getOperand(0); // this is for the new addr, not what we want.
//     Value *loadedValue = cast<LoadInst>(&inst)->getOperand(0);
//     tempValueNumbers[op0] = getValueNumber(loadedValue); //
//     errs() << getValueNumber(loadedValue) << " = " << getValueNumber(loadedValue) << "\n";
//   } else if (inst.getOpcode() == Instruction::Store) {
//     // it should be op1, the pointer. op0 is the value.
//     Value *op1 = inst.getOperand(1);
//     Value *op0 = inst.getOperand(0);
//     tempValueNumbers[op0] = getValueNumber(op1); //
//     errs() << getValueNumber(op1) << " = " << getValueNumber(op1) << "\n";
//   } else if (inst.isBinaryOp() && !inst.getType()->isVectorTy()) {
//     // Binary operation
//     Value *op0 = inst.getOperand(0);
//     Value *op1 = inst.getOperand(1);

//     // errs() << " = " << getValueNumber(op0) << " " << inst.getOpcodeName() << " " << getValueNumber(op1);

//     OpNum currentOpNum{
//         inst.getOpcode(),
//         getValueNumber(op0),
//         getValueNumber(op1)};

//     int opNumber = tempOpNumbers[currentOpNum];
//     if (opNumber == 0) {
//       opNumber = tempNextValueNumber++;
//       tempOpNumbers[currentOpNum] = opNumber;
//     }

//     errs() << opNumber << " = " << getValueNumber(op0) << " " << inst.getOpcodeName() << " " << getValueNumber(op1);

//     // Check for redundancy
//     if (tempOpNumbers.count(currentOpNum) > 1) {
//       errs() << " (redundant)";
//     }

//     errs() << "\n";
//   }
// }

// void visitor(Function &fn) {
//   for (BasicBlock &basicBlock : fn) {
//     for (Instruction &inst : basicBlock) {
//       if (inst.getOpcode() == Instruction::Alloca || Instruction::Ret == inst.getOpcode()) {
//         // Skip printing alloca
//         continue;
//       }

//       printModifiedOutput(inst);
//     }
//   }
// }

// struct HelloWorld : PassInfoMixin<HelloWorld> {
//   PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
//     visitor(F);
//     return PreservedAnalyses::all();
//   }

//   static bool isRequired() { return true; }
// };

// llvm::PassPluginLibraryInfo getHelloWorldPluginInfo() {
//   return {LLVM_PLUGIN_API_VERSION, "HelloWorld", LLVM_VERSION_STRING,
//           [](PassBuilder &PB) {
//             PB.registerPipelineParsingCallback(
//                 [](StringRef Name, FunctionPassManager &FPM, ArrayRef<PassBuilder::PipelineElement>) {
//                   if (Name == "hello-world") {
//                     FPM.addPass(HelloWorld());
//                     return true;
//                   }
//                   return false;
//                 });
//           }};
// }

// extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
//   return getHelloWorldPluginInfo();
// }













// #include "llvm/IR/LegacyPassManager.h"
// #include "llvm/Passes/PassBuilder.h"
// #include "llvm/Passes/PassPlugin.h"
// #include "llvm/Support/raw_ostream.h"

// #include <map>
// #include <tuple>
// #include <string>

// using namespace llvm;

// struct OpNum {
//   int opCode, left, right;
//   bool operator<(const OpNum &rhs) const {
//     return std::tie(opCode, left, right) < std::tie(rhs.opCode, rhs.left, rhs.right);
//   }
// };

// std::map<Value *, int> ValueNumbers;
// std::map<OpNum, int> OpNumbers;

// static int NextValueNumber = 1;

// // Helper function to get or assign a unique number to each value
// int getValueNumber(Value *v) {
//   if (ValueNumbers.count(v) == 0) {
//     ValueNumbers[v] = NextValueNumber++;
//   }
//   return ValueNumbers[v];
// }

// void printModifiedOutput(Instruction &inst) {
//   std::map<Value *, int> tempValueNumbers;
//   std::map<OpNum, int> tempOpNumbers;
//   int tempNextValueNumber = 1;

//   errs() << formatv("{0,-40}", inst);

//   if (inst.getOpcode() == Instruction::Load) {
//     Value *op0 = inst.getOperand(0); // this is for the new addr, not what we want.
//     Value *loadedValue = cast<LoadInst>(&inst)->getOperand(0);
//     tempValueNumbers[op0] = getValueNumber(loadedValue);
//     errs() << getValueNumber(loadedValue) << " = " << getValueNumber(loadedValue) << "\n";
//   } else if (inst.getOpcode() == Instruction::Store) {
//     // it should be op1, the pointer. op0 is the value.
//     Value *op1 = inst.getOperand(1);
//     Value *op0 = inst.getOperand(0);
//     tempValueNumbers[op0] = getValueNumber(op1);
//     errs() << getValueNumber(op1) << " = " << getValueNumber(op1) << "\n";
//   } else if (inst.isBinaryOp() && !inst.getType()->isVectorTy()) {
//     // Binary operation
//     Value *op0 = inst.getOperand(0);
//     Value *op1 = inst.getOperand(1);

//     OpNum currentOpNum{
//         inst.getOpcode(),
//         getValueNumber(op0),
//         getValueNumber(op1)};

//     int opNumber = tempOpNumbers[currentOpNum];
//     if (opNumber == 0) {
//       opNumber = tempNextValueNumber++;
//       tempOpNumbers[currentOpNum] = opNumber;
//     }

//     errs() << opNumber << " = " << getValueNumber(op0) << " " << inst.getOpcodeName() << " " << getValueNumber(op1);

//     // Check for redundancy
//     if (tempOpNumbers.count(currentOpNum) > 1) {
//       errs() << " (redundant)";
//     }

//     errs() << "\n";
//   }
// }

// void visitor(Function &fn) {
//   for (BasicBlock &basicBlock : fn) {
//     for (Instruction &inst : basicBlock) {
//       if (inst.getOpcode() == Instruction::Alloca || Instruction::Ret == inst.getOpcode()) {
//         // Skip printing alloca
//         continue;
//       }

//       printModifiedOutput(inst);
//     }
//   }
// }

// struct HelloWorld : PassInfoMixin<HelloWorld> {
//   PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
//     visitor(F);
//     return PreservedAnalyses::all();
//   }

//   static bool isRequired() { return true; }
// };

// llvm::PassPluginLibraryInfo getHelloWorldPluginInfo() {
//   return {LLVM_PLUGIN_API_VERSION, "HelloWorld", LLVM_VERSION_STRING,
//           [](PassBuilder &PB) {
//             PB.registerPipelineParsingCallback(
//                 [](StringRef Name, FunctionPassManager &FPM, ArrayRef<PassBuilder::PipelineElement>) {
//                   if (Name == "hello-world") {
//                     FPM.addPass(HelloWorld());
//                     return true;
//                   }
//                   return false;
//                 });
//           }};
// }

// extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
//   return getHelloWorldPluginInfo();
// }
