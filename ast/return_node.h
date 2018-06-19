// $Id: return_node.h,v 1.4 2018/03/22 14:53:40 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_RETURNNODE_H__
#define __GR8_RETURNNODE_H__

#include <cdk/ast/typed_node.h>
#include <cdk/basic_type.h>

namespace gr8 {

  /**
   * Class for describing return nodes.
   */
  class return_node: public cdk::basic_node {
    cdk::expression_node* _returnValue;

    public:
      inline return_node(int lineno,  cdk::expression_node* returnValue) :
        cdk::basic_node(lineno), _returnValue(returnValue) {
      }

    public:

      inline cdk::expression_node* returnValue() {
          return _returnValue;
      }

      void accept(basic_ast_visitor *sp, int level) {
        sp->do_return_node(this, level);
      }

  };

} // gr8

#endif
