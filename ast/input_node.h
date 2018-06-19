// $Id: input_node.h,v 1.3 2018/04/11 20:14:12 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_INPUTNODE_H__
#define __GR8_INPUTNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing input nodes.
   */
  class input_node: public cdk::expression_node {

  public:
    inline input_node(int lineno) :
        cdk::expression_node(lineno) {
    }

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_input_node(this, level);
    }

  };

} // gr8

#endif
