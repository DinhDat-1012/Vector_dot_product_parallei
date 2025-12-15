//
// Created by dinhd on 12/15/2025.
//

#ifndef OPENMP_PRJ_VECTOR_DOT_PAR_H
#define OPENMP_PRJ_VECTOR_DOT_PAR_H


#include <vector>


void vector_dot_par(int num_of_threads, const std::vector<double>& v1, const std::vector<double>& v2, double& time_taken);



#endif //OPENMP_PRJ_VECTOR_DOT_PAR_H