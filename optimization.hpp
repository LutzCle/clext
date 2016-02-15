/*
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * 
 * Copyright (c) 2016, Lutz, Clemens <lutzcle@cml.li>
 */

#ifndef OPTIMIZATION_HPP
#define OPTIMIZATION_HPP

#include <cstdint>

#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

namespace cle {

    enum Vendor : cl_uint {
        AMD = 0x1002,
        INTEL = 0x8086,
        NVIDIA = 0x10de
    };

    int device_warp_size(cl::Device device, cl_uint& warp_size);
    uint64_t optimize_global_size(uint64_t work_items, uint64_t local_size);
}

#endif /* OPTIMIZATION_HPP */
