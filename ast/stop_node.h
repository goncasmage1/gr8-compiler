// $Id: stop_node.h,v 1.4 2018/04/13 19:01:07 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_STOPNODE_H__
#define __GR8_STOPNODE_H__

#include <cdk/ast/basic_node.h>

namespace gr8 {

  /**
   * Class for describing stop nodes.
   */
  class stop_node: public cdk::basic_node {
    int _number;

  public:
    inline stop_node(int lineno, int number) :
        cdk::basic_node(lineno), _number(number){
    }

  public:

    inline int number() {
      return _number;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_stop_node(this, level);
    }

  };

} // gr8

#endif
