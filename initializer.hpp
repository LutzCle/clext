/*
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * 
 * Copyright (c) 2016, Lutz, Clemens <lutzcle@cml.li>
 */

#ifndef CLE_INITIALIZER_HPP
#define CLE_INITIALIZER_HPP

#include <cstdint>

#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

namespace cle {
    class CLInitializer {
    public:
        int choose_platform_interactive();
        int choose_device_interactive();

        int init(uint32_t platform, uint32_t device);

        int print_device_info();
        cl::Platform get_platform();
        cl::Context get_context();
        cl::Device get_device();
        cl::CommandQueue get_commandqueue();

    private:
        cl::Platform platform_;
        cl::Context context_;
        cl::Device device_;
        cl::CommandQueue queue_;
    };
}

#endif /* CLE_INITIALIZER_HPP */
