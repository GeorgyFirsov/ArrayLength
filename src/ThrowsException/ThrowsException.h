/*******************************************************
 *  ThrowsException is a function, that checks
 *  passed as first parameter callable if it throws
 *  an exception passed as a template argument.
 *
 *  ThrowsAnyException is a function, that checks
 *  passed as first parameter callable it it throws
 *  any exception.
 *
 *  Prameters:
 *      - func - callable (function, functor, etc.) to test
 *      - args - variadic number of arguments to pass to func
 *      - Exception (template parameter) - expected exception type
 *        (assumed any if none provided)
 *
 *  Return value:
 *      - true if func throws an expected exception
 *      - false otherwise
 *******************************************************
 *  Author: Firsov Georgy
 *  Contact: gfirsov007@gmail.com
 *  Date: 27.08.2019
 *******************************************************/
#pragma once

template
<
    typename Exception, typename Callable, typename... Args
>
auto ThrowsException(Callable func, Args&&... args) noexcept;

template
<
    typename Callable, typename... Args
>
auto ThrowsAnyException(Callable func, Args&&... args) noexcept;