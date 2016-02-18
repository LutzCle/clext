/*
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * 
 * Copyright (c) 2016, Lutz, Clemens <lutzcle@cml.li>
 */

#ifndef CLE_STRING_HPP
#define CLE_STRING_HPP

#include <string>
#include <type_traits>

#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

namespace cle {

    std::string opencl_device_string(cl_device_type device_type);
    std::string opencl_error_string(cl_int error_code);

    class OpenCLType {
    public:
        template <typename T>
        static char const* to_str() {

            if (std::is_same<cl_uint, T>::value) {
                return "uint";
            }
            else if (std::is_same<cl_ulong, T>::value) {
                return "ulong";
            }
            else if (std::is_same<cl_float, T>::value) {
                return "float";
            }
            else if (std::is_same<cl_double, T>::value) {
                return "double";
            }
            else {
                return "unknown type";
            }

        }
    };

}

#endif /* CLE_STRING_HPP */
