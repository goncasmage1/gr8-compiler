// $Id: address_node.h,v 1.4 2018/03/23 16:12:11 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_ADDRESSNODE_H__
#define __GR8_ADDRESSNODE_H__

#include <cdk/ast/lvalue_node.h>
#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing address nodes.
   */
  class address_node: public cdk::expression_node {
    cdk::lvalue_node* _variable;

    public:
      inline address_node(int lineno,  cdk::lvalue_node* variable) :
        cdk::expression_node(lineno), _variable(variable) {
      }

    public:
      inline cdk::lvalue_node* variable() {
        return _variable;
      }

      void accept(basic_ast_visitor *sp, int level) {
        sp->do_address_node(this, level);
      }

  };

} // gr8

#endif
