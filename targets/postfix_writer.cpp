#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/variable_visitor.h"
#include "targets/postfix_writer.h"
#include "ast/all.h"  // all.h is automatically generated

#define ASSERT_I2D(node) \
  if (node->left()->type()->name() == basic_type::TYPE_INT && \
      node->right()->type()->name() == basic_type::TYPE_DOUBLE) _pf.I2D();

void gr8::postfix_writer::auxiliaryLoad(basic_type* type) {
  if (type->name() == basic_type::TYPE_DOUBLE) _pf.LDDOUBLE(); else _pf.LDINT();
}

void gr8::postfix_writer::allocObjects(gr8::objects_node* node) {
  _pf.TEXT();
  node->argument()->accept(this, 0);
  int bytes = node->type()->name() == basic_type::TYPE_DOUBLE ? 8 : 4;
  _pf.INT(bytes);
  _pf.MUL();
  _pf.ALLOC();
  _pf.SP();

  _allocateObjects = false;
}

basic_type* gr8::postfix_writer::getPointerRoot(basic_type* type) {
  basic_type* parent = type;
  while (parent->name() == basic_type::TYPE_POINTER) {
    parent = parent->_subtype;
  }
  return parent;
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_nil_node(cdk::nil_node * const node, int lvl) {
  // EMPTY
}
void gr8::postfix_writer::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  if (!inFunction()) {
    _pf.TEXT();
    _pf.EXTERN("printi");
    _pf.EXTERN("printd");
    _pf.EXTERN("prints");
    _pf.EXTERN("println");
    _pf.EXTERN("readi");
    _pf.EXTERN("readd");
  }
  
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }

  //Declare undefined functions as external
  if (!inFunction()) {
    if (_undefinedFunctions.size() > 0) {
      std::set<std::string>::iterator it;
      for (it = _undefinedFunctions.begin(); it != _undefinedFunctions.end(); ++it)
      {
        _pf.EXTERN(*it);
      }
      _undefinedFunctions.clear();
    }
  }
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  _pf.INT(node->value());
}

void gr8::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
  _pf.DOUBLE(node->value());
}

