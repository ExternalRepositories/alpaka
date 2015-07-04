/**
* \file
* Copyright 2014-2015 Benjamin Worpitz
*
* This file is part of alpaka.
*
* alpaka is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* alpaka is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with alpaka.
* If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <alpaka/core/Common.hpp>   // ALPAKA_FN_HOST_ACC

#include <type_traits>              // std::enable_if, std::is_base_of, std::is_same, std::decay

namespace alpaka
{
    namespace math
    {
        namespace traits
        {
            //#############################################################################
            //! The cbrt trait.
            //#############################################################################
            template<
                typename T,
                typename TArg,
                typename TSfinae = void>
            struct Cbrt;
        }

        //-----------------------------------------------------------------------------
        //! Computes the cbrt.
        //!
        //! \tparam T The type of the object specializing Cbrt.
        //! \tparam TArg The arg type.
        //! \param cbrt The object specializing Cbrt.
        //! \param arg The arg.
        //-----------------------------------------------------------------------------
        template<
            typename T,
            typename TArg>
        ALPAKA_FN_HOST_ACC auto cbrt(
            T const & cbrt,
            TArg const & arg)
        -> decltype(
            traits::Cbrt<
                T,
                TArg>
            ::cbrt(
                cbrt,
                arg))
        {
            return traits::Cbrt<
                T,
                TArg>
            ::cbrt(
                cbrt,
                arg);
        }

        namespace traits
        {
            //#############################################################################
            //! The Cbrt specialization for classes with CbrtBase member type.
            //#############################################################################
            template<
                typename T,
                typename TArg>
            struct Cbrt<
                T,
                TArg,
                typename std::enable_if<
                    std::is_base_of<typename T::CbrtBase, typename std::decay<T>::type>::value
                    && (!std::is_same<typename T::CbrtBase, typename std::decay<T>::type>::value)>::type>
            {
                //-----------------------------------------------------------------------------
                //
                //-----------------------------------------------------------------------------
                ALPAKA_FN_HOST_ACC static auto cbrt(
                    T const & cbrt,
                    TArg const & arg)
                -> decltype(
                    math::cbrt(
                        static_cast<typename T::CbrtBase const &>(cbrt),
                        arg))
                {
                    // Delegate the call to the base class.
                    return
                        math::cbrt(
                            static_cast<typename T::CbrtBase const &>(cbrt),
                            arg);
                }
            };
        }
    }
}
