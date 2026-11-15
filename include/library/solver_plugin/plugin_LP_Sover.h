/*
\ \     __  ___     __      _       __ __     __
 \ \   /  |/  /__ _/ /_____(_)_ __ / // /_ __/ /
 / /  / /|_/ / _ `/ __/ __/ /\ \ // _  / // / _ \
/ /  /_/  /_/\_,_/\__/_/ /_//_\_\/_//_/\_,_/_.__/
* [INFORMATION]
    MATRIX_HUB
    AUTHOR: Xiping.Yu
    E-MAIL:Amoiensis@outlook.com
    GITHUB: https://github.com/Amoiensis/Matrix_hub
    DATE: 2020.02.12-2026.08.14
    VERSION: 2.0.0
    CASE: Matrix Operation (C)
    DETAILS: The plugin-code-file for Matrix_Hub, LP-Solver (Linear Programing).
    LICENSE: Apache-2.0
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#if !defined(_WIN32)
#include <sys/time.h>
#endif
#include "../matrix.h"
#include "./plugin_Linear_Solver.h"

// _SILENT_MODE_ == True(1) -> solver keep silence.
#define _SILENT_MODE_ 1

#define _INTEGER_GAP_ _MATRIX_ABS_EPS_
#define _ZERRO_GAP_ _MATRIX_ABS_EPS_

#define LP_STATUS_OPTIMAL 0
#define LP_STATUS_UNBOUNDED 1
#define LP_STATUS_INFEASIBLE 2
#define LP_STATUS_ITER_LIMIT 3
#define LP_STATUS_INPUT_ERROR 4
#define LP_STATUS_TIME_LIMIT 5
#define LP_STATUS_GAP_LIMIT 6

#define LP_METHOD_REVISED_SIMPLEX 1
#define LP_METHOD_INTERIOR_POINT 2

#define LP_DEGENERATE_PIVOT_LIMIT 20

typedef struct _matrix_LP_result_struct {
    /* Store simplex solver result.
     * 保存单纯形求解结果。返回结构拥有这些矩阵的释放责任。 */
    Matrix *_matrix_A;
    Matrix *_matrix_b;
    Matrix *_matrix_c;
    Matrix *_matrix_base;
    Matrix *_matrix_delta;
    int OPT_STATUS;
    MATRIX_TYPE values_opt;
    int iter_num;
} M_LP_struct;

typedef struct _lp_options_struct {
    /* Runtime controls shared by the standalone LP solvers.
     * Nonpositive limits mean "no explicit limit". */
    int method;
    int progress_interval;
    MATRIX_TYPE time_limit_seconds;
    MATRIX_TYPE gap_limit;
} LP_Options;

LP_Options LP_Default_Options(void);
M_LP_struct * LP_Solver(Matrix* mat_A,Matrix* mat_B,Matrix* mat_C, int LP_method);
M_LP_struct * LP_Solver_With_Progress(Matrix* mat_A,Matrix* mat_B,Matrix* mat_C,
                                      int LP_method, int progress_interval);
M_LP_struct * LP_Solver_With_Options(Matrix* mat_A,Matrix* mat_B,Matrix* mat_C,
                                     const LP_Options *options);
M_LP_struct * LP_simplex_method(Matrix* mat_A,Matrix* mat_B,Matrix* mat_C);
M_LP_struct * LP_simplex_method_with_progress(Matrix* mat_A,Matrix* mat_B,
                                              Matrix* mat_C, int progress_interval);
M_LP_struct * LP_simplex_method_with_options(Matrix* mat_A,Matrix* mat_B,
                                             Matrix* mat_C,
                                             const LP_Options *options,
                                             double start_seconds);
M_LP_struct * LP_interior_point_method(Matrix* mat_A,Matrix* mat_B,Matrix* mat_C);
M_LP_struct * LP_interior_point_method_with_progress(Matrix* mat_A,Matrix* mat_B,
                                                     Matrix* mat_C, int progress_interval);
M_LP_struct * LP_interior_point_method_with_options(Matrix* mat_A,Matrix* mat_B,
                                                    Matrix* mat_C,
                                                    const LP_Options *options,
                                                    double start_seconds);

int LP_free(M_LP_struct* _LP_);
int f_position_list_max(MATRIX_TYPE* list, int len);
int f_position_list_min(MATRIX_TYPE* list, int len);
