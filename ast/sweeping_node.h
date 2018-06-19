// $Id: sweeping_node.h,v 1.6 2018/04/17 22:21:35 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_sweepingNODE_H__
#define __GR8_sweepingNODE_H__

#include <cdk/ast/typed_node.h>
#include "block_node.h"

namespace gr8 {

  /**
   * Class for describing sweeping nodes.
   */
  class sweeping_node: public cdk::basic_node {
    cdk::lvalue_node *_lvalue;
    cdk::expression_node* _from;
    cdk::expression_node* _to;
    cdk::expression_node* _by;
    cdk::basic_node *_block;

  public:
    inline sweeping_node(int lineno,  cdk::lvalue_node *lvalue,
                                      cdk::expression_node* from,
                                      cdk::expression_node* to,
                                      cdk::expression_node* by,
                                      cdk::basic_node *block) :
        basic_node(lineno),
        _lvalue(lvalue),
        _from(from),
        _to(to),
        _by(by),
        _block(block) {
    }

  public:
    inline cdk::lvalue_node *lvalue() {
      return _lvalue;
    }
    inline cdk::expression_node *from() {
      return _from;
    }
    inline cdk::expression_node *to() {
      return _to;
    }
    inline cdk::expression_node *by() {
      return _by;
    }
    inline cdk::basic_node *block() {
      return _block;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_sweeping_node(this, level);
    }

  };

} // gr8

#endif
