#include <iostream>
#include <functional>

std::string oak(int f, double g, bool h) {
  std::cout << f << ' ' << g << ' ' << h << '\n';
  return "oi";
}

int bamboo(float f, short s) {
  std::cout << f << ' ' << s << '\n';
  return 99;
}

void no_op() {
  std::cout << "no-op" << std::endl;
}

namespace detail {

//recursion
template <std::size_t Index, std::size_t Size>
struct call_with_tuple_impl {
  typedef call_with_tuple_impl<Index + 1, Size> tail;

  template <typename TCallable, typename TTuple, typename... TArgs>
  static auto call(TCallable &&callable, TTuple &&tuple, TArgs &&...args)
    -> decltype(
    tail::call(
      std::forward<TCallable>(callable),
      std::forward<TTuple>(tuple),
      std::forward<TArgs>(args)...,
      std::get<Index>(std::forward<TTuple>(tuple))
    )
  )
  {
  	static_assert(
      Index == sizeof...(args),
      "we expect Index arguments to have been extracted so far"
    );

    return tail::call(
      std::forward<TCallable>(callable),
      std::forward<TTuple>(tuple),
      // we already extracted the initial args so far so just forward them
      std::forward<TArgs>(args)...,
      // and append the Index-th argument that we're extracting
      std::get<Index>(
      	std::forward<TTuple>(tuple)
      )
    );
  }
};

// base case - when Index == Size, we're done
template <std::size_t Size>
struct call_with_tuple_impl<Size, Size> {
  template <typename TCallable, typename TTuple, typename... TArgs>
  static auto call(TCallable &&callable, TTuple &&tuple, TArgs &&...args)
    -> decltype(callable(std::forward<TArgs>(args)...))
  {
  	static_assert(
  	  std::tuple_size<
  	    typename std::decay<TTuple>::type
  	  >::value == sizeof...(TArgs),
  	  "we expect to have already extracted all arguments"
  	);

  	// let's make the call since we're done extracting args
  	return callable(
  	  std::forward<TArgs>(args)...
  	);
  }
};

} // namespace detail {

template <typename TCallable, typename TTuple>
auto call_with_tuple(TCallable &&callable, TTuple &&tuple)
  -> decltype(
  	detail::call_with_tuple_impl<
  	  0, std::tuple_size<typename std::decay<TTuple>::type>::value
  	>::call(
      std::forward<TCallable>(callable),
      std::forward<TTuple>(tuple)
    )
  )
{
  // we want to recurse starting from index zero
  return detail::call_with_tuple_impl<
    0, std::tuple_size<typename std::decay<TTuple>::type>::value
  >::call(
  	std::forward<TCallable>(callable),
  	std::forward<TTuple>(tuple)
  );
}

int main() {
  std::cout << call_with_tuple(
    oak,
    std::make_tuple(10, 9.2, true)
  ) << '\n';

  std::cout << call_with_tuple(
    bamboo,
    std::make_tuple(5.6, 12)
  ) << '\n';
  
  call_with_tuple(no_op, std::make_tuple());

  return 0;
}