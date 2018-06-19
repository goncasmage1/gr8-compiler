#include <string>
#include <vector>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }
#define ASSERT_INT(typ) \
    { if (typ->name() != basic_type::TYPE_INT) throw std::string("isn't an int."); }
#define ASSERT_NUMBER(typ) \
    { if (typ->name() != basic_type::TYPE_DOUBLE && \
        typ->name() != basic_type::TYPE_INT) throw std::string("isn't a double."); }
#define ASSERT_STRING(typ) \
    { if (typ->name() != basic_type::TYPE_STRING) throw std::string("isn't a string."); }
#define ASSERT_POINTER(typ) \
    { if (typ->name() != basic_type::TYPE_POINTER) throw std::string("isn't a pointer."); }
#define ASSERT_NOT_POINTER(typ) \
    { if (typ->name() == basic_type::TYPE_POINTER) throw std::string("can't be a pointer."); }
#define ASSERT_EQUAL_TYPES(typ1, typ2) \
    { if (typ1->name() != typ2->name() && \
          ((typ1->name() != basic_type::TYPE_DOUBLE && typ1->name() != basic_type::TYPE_INT) || \
          (typ2->name() != basic_type::TYPE_DOUBLE && typ2->name() != basic_type::TYPE_INT))) throw std::string("different types"); }

//---------------------------------------------------------------------------

void gr8::type_checker::do_nil_node(cdk::nil_node * const node, int lvl) {
}
void gr8::type_checker::do_data_node(cdk::data_node * const node, int lvl) {
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl + 2);
  }
}

bool gr8::type_checker::verifyIfRead(basic_type* left, basic_type* right) {
  //Set potencial input node type
  if (left->name() == basic_type::TYPE_VOID) {
    if (right->name() == basic_type::TYPE_INT) {
      left = new basic_type(4, basic_type::TYPE_INT);
    }
    else if (right->name() == basic_type::TYPE_DOUBLE) {
      left = new basic_type(8, basic_type::TYPE_DOUBLE);
    }
    else {
      throw "input can only read numbers";
    }
    return true;
  }
  else if (right->name() == basic_type::TYPE_VOID) {
    if (left->name() == basic_type::TYPE_INT) {
      right = new basic_type(4, basic_type::TYPE_INT);
    }
    else if (left->name() == basic_type::TYPE_DOUBLE) {
      right = new basic_type(8, basic_type::TYPE_DOUBLE);
    }
    else {
      throw "input can only read numbers";
    }
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void gr8::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void gr8::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

//---------------------------------------------------------------------------

void gr8::type_checker::processUnaryExpression_I_D(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT &&
      node->argument()->type()->name() != basic_type::TYPE_DOUBLE) throw std::string("wrong type in argument of unary expression");

  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    node->type(new basic_type(4, basic_type::TYPE_INT));
  }
  else {
    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  }
}

void gr8::type_checker::processUnaryExpression_I(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT) throw std::string("wrong type in argument of unary expression");

  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void gr8::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression_I_D(node, lvl);
}

void gr8::type_checker::do_identity_node(gr8::identity_node * const node, int lvl) {
  processUnaryExpression_I_D(node, lvl);
}

void gr8::type_checker::do_not_node(cdk::not_node * const node, int lvl) {
  processUnaryExpression_I(node, lvl);
}

void gr8::type_checker::do_address_node(gr8::address_node * const node, int lvl) {
  node->variable()->accept(this, lvl);

  basic_type* newType = new basic_type(4, basic_type::TYPE_POINTER);
  newType->_subtype = node->variable()->type();
  node->type(newType);
}

void gr8::type_checker::do_objects_node(gr8::objects_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  node->type(new basic_type(4, basic_type::TYPE_STRUCT));
  //node->type()->_subtype = _parent->new_symbol()->type();
}

//---------------------------------------------------------------------------

