/*
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * 
 * Copyright (c) 2016, Lutz, Clemens <lutzcle@cml.li>
 */

#include "initializer.hpp"

#include "sanitize.hpp"
#include "kernel.hpp"
#include "string.hpp"
#include "optimization.hpp"

#include <iostream>
#include <string>

#ifdef MAC
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif


int cle::CLInitializer::choose_platform_interactive() {
    cl_int err;
    unsigned int choice;

    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    if (platforms.size() == 0) {
        std::cerr << "Error: no platforms found" << std::endl;
        return -1;
    }

    // Display platform list
    err = show_platforms(platforms);
    if (err != CL_SUCCESS) {
        return -1;
    }

    // Ask user for selection
    std::cout << "Enter platform number: " << std::flush;
    std::cin >> choice;
    std::cout << std::endl;
    this->platform_ = cl::Platform(platforms[choice]);

    // Create context
    cl_context_properties cps[3] = {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)(platforms[choice])(), 0
    };

    cle_sanitize_ref_return(
            this->context_ = cl::Context(
                CL_DEVICE_TYPE_ALL,
                cps,
                NULL,
                NULL,
                &err
                ), err);

    return 1;
}

int cle::CLInitializer::choose_device_interactive() {
    cl_int err;
    cl_uint num_devices;
    std::vector<cl::Device> devices;

    cle_sanitize_val_return(
            this->context_.getInfo(
                CL_CONTEXT_NUM_DEVICES,
                &num_devices
                ));

    devices.resize(num_devices);

    cle_sanitize_val_return(
            this->context_.getInfo(
                CL_CONTEXT_DEVICES,
                &devices
                ));

    // TODO: show devices, choose device
    this->device_ = cl::Device(devices[0]);

    // Create command queue for device
    cle_sanitize_ref_return(
            this->queue_ = cl::CommandQueue(
                this->context_,
                this->device_,
                CL_QUEUE_PROFILING_ENABLE,
                &err
                ), err);

    return 1;
}

int cle::CLInitializer::init(uint32_t const platform, uint32_t const device) {
    cl_int err;
    cl_uint num_devices;
    std::vector<cl::Device> devices;
    std::vector<cl::Platform> platforms;

    cl::Platform::get(&platforms);
    if (platforms.size() == 0) {
        std::cerr << "Error: no platforms found" << std::endl;
        return -1;
    }

    platform_ = cl::Platform(platforms[platform]);

    // Create context
    cl_context_properties cps[3] = {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)(platforms[platform])(), 0
    };

    cle_sanitize_ref_return(
            context_ = cl::Context(
                CL_DEVICE_TYPE_ALL,
                cps,
                NULL,
                NULL,
                &err
                ), err);

    cle_sanitize_val_return(
            context_.getInfo(
                CL_CONTEXT_NUM_DEVICES,
                &num_devices
                ));

    devices.resize(num_devices);

    cle_sanitize_val_return(
            context_.getInfo(
                CL_CONTEXT_DEVICES,
                &devices
                ));

    device_ = cl::Device(devices[device]);

    // Create command queue for device
    cle_sanitize_ref_return(
            queue_ = cl::CommandQueue(
                context_,
                device_,
                CL_QUEUE_PROFILING_ENABLE,
                &err
                ), err);

    return 1;
}

int cle::CLInitializer::print_device_info() {
    std::string buffer;
    cl_ulong size;
    cl_uint int_size;
    size_t size_size;

    cle_sanitize_val_return(
            device_.getInfo(CL_DEVICE_VENDOR, &buffer));
    std::cout << "Vendor: " << buffer << std::endl;

    cle_sanitize_val_return(
            device_.getInfo(CL_DEVICE_NAME, &buffer));
    std::cout << "Device: " << buffer << std::endl;

    cle_sanitize_val_return(
            device_.getInfo(CL_DEVICE_PROFILE, &buffer));
    std::cout << "OpenCL Profile: " << buffer << std::endl;

    cle_sanitize_val_return(
            device_.getInfo(CL_DEVICE_LOCAL_MEM_SIZE, &size));
    std::cout << "Local memsize (KiB) " << size / 1024 << std::endl;

    cle_sanitize_val_return(
            device_.getInfo(CL_DEVICE_GLOBAL_MEM_SIZE, &size));
    std::cout << "Global memsize (MiB) " << size / 1024 / 1024 << std::endl;

    cle_sanitize_done_return(
            cle::device_warp_size(device_, int_size));
    std::cout << "Warp size: " << int_size << std::endl;

    cle_sanitize_val_return(
            device_.getInfo(CL_DEVICE_PROFILING_TIMER_RESOLUTION, &size_size));
    std::cout << "Timer resolution: " << size_size << std::endl;

    return CL_SUCCESS;
}

cl::Platform cle::CLInitializer::get_platform() {
    return this->platform_;
}

cl::Context cle::CLInitializer::get_context() {
    return this->context_;
}

cl::Device cle::CLInitializer::get_device() {
    return this->device_;
}

cl::CommandQueue cle::CLInitializer::get_commandqueue() {
    return this->queue_;
}
