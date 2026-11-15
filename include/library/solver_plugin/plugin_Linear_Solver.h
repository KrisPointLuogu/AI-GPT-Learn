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
    DETAILS: Dense linear equation solver plugin.
    LICENSE: Apache-2.0
*/

#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../matrix.h"

Matrix *Linear_Solve(Matrix *mat_A, Matrix *mat_B);
Matrix *Linear_Solve_With_Tolerance(Matrix *mat_A, Matrix *mat_B, MATRIX_TYPE tol);
