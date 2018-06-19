// $Id: function_call_node.h,v 1.4 2018/04/14 11:02:49 ist426019 Exp $ -*- c++ -*-
#ifndef __GR8_FUNCTION_CALLNODE_H__
#define __GR8_FUNCTION_CALLNODE_H__

#include <cdk/ast/typed_node.h>
#include <vector>

namespace gr8 {

  /**
   * Class for describing function_call nodes.
   */
  class function_call_node: public cdk::expression_node {
    std::string* _functionName;
    cdk::sequence_node* _arguments;

  public:
    inline function_call_node(int lineno, std::string* functionName,
                                          cdk::sequence_node* arguments) :
        cdk::expression_node(lineno),
        _functionName(functionName),
        _arguments(arguments) {
    }

  public:
    inline std::string functionName() {
        return *_functionName;
    }
    inline  cdk::sequence_node* arguments() {
      return _arguments;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_call_node(this, level);
    }

  };

} // gr8

#endif
