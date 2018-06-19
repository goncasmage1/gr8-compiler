// $Id: cell_node.h,v 1.5 2018/04/20 08:09:07 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_CELLNODE_H__
#define __GR8_CELLNODE_H__

#include <cdk/ast/lvalue_node.h>
#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing cell nodes.
   */
  class cell_node: public cdk::lvalue_node {
    cdk::expression_node* _value;
    cdk::expression_node* _indexing;

    public:
      inline cell_node(int lineno,  cdk::expression_node* value, 
                                    cdk::expression_node* indexing) :
        cdk::lvalue_node(lineno), _value(value), _indexing(indexing) {
      }

    public:

      inline cdk::expression_node* value() {
        return _value;
      }

      inline cdk::expression_node* indexing() {
        return _indexing;
      }

      void accept(basic_ast_visitor *sp, int level) {
        sp->do_cell_node(this, level);
      }

  };

} // gr8

#endif
