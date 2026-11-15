/*
\ \     __  ___     __      _       __ __     __
 \ \   /  |/  /__ _/ /_____(_)_ __ / // /_ __/ /
 / /  / /|_/ / _ `/ __/ __/ /\ \ // _  / // / _ \
/ /  /_/  /_/\_,_/\__/_/ /_//_\_\/_//_/\_,_/_.__/
* [INFORMATION]
    MATRIX_HUB
    AUTHOR: Xiping.Yu
    GITHUB: https://github.com/Amoiensis/Matrix_hub
    VERSION: 2.0.0
    CASE: Matrix Solver Plugin (C)
    DETAILS: Teaching MIP solver plugin with simple cuts and branch-and-bound.
    LICENSE: Apache-2.0
*/

#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#if !defined(_WIN32)
#include <sys/time.h>
#endif
#include "../matrix.h"
#include "./plugin_LP_Sover.h"

#define MIP_STATUS_OPTIMAL 0
#define MIP_STATUS_INFEASIBLE 1
#define MIP_STATUS_NODE_LIMIT 2
#define MIP_STATUS_UNBOUNDED 3
#define MIP_STATUS_INPUT_ERROR 4
#define MIP_STATUS_TIME_LIMIT 5
#define MIP_STATUS_GAP_LIMIT 6

#define MIP_METHOD_BRANCH_BOUND 1
#define MIP_METHOD_CUT_BRANCH_BOUND 2

#define MIP_BRANCH_FIRST_FRACTIONAL 1
#define MIP_BRANCH_MOST_FRACTIONAL 2

#define MIP_NODE_DEPTH_FIRST 1
#define MIP_NODE_BEST_BOUND 2

#define MIP_BOUND_PARENT 1
#define MIP_BOUND_TIGHT 2

#define MIP_DEFAULT_NODE_LIMIT 1024
#define MIP_DEFAULT_OPEN_NODE_LIMIT 1024
#define MIP_DEFAULT_ROOT_CUT_ROUNDS 1
#define MIP_DEFAULT_HEURISTIC_FREQUENCY 100
#define MIP_MAX_NODES MIP_DEFAULT_NODE_LIMIT
#define MIP_INF 1e100

typedef struct _matrix_MIP_result_struct {
    /* Store MIP solver result.
     * _matrix_x is the best integer solution for the original variables.
     * node_num and cut_num are kept visible for progress reporting and debugging. */
    Matrix *_matrix_x;
    Matrix *_matrix_c;
    Matrix *_matrix_integer;
    int OPT_STATUS;
    MATRIX_TYPE values_opt;
    int node_num;
    int cut_num;
} M_MIP_struct;

typedef struct _mip_node_struct {
    MATRIX_TYPE *lower;
    MATRIX_TYPE *upper;
    Matrix *relax_x;
    MATRIX_TYPE bound;
    int depth;
    int has_relaxation;
} MIP_Node;

typedef struct _mip_options_struct {
    /* Runtime controls for the lightweight MIP solver.
     * Nonpositive limits are disabled; nonpositive tolerances use defaults. */
    int method;
    int node_limit;
    int open_node_limit;
    int progress_interval;
    int root_cut_rounds;
    int heuristic_frequency;
    int repair_limit;
    int branch_rule;
    int node_selection;
    int bound_mode;
    MATRIX_TYPE feasibility_tol;
    MATRIX_TYPE integer_tol;
    MATRIX_TYPE objective_display_sign;
    MATRIX_TYPE time_limit_seconds;
    MATRIX_TYPE gap_limit;
} MIP_Options;

MIP_Options MIP_Default_Options(void);
M_MIP_struct *MIP_Solver(Matrix *mat_A, Matrix *mat_b, Matrix *mat_c,
                         Matrix *integer_mask, int MIP_method);
M_MIP_struct *MIP_Solver_With_Progress(Matrix *mat_A, Matrix *mat_b, Matrix *mat_c,
                                       Matrix *integer_mask, int MIP_method,
                                       int progress_interval);
M_MIP_struct *MIP_Solver_With_Options(Matrix *mat_A, Matrix *mat_b, Matrix *mat_c,
                                      Matrix *integer_mask,
                                      const MIP_Options *options);
int MIP_free(M_MIP_struct *mip);
