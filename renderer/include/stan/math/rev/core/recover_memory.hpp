#ifndef STAN_MATH_REV_CORE_RECOVER_MEMORY_HPP
#define STAN_MATH_REV_CORE_RECOVER_MEMORY_HPP

#include <stan/math/rev/core/vari.hpp>
#include <stan/math/rev/core/chainablestack.hpp>
#include <stan/math/rev/core/empty_nested.hpp>
#include <stdexcept>

namespace stan {
  namespace math {

    /**
     * Recover memory used for all variables for reuse.
     *
     * @throw std::logic_error if <code>empty_nested()</code> returns
     * <code>false</code>
     */
    static inline void recover_memory() {
      if (!empty_nested())
        throw std::logic_error("empty_nested() must be true"
                               " before calling recover_memory()");
      mitsuba::StanStack::getInstance()->var_stack_.clear();
      mitsuba::StanStack::getInstance()->var_nochain_stack_.clear();
      for (size_t i = 0; i < mitsuba::StanStack::getInstance()->var_alloc_stack_.size(); ++i) {
        delete mitsuba::StanStack::getInstance()->var_alloc_stack_[i];
      }
      mitsuba::StanStack::getInstance()->var_alloc_stack_.clear();
      mitsuba::StanStack::getInstance()->memalloc_.recover_all();
    }

  }
}
#endif