void gr8::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
  int lbl1;

  /* generate the string */
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.SSTRING(node->value()); // output string characters

  /* leave the address on the stack */
  _pf.TEXT(); // return to the TEXT segment
  _pf.ADDR(mklbl(lbl1)); // the string to be printed
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.DNEG();
  }
  else {
    _pf.NEG();
  }
}
void gr8::postfix_writer::do_not_node(cdk::not_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  _pf.INT(0);
  _pf.EQ();
}
void gr8::postfix_writer::do_identity_node(gr8::identity_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  if (node->right()->type()->name() != basic_type::TYPE_POINTER){

    node->left()->accept(this, lvl);
    if (node->left()->type()->name() == basic_type::TYPE_INT &&
        node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
      _pf.I2D();
    }

    node->right()->accept(this, lvl);
    if (node->right()->type()->name() == basic_type::TYPE_INT &&
        node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
      _pf.I2D();
    }

    //Pointer sum
    if (node->left()->type()->name() == basic_type::TYPE_POINTER) {
      if (node->left()->type()->_subtype->name()  == basic_type::TYPE_DOUBLE) _pf.INT(8); else _pf.INT(4);
      _pf.MUL();
      _pf.ADD();
    } else {
      if (node->right()->type()->name() == basic_type::TYPE_DOUBLE ||
          node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
        _pf.DADD();
      }
      else {
        _pf.ADD();
      }
    }
  }
  else {
    node->right()->accept(this, lvl);
    node->left()->accept(this, lvl);
    if (node->right()->type()->_subtype->name() == basic_type::TYPE_DOUBLE) _pf.INT(8); else _pf.INT(4);
    _pf.MUL();
    _pf.ADD();
  }
}
void gr8::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  if (node->left()->type()->name() == basic_type::TYPE_INT &&
      node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }

  node->right()->accept(this, lvl);
  if (node->right()->type()->name() == basic_type::TYPE_INT &&
      node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }
  
  if (node->left()->type()->name() == basic_type::TYPE_POINTER || 
      node->right()->type()->name() == basic_type::TYPE_POINTER) {
    if (node->type()->name() == basic_type::TYPE_DOUBLE) _pf.INT(4); else _pf.INT(8);
    _pf.MUL();
    _pf.SUB();
  }
  else {
    if (node->right()->type()->name() == basic_type::TYPE_DOUBLE ||
        node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
      _pf.DSUB();
    }
    else {
      _pf.SUB();
    }
  }
}
void gr8::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  if (node->left()->type()->name() == basic_type::TYPE_INT &&
      node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }

  node->right()->accept(this, lvl);
  if (node->right()->type()->name() == basic_type::TYPE_INT &&
      node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }
  
  if (node->right()->type()->name() == basic_type::TYPE_DOUBLE ||
      node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.DMUL();
  }
  else {
    _pf.MUL();
  }
}
void gr8::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  if (node->left()->type()->name() == basic_type::TYPE_INT &&
      node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }

  node->right()->accept(this, lvl);
  if (node->right()->type()->name() == basic_type::TYPE_INT &&
      node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }
  
  if (node->right()->type()->name() == basic_type::TYPE_DOUBLE ||
      node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.DDIV();
  }
  else {
    _pf.DIV();
  }
}
void gr8::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
void gr8::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  if (node->left()->type()->name() == basic_type::TYPE_INT &&
      node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }

  node->right()->accept(this, lvl);
  if (node->right()->type()->name() == basic_type::TYPE_INT &&
      node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }
  
  if (node->left()->type()->name() == basic_type::TYPE_DOUBLE ||
      node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
    
    _pf.DCMP();
    _pf.INT(0);
    _pf.LT();
  } else {
    _pf.LT();
  }
}
void gr8::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  if (node->left()->type()->name() == basic_type::TYPE_INT &&
      node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }

  node->right()->accept(this, lvl);
  if (node->right()->type()->name() == basic_type::TYPE_INT &&
      node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }
  
  if (node->left()->type()->name() == basic_type::TYPE_DOUBLE ||
      node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
    
    _pf.DCMP();
    _pf.INT(0);
    _pf.GT();
  } else {
    _pf.GT();
  }
}
void gr8::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  if (node->left()->type()->name() == basic_type::TYPE_INT &&
      node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }

  node->right()->accept(this, lvl);
  if (node->right()->type()->name() == basic_type::TYPE_INT &&
      node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }
  
  if (node->left()->type()->name() == basic_type::TYPE_DOUBLE ||
      node->right()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.DCMP();
    _pf.INT(0);
    _pf.EQ();
  } else {
    _pf.EQ();
  }

}
void gr8::postfix_writer::do_and_node(cdk::and_node * const node, int lvl) {
  int end = ++_lbl;

  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  
  _pf.JZ(mklbl(end));

  _pf.INT(1);
  node->right()->accept(this, lvl);
  _pf.AND();
  
  _pf.ALIGN();
  _pf.LABEL(mklbl(end));
}
void gr8::postfix_writer::do_or_node(cdk::or_node * const node, int lvl) {
  int end = ++_lbl;

  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  
  _pf.JNZ(mklbl(end));

  _pf.INT(0);
  node->right()->accept(this, lvl);
  _pf.OR();
  
  _pf.ALIGN();
  _pf.LABEL(mklbl(end));
}


void gr8::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LE();
}
void gr8::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GE();
}
void gr8::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.NE();
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  std::map<std::string,int>::iterator it;
  it = _variableOffset.find(node->name());
  if (it != _variableOffset.end()) {
    _pf.LOCAL(_variableOffset.at(node->name()));
  }
  else {
    _pf.ADDR(node->name());
  }
}

void gr8::postfix_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->lvalue()->accept(this, lvl);
  auxiliaryLoad(node->type());
}

