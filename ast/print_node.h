// $Id: print_node.h,v 1.3 2018/04/14 11:02:49 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_PRINTNODE_H__
#define __GR8_PRINTNODE_H__

#include <cdk/ast/typed_node.h>

namespace gr8 {

  /**
   * Class for describing print nodes.
   */
  class print_node: public cdk::basic_node {
    bool _newLine;
    cdk::expression_node *_argument;

  public:
    inline print_node(int lineno, bool newLine, cdk::expression_node *argument) :
        cdk::basic_node(lineno), _newLine(newLine), _argument(argument) {
    }

  public:
    inline bool newLine() {
      return _newLine;
    }
    inline cdk::expression_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_print_node(this, level);
    }

  };

} // gr8

#endif
