/*******************************************************
 *  ThrowsException implementation
 *******************************************************
 *  Author: Firsov Georgy
 *  Contact: gfirsov007@gmail.com
 *  Date: 27.08.2019
 *******************************************************/

#include <utility>

template
<
    typename Exception, typename Callable, typename... Args
>
auto ThrowsException(Callable func, Args&&... args) noexcept
{
    try {
        func(std::forward<Args>(args)...);
        return false;
    }
    catch (const Exception& error) {
        return true;
    }
    catch(... /* Safity */) {
        return false;
    }
}

template
<
    typename Callable, typename... Args
>
auto ThrowsAnyException(Callable func, Args&&... args) noexcept
{
    try {
        func(std::forward<Args>(args)...);
        return false;
    }
    catch (... /* Anything */) {
        return true;
    }
}