void gr8::postfix_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  node->rvalue()->accept(this, lvl);

  if (node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE &&
      node->rvalue()->type()->name() == basic_type::TYPE_INT)
    _pf.I2D();

  if (_allocateObjects) {
    gr8::objects_node* obj = dynamic_cast<gr8::objects_node*>(node->rvalue());
    if (obj == nullptr) throw "should be objects node!";
    allocObjects(obj);
  }

  if (new_symbol() != nullptr) {
    node->lvalue()->accept(this, lvl);
  } else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
  }

  if (node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE) _pf.STDOUBLE(); else _pf.STINT();

  reset_new_symbol();
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {
  //ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl);
  if (node->argument()->type() == nullptr) return;
  
  if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.TRASH(8);
  } else {
    _pf.TRASH(4);
  }
}

void gr8::postfix_writer::do_print_node(gr8::print_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value to print
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
    } else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.CALL("printd");
    _pf.TRASH(8); // delete the printed value's address
  } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  } else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }

  if (node->newLine()) {
    _pf.CALL("println"); // print a newline
  }
}

void gr8::postfix_writer::do_if_node(gr8::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int end = ++_lbl;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(end));
  node->block()->accept(this, lvl + 2);
  _pf.ALIGN();
  _pf.LABEL(mklbl(end));
}

void gr8::postfix_writer::do_if_else_node(gr8::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int else_label = ++_lbl;
  int end = ++_lbl;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(else_label));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(end));
  _pf.ALIGN();
  _pf.LABEL(mklbl(else_label));
  node->elseblock()->accept(this, lvl + 2);
  _pf.ALIGN();
  _pf.LABEL(mklbl(end));
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_address_node(gr8::address_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->variable()->accept(this, lvl);
}

void gr8::postfix_writer::do_again_node(gr8::again_node * const node, int lvl) {
  _pf.JMP(sweepingAgainLabels.at(sweepingAgainLabels.size() - node->number()));
}

void gr8::postfix_writer::do_block_node(gr8::block_node * const node, int lvl) {
  if (node->declarations() != nullptr) node->declarations()->accept(this, lvl);
  if (node->instructions() != nullptr) node->instructions()->accept(this, lvl);
  _symtab.pop();
}

void gr8::postfix_writer::do_cell_node(gr8::cell_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  node->value()->accept(this, lvl);
  node->indexing()->accept(this, lvl);

  if (node->type()->name() == basic_type::TYPE_DOUBLE) _pf.INT(8); else _pf.INT(4);
  _pf.MUL();
  _pf.ADD();
}

void gr8::postfix_writer::do_function_call_node(gr8::function_call_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  if (node->arguments() != nullptr && node->arguments()->size() > 0) {
    std::shared_ptr<gr8::symbol> symbol = _symtab.find(node->functionName());
    if (symbol == nullptr) throw "can't call undefined function!";
    //Calculate byte size for function parameters
    for (int i = node->arguments()->size() - 1; i >= 0; --i) {
      node->arguments()->node(i)->accept(this, lvl);
      cdk::typed_node* typ = dynamic_cast<cdk::typed_node*>(node->arguments()->node(i));
      if (typ == nullptr) throw "must have type!";
      if (typ->type()->name() == basic_type::TYPE_INT &&
          symbol->params().at(i).name() == basic_type::TYPE_DOUBLE) {
        _pf.I2D();
      }
    }
  }
  _pf.CALL(node->functionName());
  if (_bytesOffset > 0) _pf.TRASH(_bytesOffset);
  _bytesOffset = 0;
  //Put value from eax in stack
  if (node->type() != nullptr) {
    if (node->type()->name() == basic_type::TYPE_DOUBLE) _pf.LDFVAL64(); else _pf.LDFVAL32();
  }
}

void gr8::postfix_writer::do_function_dec_node(gr8::function_dec_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
}

