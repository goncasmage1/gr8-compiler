#ifndef __GR8_BASIC_AST_VISITOR_H__
#define __GR8_BASIC_AST_VISITOR_H__

#include <string>
#include <memory>
#include <set>
#include <iostream>
#include <cdk/compiler.h>
#include <cdk/basic_type.h>
#include "symbol.h"

/* do not edit -- include node forward declarations */
#define __NODE_DECLARATIONS_ONLY__
#include "ast/all.h"  // automatically generated
#undef __NODE_DECLARATIONS_ONLY__
/* do not edit -- end */

//!
//! Print nodes as XML elements to the output stream.
//!
class basic_ast_visitor {
protected:
  //! The owner compiler
  std::shared_ptr<cdk::compiler> _compiler;

  std::vector<std::string> sweepingStopLabels;
  std::vector<std::string> sweepingAgainLabels;

  basic_type* _functionType;
  bool _inFunction = false;

  int _stop = 0;
  int _again = 0;
  int _forDepth = 0;

  std::map<std::string, int> _variableOffset;
  int _bytesOffset = 0;

  bool _callAllocking = false;
  bool _returned = false;

  int _totalBytes = 0;

private:

  // last symbol inserted in symbol table
  std::shared_ptr<gr8::symbol> _new_symbol;

protected:
  basic_ast_visitor(std::shared_ptr<cdk::compiler> compiler) :
      _compiler(compiler) {
  }

  bool debug() {
    return _compiler->debug();
  }

  std::ostream &os() {
    return *_compiler->ostream();
  }

public:
  virtual ~basic_ast_visitor() {
  }

public:

  std::set<std::string> _undefinedFunctions;
  std::vector<int> _callStackBytes;
  int _functionEndLabel = 0;

  bool _allocateObjects = false;

  std::shared_ptr<gr8::symbol> new_symbol() {
    return _new_symbol;
  }

  void set_new_symbol(std::shared_ptr<gr8::symbol> symbol) {
    _new_symbol = symbol;
  }

  void reset_new_symbol() {
    _new_symbol = nullptr;
  }

  void setFunctionType(basic_type* funcType) {
    _functionType = funcType;
  }

  basic_type* functionType() {
    return _functionType;
  }

  int forDepth() const {
    return _forDepth;
  }

  void incrementForDepth() {
    _forDepth++;
  }
  
  void decrementForDepth() {
    _forDepth--;
  }

  void setInFunction(bool inFunc) {
    _inFunction = inFunc;
  }

  bool inFunction() {
    return _inFunction;
  }

  void setTotalBytes(int newBytes) {
    _totalBytes = newBytes; 
  }

  void setReturned(bool newReturn) {
    _returned = newReturn;
  }

  bool returned() const {
    return _returned;
  }
  

public:
  // do not edit these lines
#define __IN_VISITOR_HEADER__
#define __PURE_VIRTUAL_DECLARATIONS_ONLY__
#include "ast/visitor_decls.h"       // automatically generated
#undef __PURE_VIRTUAL_DECLARATIONS_ONLY__
#undef __IN_VISITOR_HEADER__
  // do not edit these lines: end

};

#endif
