// $Id: type_checker.h,v 1.10 2018/05/14 13:28:11 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_SEMANTICS_TYPE_CHECKER_H__
#define __GR8_SEMANTICS_TYPE_CHECKER_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/ast/basic_node.h>
#include "targets/symbol.h"
#include "targets/basic_ast_visitor.h"

namespace gr8 {

  class type_checker: public basic_ast_visitor {
    cdk::symbol_table<gr8::symbol> &_symtab;

    basic_ast_visitor *_parent;

  public:
    type_checker(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<gr8::symbol> &symtab, basic_ast_visitor *parent) :
        basic_ast_visitor(compiler), _symtab(symtab), _parent(parent) {
    }

  public:
    ~type_checker() {
      os().flush();
    }
    
  protected:
    void processUnaryExpression_I_D(cdk::unary_expression_node * const node, int lvl);
    void processUnaryExpression_I(cdk::unary_expression_node * const node, int lvl);
    void processUnaryExpression_L(cdk::unary_expression_node * const node, int lvl);
    void processBinaryExpression_I_D_P(cdk::binary_expression_node * const node, bool forceInt, int lvl);
    void processBinaryExpression_I_D(cdk::binary_expression_node * const node, bool forceInt, int lvl);
    void processBinaryExpression_I(cdk::binary_expression_node * const node, int lvl);
    bool verifyIfRead(basic_type* left, basic_type* right);
    template<typename T>
    void process_literal(cdk::literal_node<T> * const node, int lvl) {
    }

  public:
  // do not edit these lines
#define __IN_VISITOR_HEADER__
#include "ast/visitor_decls.h"       // automatically generated
#undef __IN_VISITOR_HEADER__
  // do not edit these lines: end

  };

} // gr8

//---------------------------------------------------------------------------
//     HELPER MACRO FOR TYPE CHECKING
//---------------------------------------------------------------------------

#define CHECK_TYPES(compiler, symtab, node) { \
  try { \
    gr8::type_checker checker(compiler, symtab, this); \
    (node)->accept(&checker, 0); \
  } \
  catch (const std::string &problem) { \
    std::cerr << (node)->lineno() << ": " << problem << std::endl; \
    return; \
  } \
}

#define ASSERT_SAFE_EXPRESSIONS CHECK_TYPES(_compiler, _symtab, node)

#endif