void gr8::postfix_writer::do_function_def_node(gr8::function_def_node * const node, int lvl) {
  gr8::function_dec_node* declaration = new gr8::function_dec_node(node);
  do_function_dec_node(declaration, lvl); 
  ASSERT_SAFE_EXPRESSIONS;
  
  std::string id = "";
  if (node->functionName().compare("covfefe") == 0) {
    id = "_main";
  }
  else if (node->functionName().compare("_main") == 0) {
    id = "_main_.";
  }
  else {
    id = node->functionName();
  }
  _pf.ALIGN();
  _pf.LABEL(id);
  if (node->access() == gr8::access_specifier::_public) _pf.GLOBAL(id, _pf.FUNC());
  else if (node->access() == gr8::access_specifier::_use) _pf.EXTERN(id);

  _symtab.push();
  setInFunction(true);
  _callAllocking = true;
  if (node->arguments() != nullptr && node->arguments()->size() > 0) {
    for (int i = node->arguments()->size() - 1; i >= 0; --i) {
      node->arguments()->node(i)->accept(this, lvl);
    }
    _callStackBytes.clear();
  }
  _callAllocking = false;

  _bytesOffset = 0;
  _totalBytes = 0;
  VISIT_VARIABLES;
  _pf.ENTER(_totalBytes);

  _functionEndLabel = ++_lbl;

  node->block()->accept(this, lvl);
  if (node->type() != nullptr && !returned()) throw "non-procedure function didn't return!";
  setReturned(false);

  _pf.ALIGN();
  _pf.LABEL(mklbl(_functionEndLabel));
  _functionEndLabel = 0;

  _pf.LEAVE();
  _pf.RET();

  setFunctionType(nullptr);
  setInFunction(false);
  _bytesOffset = 0;
  _variableOffset.clear();
}

void gr8::postfix_writer::do_input_node(gr8::input_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  if (node->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("readi");
  }
  else {
    _pf.CALL("readd");
  }
  _pf.LDFVAL32();
  if (node->type()->name() == basic_type::TYPE_INT) {
    _pf.STINT();
  }
  else {
    _pf.STDOUBLE();
  }
}

void gr8::postfix_writer::do_null_node(gr8::null_node * const node, int lvl) {
  //EMPTY
}

void gr8::postfix_writer::do_objects_node(gr8::objects_node * const node, int lvl) {
  //EMPTY
}

void gr8::postfix_writer::do_return_node(gr8::return_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  node->returnValue()->accept(this, lvl);
  if (node->returnValue()->type()->name() == basic_type::TYPE_INT &&
      functionType()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
    _pf.STFVAL64();
  }
  else {
    if (node->returnValue()->type()->name() == basic_type::TYPE_DOUBLE) _pf.STFVAL64(); else _pf.STFVAL32();
  }
  setReturned(true);
  _pf.JMP(mklbl(_functionEndLabel));
}

void gr8::postfix_writer::do_stop_node(gr8::stop_node * const node, int lvl) {
  _pf.JMP(sweepingStopLabels.at(sweepingStopLabels.size() - node->number()));
}

