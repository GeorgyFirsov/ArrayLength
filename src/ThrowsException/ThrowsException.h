/*******************************************************
 *  ThrowsException is a function, that checks
 *  passed as first parameter callable if it throws
 *  an exception passed as a template argument.
 *
 *  ThrowsAnyException is a function, that checks
 *  passed as first parameter callable it it throws
 *  any exception.
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