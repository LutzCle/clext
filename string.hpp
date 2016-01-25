#ifndef CLE_STRING_HPP
#define CLE_STRING_HPP

#include <string>

#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

namespace cle {

    std::string opencl_device_string(cl_device_type device_type);
    std::string opencl_error_string(cl_int error_code);

}

#endif /* CLE_STRING_HPP */