void gr8::postfix_writer::do_sweeping_node(gr8::sweeping_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int condition = ++_lbl;
  int beforeJump = ++_lbl;
  int greater = ++_lbl;
  int less = ++_lbl;
  int end = ++_lbl;
  int increment = ++_lbl;

  sweepingAgainLabels.push_back(mklbl(increment));
  sweepingStopLabels.push_back(mklbl(end));

  node->from()->accept(this, lvl);
  _pf.DUP32();
  
  //Set lvalue to FROM
  node->lvalue()->accept(this, lvl);
  _pf.STINT();
  //Add TO to stack
  node->to()->accept(this, lvl);
  //Start the loop
  _pf.JMP(mklbl(condition));

  //Add lvalue and TO to stack
  node->lvalue()->accept(this, lvl);
  _pf.LDINT();
  node->to()->accept(this, lvl);

  //Start of condition
  _pf.ALIGN();
  _pf.LABEL(mklbl(condition));

  //Check if BY > 0
  if (node->by() != nullptr) node->by()->accept(this, lvl); else _pf.INT(1);
  _pf.INT(0);
  _pf.LT();
  _pf.JNZ(mklbl(less));

  _pf.JMP(mklbl(greater));

  //If BY == 0, go to end of cicle
  _pf.JMP(mklbl(end));

  //BY < 0
  _pf.ALIGN();
  _pf.LABEL(mklbl(less));
  _pf.LT();
  _pf.JMP(mklbl(beforeJump));

  //BY > 0
  _pf.ALIGN();
  _pf.LABEL(mklbl(greater));
  _pf.GT();

  _pf.ALIGN();
  _pf.LABEL(mklbl(beforeJump));
  _pf.JNZ(mklbl(end));

  //------------------------------------------------------------

  //Execute instruction block
  node->block()->accept(this, lvl);

  _pf.ALIGN();
  _pf.LABEL(mklbl(increment));
  //Increment lvalue
  node->lvalue()->accept(this, lvl);
  _pf.LDINT();
  if (node->by() != nullptr) {
    node->by()->accept(this, lvl);
  } else {
    _pf.INT(1);
  }
  _pf.ADD();
  node->lvalue()->accept(this, lvl);
  _pf.STINT();

  //Add lvalue and TO to stack
  node->lvalue()->accept(this, lvl);
  _pf.LDINT();
  node->to()->accept(this, lvl);

  //Re-evaluate lvalue and TO
  _pf.JMP(mklbl(condition));

  //End sweeping
  _pf.ALIGN();
  _pf.LABEL(mklbl(end));

  sweepingStopLabels.pop_back();
  sweepingAgainLabels.pop_back();

  reset_new_symbol();
}

void gr8::postfix_writer::do_variable_node(gr8::variable_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  if (node->access() != gr8::access_specifier::_use) {
    if (inFunction()) {
      localVariable(node);
    } else {
      globalVariable(node);
    }
  }
  else {
    if (node->value() != nullptr) throw "cannot initialize external variable!";
    _pf.EXTERN(node->name());
  }
  reset_new_symbol();
}

void gr8::postfix_writer::localVariable(gr8::variable_node * const node) {
  if (_callAllocking) {
    int varOffset = _callStackBytes.back();
    _callStackBytes.pop_back();
    _variableOffset.insert(std::make_pair(node->name(), 8+varOffset));
    _bytesOffset += node->type()->name() == basic_type::TYPE_DOUBLE ? 8 : 4;
  }
  else {
    //Value
    if (node->value() != nullptr) {
      node->value()->accept(this, 0);

      if (_allocateObjects) {
        gr8::objects_node* obj = dynamic_cast<gr8::objects_node*>(node->value());
        if (obj == nullptr) throw "should be objects node!";
        allocObjects(obj);
      }
    }
    gr8::null_node* null_node = dynamic_cast<gr8::null_node*>(node->value());

    //Calculate offset
    _variableOffset.insert(std::make_pair(node->name(), -4-_bytesOffset));
    if (node->value() != nullptr && null_node == nullptr) _pf.LOCAL(-4-_bytesOffset);
    _bytesOffset += node->type()->name() == basic_type::TYPE_DOUBLE ? 8 : 4;

    //Store
    if (node->value() != nullptr && null_node == nullptr){
      if (node->value()->type()->name() == basic_type::TYPE_DOUBLE) _pf.STDOUBLE(); else _pf.STINT();
    }
  }
}

void gr8::postfix_writer::globalVariable(gr8::variable_node * const node) {
  //Pointers and string save an address to data, not data directly
  if (node->type()->name() != basic_type::TYPE_STRING &&
      node->type()->name() != basic_type::TYPE_POINTER) {
    _pf.DATA();
    _pf.ALIGN();
    if (node->access() == gr8::access_specifier::_public) _pf.GLOBAL(node->name(), _pf.OBJ());
    _pf.LABEL(node->name());
  }
  //Value
  if (node->value() != nullptr) {
    varValidValue(node);
  }
  else {
    varNullValue(node);
  }
  _pf.TEXT();
}