void gr8::type_checker::processBinaryExpression_I_D_P(cdk::binary_expression_node * const node, bool forceInt, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);

  if (verifyIfRead(node->left()->type(), node->right()->type())) {
    if (node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
      node->type(new basic_type(4, basic_type::TYPE_DOUBLE));
    } else {
      node->type(new basic_type(4, basic_type::TYPE_INT));
    }
  }
  else {
    if (node->left()->type()->name() != basic_type::TYPE_POINTER &&
        node->right()->type()->name() != basic_type::TYPE_POINTER) {
      ASSERT_NUMBER(node->left()->type());
      ASSERT_NUMBER(node->right()->type());

      if ((node->left()->type()->name() == basic_type::TYPE_INT && 
          node->right()->type()->name() == basic_type::TYPE_INT) ||
          forceInt) {
        node->type(new basic_type(4, basic_type::TYPE_INT));
      }
      else {
        node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
      }
    }
  }
}

void gr8::type_checker::processBinaryExpression_I_D(cdk::binary_expression_node * const node, bool forceInt, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);

  if (verifyIfRead(node->left()->type(), node->right()->type())) {
    if (node->left()->type()->name() == basic_type::TYPE_DOUBLE) {
      node->type(new basic_type(4, basic_type::TYPE_DOUBLE));
    } else {
      node->type(new basic_type(4, basic_type::TYPE_INT));
    }
  }
  else {
    ASSERT_NUMBER(node->left()->type());
    ASSERT_NUMBER(node->right()->type());

    if ((node->left()->type()->name() == basic_type::TYPE_INT && 
        node->right()->type()->name() == basic_type::TYPE_INT) ||
        forceInt) {
      node->type(new basic_type(4, basic_type::TYPE_INT));
    }
    else {
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
    }
  }
}

void gr8::type_checker::processBinaryExpression_I(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);

  if (verifyIfRead(node->left()->type(), node->right()->type())) {
    if (node->left()->type()->name() != basic_type::TYPE_DOUBLE) throw "int expected.";
    node->type(new basic_type(4, basic_type::TYPE_INT));
  }
  else {
    ASSERT_INT(node->left()->type());
    ASSERT_INT(node->right()->type());

    node->type(new basic_type(4, basic_type::TYPE_INT));
  }
}

void gr8::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression_I_D_P(node, false, lvl);
  if (node->left()->type()->name() == basic_type::TYPE_POINTER &&
      node->right()->type()->name() == basic_type::TYPE_INT) {
    basic_type* newType = new basic_type(4, basic_type::TYPE_POINTER);
    newType->_subtype = node->left()->type()->_subtype;
    node->type(newType);
  }
  else if (node->right()->type()->name() == basic_type::TYPE_POINTER &&
          node->left()->type()->name() == basic_type::TYPE_INT) {
    basic_type* newType = new basic_type(4, basic_type::TYPE_POINTER);
    newType->_subtype = node->right()->type()->_subtype;
    node->type(newType);
  }
}
void gr8::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression_I_D_P(node, false, lvl);
  if (node->left()->type()->name() == basic_type::TYPE_POINTER &&
      node->right()->type()->name() == basic_type::TYPE_INT) {
    basic_type* newType = new basic_type(4, basic_type::TYPE_POINTER);
    newType->_subtype = node->left()->type()->_subtype;
    node->type(newType);
  }
  else if (node->right()->type()->name() == basic_type::TYPE_POINTER &&
      node->left()->type()->name() == basic_type::TYPE_INT) {
    basic_type* newType = new basic_type(4, basic_type::TYPE_POINTER);
    newType->_subtype = node->right()->type()->_subtype;
    node->type(newType);
  }
}
void gr8::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression_I_D(node, false, lvl);
}
void gr8::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression_I_D(node, false, lvl);
}
void gr8::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression_I(node, lvl);
}
void gr8::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression_I_D(node, true, lvl);
}
void gr8::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression_I_D(node, true, lvl);
}
void gr8::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression_I_D(node, true, lvl);
}
void gr8::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression_I_D(node, true, lvl);
}
void gr8::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression_I_D_P(node, true, lvl);
}
void gr8::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression_I_D_P(node, true, lvl);
  if (node->left()->type()->name() == basic_type::TYPE_POINTER) {
    if (node->right()->type()->name() != basic_type::TYPE_POINTER) throw "comparing pointer with non-pointer.";
  }
}
void gr8::type_checker::do_and_node(cdk::and_node * const node, int lvl) {
  processBinaryExpression_I(node, lvl);
}
void gr8::type_checker::do_or_node(cdk::or_node * const node, int lvl) {
  processBinaryExpression_I(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_UNSPEC;
  const std::string &id = node->name();
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);

  if (symbol != nullptr) {
    _parent->set_new_symbol(symbol);  
    node->type(symbol->type());
  } else {
    throw "undeclared variable '" + id + "'";
  }
}

