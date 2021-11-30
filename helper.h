#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <vector>

void print_matrix(std::vector <std::vector <float> > &mat, int N, int M);
void subtract_min_row_elem_from_each_row(std::vector <std::vector <float> > &mat, int N, int M);
void subtract_min_col_elem_from_each_col(std::vector <std::vector <float> > &mat, int N, int M);
void set_elem_to_one_if_elem_is_zero_else_one(std::vector <std::vector <float> > &mat, std::vector <std::vector <int> > &zero_mat, int N, int M);
void find_row_with_fewest_ones(std::vector <std::vector <int> > &zero_mat, std::vector <std::vector <int> > &marked_zero, int N, int M);
bool element_equal_to_one_exist(std::vector <std::vector <int> > &zero_mat, int N, int M);
bool exist(std::vector<int> temp, int i);
void mark_matrix(std::vector <std::vector <float> > &mat, std::vector <std::vector <int> > &ans, std::vector <std::vector <int> > &marked_zero, int N, int M);
void adjust_matrix(std::vector <std::vector <float> > &mat, std::vector<int> marked_rows, std::vector<int> marked_cols, int N, int M);
void hungarian_matching(std::vector <std::vector <float> > &mat, std::vector <std::vector <int> > &result, int N, int M);
void pad(std::vector <std::vector <float> > &mat, std::vector <std::vector <float> > &new_mat, int N, int M, int pad_val);
int calculate_cost(std::vector <std::vector <float> > &mat, std::vector <std::vector <int> > &result);
int solve(std::vector <std::vector <float> > &mat, std::vector <int> &indexes, int state);
int get_max_element(std::vector <std::vector <float> > &mat, int N, int M);
bool cmp(std::vector<int> a, std::vector<int> b);
#endif 