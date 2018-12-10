#include <tuple>
#include <utility>

namespace my {

template <typename InputIter1, typename OutputIter, typename Function, typename ... InputIters>
OutputIter __transform_impl(InputIter1 first1, InputIter1 last1, OutputIter d_first, Function func, InputIters ... firsts)
{
    while (first1 != last1) {
        *(d_first++) = func(*(first1++), *(firsts++) ... );
    }
    return d_first;
}

template <typename InputIter1, typename ArgsTuple, size_t ... I>
decltype(auto) __transform_helper(InputIter1 first1, InputIter1 last1, ArgsTuple argsTuple, std::index_sequence<I ...>)
{
    constexpr auto argsTupleSize = std::tuple_size<decltype(argsTuple)>::value;
    auto outputIter = std::get<argsTupleSize - 2>(argsTuple);
    auto function   = std::get<argsTupleSize - 1>(argsTuple);
    return __transform_impl(first1, last1, outputIter, function, std::get<I>(argsTuple) ...);
}

template <typename InputIter1, typename ... InputIters_OutputIter_Function>
decltype(auto) transform(InputIter1 first1, InputIter1 last1, InputIters_OutputIter_Function ... inputIters_outputIter_function)
{
    const auto argsTuple = std::make_tuple(inputIters_outputIter_function ...);
    constexpr auto argsTupleSize = std::tuple_size<decltype(argsTuple)>::value;
    return __transform_helper(first1, last1, argsTuple, std::make_index_sequence<argsTupleSize - 2> ());
}

} // namespace my