void gr8::type_checker::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_UNSPEC;
  //Save new_symbol
  //std::shared_ptr<gr8::symbol> previousSymbol = _parent->new_symbol();
  node->lvalue()->accept(this, lvl);
  node->type(node->lvalue()->type());
  //_parent->set_new_symbol(previousSymbol);
}

void gr8::type_checker::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->lvalue()->accept(this, lvl);
  if (_parent->new_symbol()->function()) throw "cannot assign expression to function.";
  node->rvalue()->accept(this, lvl + 2);

  if (!verifyIfRead(node->lvalue()->type(), node->rvalue()->type())) {
    //Check if objects node
    if (node->rvalue()->type()->name() == basic_type::TYPE_STRUCT) {
      if (node->lvalue()->type()->name() == basic_type::TYPE_POINTER) {
        basic_type* newType = node->lvalue()->type()->_subtype;
        gr8::objects_node* obj = dynamic_cast<gr8::objects_node*>(node->rvalue());
        if (obj == nullptr) throw "should be objects node!";
        if (newType->name() == basic_type::TYPE_INT) {
          obj->type(new basic_type(4, basic_type::TYPE_INT));
        } else if (newType->name() == basic_type::TYPE_DOUBLE) {
          obj->type(new basic_type(8, basic_type::TYPE_DOUBLE));
        } else if (newType->name() == basic_type::TYPE_STRING) {
          obj->type(new basic_type(4, basic_type::TYPE_STRING));
        } else if (newType->name() == basic_type::TYPE_POINTER) {
          obj->type(new basic_type(4, basic_type::TYPE_POINTER));
        }
        _parent->_allocateObjects = true;
      }
      else {
        throw "can only allocate objects to pointers";
      }
    }
    else {
      if (node->lvalue()->type()->name() == basic_type::TYPE_POINTER) {
        ASSERT_EQUAL_TYPES(node->lvalue()->type(), node->rvalue()->type());
      }
      else {
        ASSERT_EQUAL_TYPES(node->lvalue()->type(), node->rvalue()->type());
      }

      if (node->lvalue()->type()->name() == basic_type::TYPE_INT &&
          node->rvalue()->type()->name() == basic_type::TYPE_DOUBLE)
        throw "cannot assign double to int.";
    }
  }
  node->type(new basic_type(4, basic_type::TYPE_VOID));
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void gr8::type_checker::do_print_node(gr8::print_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  ASSERT_NOT_POINTER(node->argument()->type());

  if (node->argument()->type()->name() == basic_type::TYPE_VOID) {
    node->argument()->type(new basic_type(4, basic_type::TYPE_INT));
  }
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_if_node(gr8::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
  ASSERT_INT(node->condition()->type());
  //node->block()->accept(this, lvl);
}

void gr8::type_checker::do_if_else_node(gr8::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
  ASSERT_INT(node->condition()->type());
  //node->thenblock()->accept(this, lvl);
  //node->elseblock()->accept(this, lvl);
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_again_node(gr8::again_node * const node, int lvl) {
  if (_parent->forDepth() == 0) throw "again can't be used here";
  if (_parent->forDepth() < node->number()) throw "again keyword parameter too high";
  if (node->number() < 0) throw "again has to receive a positive parameter";
}

void gr8::type_checker::do_block_node(gr8::block_node * const node, int lvl) {
  if (node->declarations() != nullptr) node->declarations()->accept(this, lvl);
  if (node->instructions() != nullptr) node->instructions()->accept(this, lvl);
}

void gr8::type_checker::do_cell_node(gr8::cell_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->indexing()->accept(this, lvl);

  if (node->indexing()->type()->name() == basic_type::TYPE_VOID) {
    node->indexing()->type(new basic_type(4, basic_type::TYPE_INT));
  }

  ASSERT_INT(node->indexing()->type());

  node->value()->accept(this, lvl);
  ASSERT_POINTER(node->value()->type());
  if (node->value()->type()->_subtype != nullptr) {
    node->type(node->value()->type()->subtype());
  }
  else {
    throw "trying to access empty pointer.";
  }
}

void gr8::type_checker::do_function_call_node(gr8::function_call_node * const node, int lvl) {
  ASSERT_UNSPEC;
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(node->functionName());

  if (symbol != nullptr) {
    if (!symbol->function()) throw "'" + node->functionName() + "' isn't a function.";

    if (node->arguments() != nullptr) { 
      if (node->arguments()->size() == symbol->params().size()) {
        if (node->arguments()->size() > 0) {
          for (size_t i = 0; i < node->arguments()->size(); i++) {
            cdk::typed_node* param = (cdk::typed_node*) node->arguments()->node(i);
            if (param == nullptr) std::cerr << "ERROR (type_checker): MUST HAVE TYPE" << std::endl;
            param->accept(this, lvl);
            try {
              basic_type direct_type = symbol->params().at(i);
              basic_type* param_type = &direct_type;
              ASSERT_EQUAL_TYPES(param->type(), param_type);
            } catch (std::string& e) {
              throw "parameter " + std::to_string(i) + " incoherent with '" + node->functionName() + "' function definition";
            }
          }
        }
      } else {
        throw "number of parameters in function '" + node->functionName() + "' call and definition are different.";
      }
    } 
    else {
      if (symbol->params().size() != 0) throw "number of parameters in function '" + node->functionName() + "' call and definition are different.";
    }
  } else {
    throw "function '" + node->functionName() + "' doesn't exist";
  }
  node->type(symbol->type());
}

void gr8::type_checker::do_function_dec_node(gr8::function_dec_node * const node, int lvl) {
  std::string nome = node->functionName();
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(nome);
  
  if (symbol != nullptr) {
    if (!node->fromDefinition()) throw "identifier '" + nome + "' already exists.";
  } else {
    std::vector<basic_type> types;
    std::shared_ptr<gr8::symbol> newSymbol;
    if (node->arguments() != nullptr) {
      for (size_t i = 0; i < node->arguments()->size(); i++) {
        gr8::variable_node* var = (gr8::variable_node*) node->arguments()->node(i);
        types.push_back(*(var->type()));
      }
      newSymbol = std::make_shared<gr8::symbol>(node->type(), nome, true, node->access(), node->arguments()->size(), types);
    }
    else {
      newSymbol = std::make_shared<gr8::symbol>(node->type(), nome, true, node->access(), 0, types);
    }
    _symtab.insert(nome, newSymbol);
    _parent->set_new_symbol(newSymbol);
    _parent->_undefinedFunctions.insert(nome);
  }
}

void gr8::type_checker::do_function_def_node(gr8::function_def_node * const node, int lvl) {
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(node->functionName());

  std::string nome = node->functionName();

  if (symbol != nullptr) {
    //Remove from undeclared functions set
    std::set<std::string>::iterator elem = _parent->_undefinedFunctions.find(nome);
    if (elem != _parent->_undefinedFunctions.end()) {
      _parent->_undefinedFunctions.erase(elem);
    }
    if (node->arguments() != nullptr && node->arguments()->size() > 0) {
      int callBytes = 0;
      for (size_t i = 0; i < node->arguments()->size(); ++i) {
        gr8::variable_node* var = dynamic_cast<gr8::variable_node*>(node->arguments()->node(i));
        if (var == nullptr) throw "must be variable";
        _parent->_callStackBytes.push_back(callBytes);
        callBytes += var->type()->name() == basic_type::TYPE_DOUBLE ? 8 : 4;
      }
    }
  }
  else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
  }

  if (node->type() != nullptr) _parent->setReturned(true);
  _parent->setFunctionType(node->type());
}

void gr8::type_checker::do_input_node(gr8::input_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(0, basic_type::TYPE_VOID));
}

