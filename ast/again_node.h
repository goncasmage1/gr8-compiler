// $Id: again_node.h,v 1.4 2018/04/13 19:01:07 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_AGAINNODE_H__
#define __GR8_AGAINNODE_H__

#include <cdk/ast/basic_node.h>

namespace gr8 {

  /**
   * Class for describing again nodes.
   */
  class again_node: public cdk::basic_node {
    int _number;

  public:
    inline again_node(int lineno, int number) :
        cdk::basic_node(lineno), _number(number) {
    }

  public:

    inline int number() {
      return _number;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_again_node(this, level);
    }

  };

} // gr8

#endif
