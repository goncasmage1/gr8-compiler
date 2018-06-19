// $Id: objects_node.h,v 1.7 2018/04/19 17:22:05 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_OBJECTSNODE_H__
#define __GR8_OBJECTSNODE_H__

#include <cdk/ast/integer_node.h>

namespace gr8 {

  /**
   * Class for describing objects nodes.
   */
  class objects_node: public cdk::unary_expression_node {

    public:
      inline objects_node(int lineno, cdk::expression_node* number) :
        cdk::unary_expression_node(lineno, number) {
      }

    public:

      void accept(basic_ast_visitor *sp, int level) {
        sp->do_objects_node(this, level);
      }

  };

} // gr8

#endif