void gr8::type_checker::do_null_node(gr8::null_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_POINTER));
}

void gr8::type_checker::do_return_node(gr8::return_node * const node, int lvl) {
  node->returnValue()->accept(this, lvl);
  if (_parent->functionType() == nullptr) { 
    throw "return used innapropriately";
  }

  ASSERT_EQUAL_TYPES(_parent->functionType(), node->returnValue()->type());
  if (_parent->functionType()->name() == basic_type::TYPE_INT &&
      node->returnValue()->type()->name() == basic_type::TYPE_DOUBLE)
    throw "trying to return double when int is expected.";

}

void gr8::type_checker::do_stop_node(gr8::stop_node * const node, int lvl) {
  if (_parent->forDepth() == 0) throw "stop can't be used here";
  if (_parent->forDepth() < node->number()) throw "stop keyword parameter too high";
  if (node->number() < 0) throw "stop has to receive a positive parameter";
}

void gr8::type_checker::do_sweeping_node(gr8::sweeping_node * const node, int lvl) {
  node->lvalue()->accept(this, lvl);
  ASSERT_INT(_parent->new_symbol()->type());
  if (_parent->new_symbol()->function()) throw "sweeping can't accept function identifiers.";

  node->from()->accept(this, lvl);
  ASSERT_INT(node->from()->type());

  node->to()->accept(this, lvl);
  ASSERT_INT(node->to()->type());

  if (node->by() != nullptr) {
    node->by()->accept(this, lvl);
    ASSERT_INT(node->by()->type());
  }

  _parent->incrementForDepth();
  _parent->decrementForDepth();
}

