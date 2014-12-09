/**
* Copyright 2014 Benjamin Worpitz
*
* This file is part of alpaka.
*
* alpaka is free software: you can redistribute it and/or modify
* it under the terms of either the GNU General Public License or
* the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* alpaka is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License and the GNU Lesser General Public License
* for more details.
*
* You should have received a copy of the GNU General Public License
* and the GNU Lesser General Public License along with alpaka.
* If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <alpaka/fibers/Common.hpp>

#include <alpaka/core/Common.hpp>   // ALPAKA_FCT_HOST_ACC

namespace alpaka
{
    namespace fibers
    {
        namespace detail
        {
            //#############################################################################
            //! A barrier.
            // NOTE: We do not use the boost::fibers::barrier because it does not support simple resetting.
            //#############################################################################
            class FiberBarrier
            {
            public:
                //-----------------------------------------------------------------------------
                //! Constructor.
                //-----------------------------------------------------------------------------
                ALPAKA_FCT_HOST explicit FiberBarrier(std::size_t uiNumFibersToWaitFor = 0) :
                    m_uiNumFibersToWaitFor{uiNumFibersToWaitFor}
                {}
                //-----------------------------------------------------------------------------
                //! Deleted copy-constructor.
                //-----------------------------------------------------------------------------
                ALPAKA_FCT_HOST FiberBarrier(FiberBarrier const &) = delete;
                //-----------------------------------------------------------------------------
                //! Move-constructor.
                //-----------------------------------------------------------------------------
                ALPAKA_FCT_HOST FiberBarrier(FiberBarrier &&) = default;
                //-----------------------------------------------------------------------------
                //! Copy-assignment.
                //-----------------------------------------------------------------------------
                ALPAKA_FCT_HOST FiberBarrier & operator=(FiberBarrier const &) = delete;
                //-----------------------------------------------------------------------------
                //! Destructor.
                //-----------------------------------------------------------------------------
                ALPAKA_FCT_HOST ~FiberBarrier() noexcept = default;

                //-----------------------------------------------------------------------------
                //! Waits for all the other fibers to reach the barrier.
                //-----------------------------------------------------------------------------
                ALPAKA_FCT_HOST void wait()
                {
                    boost::unique_lock<boost::fibers::mutex> lock(m_mtxBarrier);
                    if(--m_uiNumFibersToWaitFor == 0)
                    {
                        m_cvAllFibersReachedBarrier.notify_all();
                    }
                    else
                    {
                        m_cvAllFibersReachedBarrier.wait(lock, [this] { return m_uiNumFibersToWaitFor == 0; });
                    }
                }

                //-----------------------------------------------------------------------------
                //! \return The number of fibers to wait for.
                //! NOTE: The value almost always is invalid the time you get it.
                //-----------------------------------------------------------------------------
                ALPAKA_FCT_HOST std::size_t getNumFibersToWaitFor() const
                {
                    return m_uiNumFibersToWaitFor;
                }

                //-----------------------------------------------------------------------------
                //! Resets the number of fibers to wait for to the given number.
                //-----------------------------------------------------------------------------
                ALPAKA_FCT_HOST void reset(std::size_t uiNumFibersToWaitFor)
                {
                    //boost::unique_lock<boost::fibers::mutex> lock(m_mtxBarrier);
                    m_uiNumFibersToWaitFor = uiNumFibersToWaitFor;
                }

            private:
                boost::fibers::mutex m_mtxBarrier;
                boost::fibers::condition_variable m_cvAllFibersReachedBarrier;
                std::size_t m_uiNumFibersToWaitFor;
            };
        }
    }
}
