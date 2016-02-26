/*
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * 
 * Copyright (c) 2016, Lutz, Clemens <lutzcle@cml.li>
 */

#ifndef CLE_KERNEL_HPP
#define CLE_KERNEL_HPP

#include <vector>
#include <string>

#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

namespace cle {

    cl_int show_platforms(std::vector<cl::Platform> const& platforms);
    cl::Program make_program(cl::Context context, std::string file, std::string options, cl_int& error_code);
    void sanitize_make_kernel(cl_int error_code, cl::Context const& context, cl::Program const& program);

}

#endif /* CLE_KERNEL_HPP */
