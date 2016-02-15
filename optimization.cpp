/*
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * 
 * Copyright (c) 2016, Lutz, Clemens <lutzcle@cml.li>
 */

#include "optimization.hpp"

#include "string.hpp"
#include "sanitize.hpp"

#include <cassert>

cl_int cle::device_warp_size(cl::Device device, cl_uint& warp_size) {

    cl_uint vendor_id = 0;
    warp_size = 0;

    cle_sanitize_val_return(
            device.getInfo(CL_DEVICE_VENDOR_ID, &vendor_id));

    switch (vendor_id) {
        case cle::Vendor::AMD:
#ifdef CL_DEVICE_WAVEFRONT_WIDTH_AMD
            cle_sanitize_val_return(
                    device.getInfo(CL_DEVICE_WAVEFRONT_WIDTH_AMD, &warp_size));
#else
            assert(false /* AMD not available */);
#endif
            break;
        case cle::Vendor::INTEL:
            assert(false /* Intel not available */);
            break;
        case cle::Vendor::NVIDIA:
#ifdef CL_DEVICE_WARP_SIZE_NV
            cle_sanitize_val_return(
                    device.getInfo(CL_DEVICE_WARP_SIZE_NV, &warp_size));
#else
            assert(false /* Nvidia not available */);
#endif
            break;
        default:
            assert(false /* Unknown vendor */);
    }

    return CL_SUCCESS;
}

uint64_t cle::optimize_global_size(uint64_t work_items, uint64_t local_size) {

    bool is_multiple = not (not (work_items % local_size));
    uint64_t work_groups = work_items / local_size + is_multiple;

    return work_groups * local_size;
}