void gr8::type_checker::do_variable_node(gr8::variable_node * const node, int lvl) {
  //Verify if identifier exists
  const std::string &id = node->name();
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);
  if (symbol != nullptr) {
    std::shared_ptr<gr8::symbol> localSymbol = _symtab.find_local(id);
    if (localSymbol != nullptr) throw "already declared symbol '" + id + "'";
    symbol = std::make_shared<gr8::symbol>(node->type(), id, false, gr8::access_specifier::_none, 0, std::vector<basic_type>());
    _symtab.insert(id, symbol);
    _parent->set_new_symbol(symbol);
  }
  else {
    symbol = std::make_shared<gr8::symbol>(node->type(), id, false, node->access(), 0, std::vector<basic_type>());
    _symtab.insert(id, symbol);
    _parent->set_new_symbol(symbol);
  }

  //Verify value type
  if (node->value() != nullptr) {
    if (node->access() == gr8::access_specifier::_use) throw "can't reinitialize a variable from another file.";
    node->value()->accept(this, lvl);
    //Set objects node type
    if (node->value()->type()->name() == basic_type::TYPE_STRUCT) {
      if (node->type()->name() == basic_type::TYPE_POINTER) {
        basic_type* newType = node->type()->_subtype;
        if (newType->name() == basic_type::TYPE_INT) {
          node->value()->type(new basic_type(4, basic_type::TYPE_INT));
        } else if (newType->name() == basic_type::TYPE_DOUBLE) {
          node->value()->type(new basic_type(8, basic_type::TYPE_DOUBLE));
        } else if (newType->name() == basic_type::TYPE_STRING) {
          node->value()->type(new basic_type(4, basic_type::TYPE_STRING));
        } else if (newType->name() == basic_type::TYPE_POINTER) {
          node->value()->type(new basic_type(4, basic_type::TYPE_POINTER));
        }
        _parent->_allocateObjects = true;
      }
      else {
        throw "can only assign objects to pointers";
      }
    }
    ASSERT_EQUAL_TYPES(node->value()->type(), node->type());
  }

}