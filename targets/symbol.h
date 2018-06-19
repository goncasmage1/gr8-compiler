#ifndef __GR8_SEMANTICS_SYMBOL_H__
#define __GR8_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>
#include "../access_specifier.h"

namespace gr8 {

  class symbol {
    basic_type *_type;
    std::string _name;
    bool _function;
    gr8::access_specifier _access;
    int _numParams;
    std::vector<basic_type> _params;

    public:
      symbol(basic_type *type, const std::string &name, bool function, gr8::access_specifier access,
              int numParams, std::vector<basic_type> params) :
                      _type(type),
                      _name(name),
                      _function(function),
                      _access(access),
                      _numParams(numParams),
                      _params(params) {
      }

      virtual ~symbol() {
        delete _type;
      }

      basic_type *type() const {
        return _type;
      }
      const std::string &name() const {
        return _name;
      }
      bool function() {
        return _function;
      }
      gr8::access_specifier access() {
        return _access;
      }
      int numParams() {
        return _numParams;
      }
      std::vector<basic_type> params() {
        return _params;
      }
    };

} // gr8

#endif
