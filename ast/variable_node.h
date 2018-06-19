// $Id: variable_node.h,v 1.10 2018/04/14 09:33:33 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_VARIABLENODE_H__
#define __GR8_VARIABLENODE_H__

#include <cdk/ast/identifier_node.h>
#include <cdk/ast/expression_node.h>
#include <cdk/basic_type.h>
#include "access_specifier.h"

namespace gr8 {

  /**
   * Class for describing variable nodes.
   */
  class variable_node: public cdk::basic_node {
    gr8::access_specifier _access;
    std::string* _name;
    basic_type* _type;
    cdk::expression_node* _value;

    public:
      inline variable_node(int lineno,  gr8::access_specifier access,
                                        std::string* s,
                                        basic_type* type,
                                        cdk::expression_node* value) :
        cdk::basic_node(lineno), _access(access), _name(s), _type(type), _value(value) {
      }

    public:
      inline gr8::access_specifier access() {
        return _access;
      }

      inline std::string name() {
        return *_name;
      }

      inline cdk::expression_node* value() {
        return _value;
      }

      inline basic_type* type() {
        return _type;
      }

      void accept(basic_ast_visitor *sp, int level) {
        sp->do_variable_node(this, level);
      }

  };

} // gr8

#endif
