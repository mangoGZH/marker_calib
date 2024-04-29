cmake_minimum_required(VERSION 3.19)
project(marker_calib_develop C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(examples)
include_directories(interface)

add_executable(marker_calib_develop
        examples/main.c
        examples/main.h
        compute_fit_error_pso.c
        compute_fit_error_pso.h
        eml_rand_mt19937ar_stateful.c
        eml_rand_mt19937ar_stateful.h
        ixfun.c
        ixfun.h
        minOrMax.c
        minOrMax.h
        PSO_marker_extric_estimate.c
        PSO_marker_extric_estimate.h
        PSO_marker_extric_estimate_data.c
        PSO_marker_extric_estimate_data.h
        PSO_marker_extric_estimate_emxAPI.c
        PSO_marker_extric_estimate_emxAPI.h
        PSO_marker_extric_estimate_emxutil.c
        PSO_marker_extric_estimate_emxutil.h
        PSO_marker_extric_estimate_initialize.c
        PSO_marker_extric_estimate_initialize.h
        PSO_marker_extric_estimate_terminate.c
        PSO_marker_extric_estimate_terminate.h
        PSO_marker_extric_estimate_types.h
        rand.c
        rand.h
        rt_nonfinite.c
        rt_nonfinite.h
        rtGetInf.c
        rtGetInf.h
        rtGetNaN.c
        rtGetNaN.h
        rtwtypes.h)
target_link_libraries(marker_calib_develop m)