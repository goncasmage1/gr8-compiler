// $Id: variable_visitor.h,v 1.2 2018/05/14 13:28:11 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_SEMANTICS_VARIABLE_VISITOR_H__
#define __GR8_SEMANTICS_VARIABLE_VISITOR_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/ast/basic_node.h>
#include "targets/symbol.h"
#include "targets/basic_ast_visitor.h"

namespace gr8 {

  class variable_visitor : public basic_ast_visitor {
    cdk::symbol_table<gr8::symbol>& _symtab;

    basic_ast_visitor *_parent;

    public:
      variable_visitor(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<gr8::symbol> &symtab, basic_ast_visitor *parent) : 
        basic_ast_visitor(compiler),
        _symtab(symtab),
        _parent(parent) { 
      }
    
    public:

      int getTotalBytes() const { return _totalBytes; }

    protected:
      int _totalBytes = 0;

    public:
  // do not edit these lines
#define __IN_VISITOR_HEADER__
#include "ast/visitor_decls.h"       // automatically generated
#undef __IN_VISITOR_HEADER__
  // do not edit these lines: end

  };

}

#define CHECK_VARIABLE_TYPES(compiler, symtab, node) { \
  try { \
    gr8::variable_visitor variables(compiler, symtab, this); \
    (node)->accept(&variables, 0); \
  } \
  catch (const std::string &problem) { \
    std::cerr << (node)->lineno() << ": " << problem << std::endl; \
    return; \
  } \
}

#define VISIT_VARIABLES CHECK_VARIABLE_TYPES(_compiler, _symtab, node)

#endif