void gr8::postfix_writer::varValidValue(gr8::variable_node * const node) {
  if (node->type()->name() == basic_type::TYPE_INT) {
    cdk::integer_node* integer = dynamic_cast<cdk::integer_node*>(node->value());
    _pf.SINT(integer->value());
  } else if (node->type()->name() == basic_type::TYPE_DOUBLE) {
    cdk::double_node* doubl = dynamic_cast<cdk::double_node*>(node->value());
    if (doubl == nullptr) {
      cdk::integer_node* integer = dynamic_cast<cdk::integer_node*>(node->value());
      _pf.SDOUBLE(integer->value());
    }
    else {
      _pf.SDOUBLE(doubl->value());
    }
  } else if (node->type()->name() == basic_type::TYPE_STRING) {
    cdk::string_node* str = dynamic_cast<cdk::string_node*>(node->value());
    int strlbl = ++_lbl;
    _pf.RODATA();
    _pf.ALIGN();
    _pf.LABEL(mklbl(strlbl));
    _pf.SSTRING(str->value());

    _pf.DATA();
    if (node->access() == gr8::access_specifier::_public) _pf.GLOBAL(node->name(), _pf.OBJ());
    _pf.LABEL(node->name());
    _pf.SADDR(mklbl(strlbl));
  } else if (node->type()->name() == basic_type::TYPE_POINTER) {
    int ptrlbl = ++_lbl;
    basic_type* rootType = getPointerRoot(node->type());

    if (rootType->name() == basic_type::TYPE_STRING) _pf.RODATA(); else _pf.DATA();
    _pf.ALIGN();
    _pf.LABEL(mklbl(ptrlbl));
    if (rootType->name() == basic_type::TYPE_INT) {
      _pf.SINT(0);
    } else if (rootType->name() == basic_type::TYPE_DOUBLE) {
      _pf.SDOUBLE(0.0);
    } else if (rootType->name() == basic_type::TYPE_STRING) {
      _pf.SSTRING("");
    }

    _pf.ALIGN();
    if (node->access() == gr8::access_specifier::_public) _pf.GLOBAL(node->name(), _pf.OBJ());
    _pf.LABEL(node->name());
    _pf.SADDR(mklbl(ptrlbl));
  }
}

void gr8::postfix_writer::varNullValue(gr8::variable_node * const node) {
  if (node->type()->name() == basic_type::TYPE_INT) {
    _pf.SINT(0);
  } else if (node->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.SDOUBLE(0.0);
  } else if (node->type()->name() == basic_type::TYPE_STRING) {
    int strlbl = ++_lbl;
    _pf.RODATA();
    _pf.ALIGN();
    _pf.LABEL(mklbl(strlbl));
    _pf.SSTRING("");

    _pf.DATA();
    if (node->access() == gr8::access_specifier::_public) _pf.GLOBAL(node->name(), _pf.OBJ());
    _pf.LABEL(node->name());
    _pf.SADDR(mklbl(strlbl));
  } else if (node->type()->name() == basic_type::TYPE_POINTER) {
    int ptrlbl = ++_lbl;
    basic_type* rootType = getPointerRoot(node->type());

    if (rootType->name() == basic_type::TYPE_STRING) _pf.RODATA(); else _pf.DATA();
    _pf.ALIGN();
    _pf.LABEL(mklbl(ptrlbl));
    if (rootType->name() == basic_type::TYPE_INT) {
      _pf.SINT(0);
    } else if (rootType->name() == basic_type::TYPE_DOUBLE) {
      _pf.SDOUBLE(0.0);
    } else if (rootType->name() == basic_type::TYPE_STRING) {
      _pf.SSTRING("");
    }

    _pf.ALIGN();
    if (node->access() == gr8::access_specifier::_public) _pf.GLOBAL(node->name(), _pf.OBJ());
    _pf.LABEL(node->name());
    _pf.SADDR(mklbl(ptrlbl));
  }
}