#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/FormatVariadic.h"
#include <string>
#include <map>

using namespace llvm;
using namespace std;

#define DEBUG_TYPE "ValueNumbering"

using namespace llvm;

namespace {
struct ValueNumbering : public FunctionPass {
    string func_name = "test";
    static char ID;
    
    map<llvm::Value *,int> valTable;
    map<string, int> redTable;
    int valueNumber = 0;
    string op = "";
    string repeat = "";

    ValueNumbering() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
	    
        errs() << "ValueNumbering: " << F.getName() << "\n";
        // if (F.getName() != func_name) return false;

        for (auto& basic_block : F)
        {
            for (auto& inst : basic_block)
            {
                // errs() << inst << "\n";
                // errs() << inst.getOperand(0) << "\n";
                if (inst.getOpcode() == Instruction::Alloca){
                    // errs() << formatv("{0,-40}", inst);
                    continue;
                }

                if(inst.getOpcode() == Instruction::Load){
                    // errs() << "Load ";
                    // errs() << inst.getOperand(0) << "\n";
                    // errs() << inst.getOperand(1) << "\n";
                    if (valTable.find(inst.getOperand(0)) == valTable.end()){
                        valTable[inst.getOperand(0)] = ++valueNumber;
                    }
                    if (valTable.find(inst.getOperandList()->getUser()) == valTable.end()){
                        valTable[inst.getOperandList()->getUser()] = valTable[inst.getOperand(0)];
                    }

                    errs() << formatv("{0,-40}", inst) << valTable[inst.getOperandList()->getUser()] << " = " << valTable[inst.getOperandList()->getUser()] << "\n";
                }
                if(inst.getOpcode() == Instruction::Store){
                    // errs() << "Store ";
                    // if (inst.getOperand(0)){
                        // errs() << inst.getOperand(0) << "\n";
                        // errs() << inst.getOperand(1) << "\n";
                    // }
                    // if (valTable.find(inst.getOperand(0)) != valTable.end()){
                    //     valTable[inst.getOperand(1)] = valTable[inst.getOperand(0)];
                    //     errs() << formatv("{0,-40}", inst) << valTable[inst.getOperand(1)] << " = " << valTable[inst.getOperand(1)] << "\n";
                    // }
                    // else if (valTable.find(inst.getOperand(1)) == valTable.end()){
                    //     valTable[inst.getOperand(1)] = ++valueNumber;
                    //     errs() << formatv("{0,-40}", inst) << valTable[inst.getOperand(1)] << " = " << valTable[inst.getOperand(1)] << "\n";
                    // }

                    if (valTable.find(inst.getOperand(0)) == valTable.end()){
                        valTable[inst.getOperand(0)] = ++valueNumber;
                        valTable[inst.getOperand(1)] = valTable[inst.getOperand(0)];
                        errs() << formatv("{0,-40}", inst) << valTable[inst.getOperand(0)] << " = " << valTable[inst.getOperand(1)] << "\n";
                    }
                    valTable[inst.getOperand(1)] = valTable[inst.getOperand(0)];
                    errs() << formatv("{0,-40}", inst) << valTable[inst.getOperand(0)] << " = " << valTable[inst.getOperand(1)] << "\n";

                    // errs() << inst.getOperandList()->get() << "\n";
                    // errs() << "\nOperand(1)" << (*inst.getOperand(1)) <<"\n";
                    // errs() << "\nOperand(1) Mem: " << inst.getOperand(1) <<"---\n";
                }
                if (inst.isBinaryOp())
                {
                    // errs() << "Op Code:" << inst.getOpcodeName()<<"\n";
                    if(inst.getOpcode() == Instruction::Add){
                        // errs() << "Add ";
                        op = "Add";
                        if (valTable.find(inst.getOperand(0)) == valTable.end()){
                            valTable[inst.getOperand(0)] = ++valueNumber;
                        }
                        if (valTable.find(inst.getOperand(1)) == valTable.end()){
                            valTable[inst.getOperand(1)] = ++valueNumber;
                        }
                        if (valTable.find(inst.getOperandList()->getUser()) == valTable.end()){
                            valTable[inst.getOperandList()->getUser()] = ++valueNumber;
                        }

                        // errs() << "\nOperand(0) Add Mem: " << inst->get() <<"\n";
                        // errs() << valTable[inst.getOperandList()->getUser()] << " = " ;

                    }
                    if(inst.getOpcode() == Instruction::Sub){
                        // errs() << "Sub ";
                        op = "Sub";
                        if (valTable.find(inst.getOperand(0)) == valTable.end()){
                            valTable[inst.getOperand(0)] = ++valueNumber;
                        }
                        if (valTable.find(inst.getOperand(1)) == valTable.end()){
                            valTable[inst.getOperand(1)] = ++valueNumber;
                        }
                        if (valTable.find(inst.getOperandList()->getUser()) == valTable.end()){
                            valTable[inst.getOperandList()->getUser()] = ++valueNumber;
                        }


                    }
                    if(inst.getOpcode() == Instruction::Mul){
                        // errs() << "Mult ";
                        op = "Mult";
                        if (valTable.find(inst.getOperand(0)) == valTable.end()){
                            valTable[inst.getOperand(0)] = ++valueNumber;
                        }
                        if (valTable.find(inst.getOperand(1)) == valTable.end()){
                            valTable[inst.getOperand(1)] = ++valueNumber;
                        }
                        if (valTable.find(inst.getOperandList()->getUser()) == valTable.end()){
                            valTable[inst.getOperandList()->getUser()] = ++valueNumber;
                        }


                    }
                    if(inst.getOpcode() == Instruction::UDiv){
                        // errs() << "Div ";
                        op = "Div";
                        if (valTable.find(inst.getOperand(0)) == valTable.end()){
                            valTable[inst.getOperand(0)] = ++valueNumber;
                        }
                        if (valTable.find(inst.getOperand(1)) == valTable.end()){
                            valTable[inst.getOperand(1)] = ++valueNumber;
                        }
                        if (valTable.find(inst.getOperandList()->getUser()) == valTable.end()){
                            valTable[inst.getOperandList()->getUser()] = ++valueNumber;
                        }


                    }
                    
                    // see other classes, Instruction::Sub, Instruction::UDiv, Instruction::SDiv
                    // errs() << "Operand(0)" << (*inst.getOperand(0)) <<"---\n";
                    // errs() << "Operand(1)" << (*inst.getOperand(1)) <<"---\n";
                    auto* ptr = dyn_cast<User>(&inst);
		            //errs() << "\t" << *ptr << "\n";
                    int i = 0;
                    int temp1 = 0;
                    int temp2 = 0;

                    for (auto it = ptr->op_begin(); it != ptr->op_end(); ++it) {
                        
                        // errs() << dyn_cast<Instruction>(it)->getOperand(0) << "\n";
                        // (*it)->setName(to_string(valueNumber));
                        // errs() << valTable[dyn_cast<Instruction>(it)->getOperand(0)];
                        // errs() << "PRINTING INT: " << (*it) << "\n";
                        // if (valTable.find((*it)) == valTable.end()){
                        //     // errs() << "HERE\n";
                        //     valTable[(*it)] = ++valueNumber;
                        //     errs() << formatv("{0,-40}", *(*it)) << valTable[(*it)] << " = " << valTable[(*it)] << "\n";
                        // }
                        if (i == 0){
                            // errs() << valTable[dyn_cast<Instruction>(it)->getOperand(0)] << " " + op + " ";
                            temp1 = valTable[(*it)];
                        }
                        else{
                            // errs() << valTable[dyn_cast<Instruction>(it)->getOperand(0)] << "\n";

                            temp2 = valTable[(*it)];
                            string temp = to_string(temp1) + op + to_string(temp2);

                            if (redTable.find(temp) == redTable.end()){
                                redTable[temp] = valTable[inst.getOperandList()->getUser()];
                            }
                            else{
                                repeat = " (redundant) ";
                                valTable[inst.getOperandList()->getUser()] = redTable[temp];
                            }
                        }
                        i++;
                        // if ((*it)->hasName()) 
            			//     errs() << (*it)->getName() << "\n";                      
                    }
                    //output for binary OP w/ redundant computation output
                    errs() << formatv("{0,-40}", inst) << valTable[inst.getOperandList()->getUser()] << " = " << temp1 << " " + op + " " << temp2 << repeat << "\n";
                    repeat = "";
                } // end if
            } // end for inst
        } // end for block
        return false;
    } // end runOnFunction
}; // end of struct ValueNumbering
}  // end of anonymous namespace

char ValueNumbering::ID = 0;
static RegisterPass<ValueNumbering> X("ValueNumbering", "ValueNumbering Pass",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);
