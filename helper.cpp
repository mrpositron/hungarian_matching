#include <iostream>
#include "helper.h"

using namespace std;

void print_matrix(vector <vector <float> > &mat, int N, int M)
{
    /*
    Prints the matrix.
    Arguments:
        mat: the matrix to print
        N: the number of rows
        M: the number of columns
    */
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}
void subtract_min_row_elem_from_each_row(vector <vector <float> > &mat, int N, int M)
{
    /*
    Subtracts the minimum element of each row from each element of the row.
    Arguments:
        mat: the matrix to subtract from
        N: the number of rows
        M: the number of columns
    */
    for(int i = 0; i < N; i++){
        float min = mat[i][0];
        for(int j = 1; j < M; j++){
            if(mat[i][j] < min){
                min = mat[i][j];
            }
        }
        for(int j = 0; j < M; j++){
            mat[i][j] -= min;
        }
    }
}
void subtract_min_col_elem_from_each_col(vector <vector <float> > &mat, int N, int M)
{
    /* 
    Subtracts the minimum element of each column from each element of the column.
    Arguments:
        mat: the matrix to subtract from
        N: the number of rows
        M: the number of columns
    */
    for(int j = 0; j < M; j++){
        float min = mat[0][j];
        for(int i = 1; i < N; i++){
            if(mat[i][j] < min){
                min = mat[i][j];
            }
        }
        for(int i = 0; i < N; i++){
            mat[i][j] -= min;
        }
    }
}

void set_elem_to_one_if_elem_is_zero_else_one(vector <vector <float> > &mat, vector <vector <int> > &zero_mat, int N, int M)
{
    /*
    Sets the element to 1 if it is zero, else sets it to 0.
    Arguments:
        mat: the matrix
        zero_mat: the matrix to set the elements to 1 or 0
        N: the number of rows
        M: the number of columns
    */
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(mat[i][j] == 0){
                zero_mat[i][j] = 1;
            } else {
                zero_mat[i][j] = 0;
            }
        }
    }
}

void find_row_with_fewest_ones(vector <vector <int> > &zero_mat, vector <vector <int> > &marked_zero, int N, int M){
    vector<int> min_row{100000, -1};

    for (int i = 0; i < N; i++){
        int count = 0;
        for (int j = 0; j < M; j++){
            if (zero_mat[i][j] == 1){
                count++;
            }
        }
        if (count > 0 && min_row[0] > count){
            min_row[0] = count;
            min_row[1] = i;
        }
    }
    
    int zero_index = 0;
    for (int j = 0; j < M; j++){
        if (zero_mat[min_row[1]][j] == 1){
            zero_index = j;
            break;
        }
    }
    vector<int> temp;
    temp.push_back(min_row[1]);
    temp.push_back(zero_index);

    marked_zero.push_back(temp);
    // set all elements in row to zero at column zero_index
    for (int j = 0; j < M; j++){
        zero_mat[min_row[1]][j] = 0;
    }
    // set all elements in column to zero at row min_row[1]
    for (int i = 0; i < N; i++){
        zero_mat[i][zero_index] = 0;
    }

}

bool element_equal_to_one_exist(vector <vector <int> > &zero_mat, int N, int M){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (zero_mat[i][j] == 1){
                return true;
            }
        }
    }
    return false;
}

bool exist(vector<int> temp, int i){
    for (int j = 0; j < temp.size(); j++){
        if (temp[j] == i){
            return true;
        }
    }
    return false;
}

void mark_matrix(vector <vector <float> > &mat, vector <vector <int> > &ans, vector <vector <int> > &marked_zero, int N, int M){

    vector <vector <int> > zero_mat(N, vector<int>(M));
    vector <vector <int> >  zero_mat_copy(N, vector<int>(M));

    set_elem_to_one_if_elem_is_zero_else_one(mat, zero_mat, N, M);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            zero_mat_copy[i][j] = zero_mat[i][j];
        }
    }

    while(element_equal_to_one_exist(zero_mat_copy, N, M)){
        find_row_with_fewest_ones(zero_mat_copy, marked_zero, N, M);
    }

    vector<int> marked_zero_row;
    for(int i = 0; i < marked_zero.size(); i++){
        vector<int> temp = marked_zero[i];
        marked_zero_row.push_back(temp[0]);
    }

    vector<int> non_marked_row;
    for (int i = 0; i < N; i++){
        if (!exist(marked_zero_row, i)){
            non_marked_row.push_back(i);
        }
    }

    vector<int> marked_cols;
    bool check = true;
    while (check){
        check = false;
        for (int i = 0; i < non_marked_row.size(); i++){
            vector<int> row_array = zero_mat[non_marked_row[i]];

            for (int j = 0; j < row_array.size(); j++){
                if (row_array[j] == 1 && !exist(marked_cols, j)){
                    marked_cols.push_back(j);
                    check = true;
                }
            }
        }

        for (int i = 0; i < marked_zero.size(); i++){
            vector<int> temp = marked_zero[i];
            int row_num = temp[0];
            int col_num = temp[1];

            if ( !exist(non_marked_row, row_num) && exist(marked_cols, col_num)){
                non_marked_row.push_back(row_num);
                check = true;
            }
        }

    }

    vector<int> marked_rows;
    for (int i = 0; i < N; i++){
        if (!exist(non_marked_row, i)){
            marked_rows.push_back(i);
        }
    }
    ans.push_back(marked_rows);
    ans.push_back(marked_cols);
}

void adjust_matrix(vector <vector <float> > &mat, vector<int> marked_rows, vector<int> marked_cols, int N, int M){
    vector<float> non_zero_element;

    for (int row = 0; row < N; row++){
        if (!exist(marked_rows, row)){
            for (int i = 0; i < M; i++) {
                if (!exist(marked_cols, i)){
                    non_zero_element.push_back(mat[row][i]);
                }
            }
        }
    }

    int min_num = 100000;
    for(int i = 0; i < non_zero_element.size(); i++){
        if (min_num > non_zero_element[i]){
            min_num = non_zero_element[i];
        }
    }

    for (int row = 0; row < N; row++){
        if (!exist(marked_rows, row)){
            for (int i = 0; i < M; i++) {
                if (!exist(marked_cols, i)){
                    mat[row][i] = mat[row][i] - min_num;
                }
            }
        }
    }

    for (int row = 0; row < marked_rows.size(); row++){
        for (int col = 0; col < marked_cols.size(); col++){
            mat[marked_rows[row]][marked_cols[col]] += min_num;
        }
    }
}

void hungarian_matching(vector <vector <float> > &mat, vector <vector <int> > &result, int N, int M)
{
    subtract_min_row_elem_from_each_row(mat, N, M);
    subtract_min_col_elem_from_each_col(mat, N, M);

    int zero_count = 0;
    while (zero_count < N){
        vector<vector <int> > marked_zero;
        vector<vector <int> > ans;
        mark_matrix(mat, ans, marked_zero, N, M);
        
        vector<int> marked_rows = ans[0];
        vector<int> marked_cols = ans[1];        

        zero_count = marked_rows.size() + marked_cols.size();
        if (zero_count < N){
            adjust_matrix(mat, marked_rows, marked_cols, N, M);
        }
        result = marked_zero;
    }
    
}

void pad(vector <vector <float> > &mat, vector <vector <float> > &new_mat, int N, int M, int pad_val){
    // copy the matrix mat to new_mat
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            new_mat[i][j] = mat[i][j];
        }
    }
    if (N > M){
        // pad the matrix with zeros
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M - N; j++){
                new_mat[i].push_back(pad_val);
            }
        }

    }
    else if (N < M){
        // pad the matrix with zeros
        for (int i = 0; i < M - N; i++){
            vector<float> temp;
            for (int j = 0; j < M; j++){
                temp.push_back(pad_val);
            }
            new_mat.push_back(temp);
        }
    }
}

int calculate_cost(vector <vector <float> > &mat, vector <vector <int> > &result){
    int cost = 0;
    for (int i = 0; i < result.size(); i++){
        vector<int> temp = result[i];
        int row_num = temp[0];
        int col_num = temp[1];
        cost += mat[row_num][col_num];
    }
    return cost;
}

void copy_matrix(vector <vector <float> > &mat, vector <vector <float> > &new_mat, int N, int M){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            new_mat[i][j] = mat[i][j];
        }
    }
}
int get_max_element(vector <vector <float> > &mat, int N, int M){
    int max_element = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (max_element < mat[i][j]){
                max_element = mat[i][j];
            }
        }
    }
    return max_element;
}

bool cmp(vector<int> a, vector<int> b){
    return a[0] < b[0];
}

int solve(vector <vector <float> > &mat, vector < int > &indexes, int state){
    int N, M;
    N = mat.size();
    M = mat[0].size();
    vector< vector<float> > mat_padded, mat_padded_copy;
    mat_padded.resize(N,vector<float>(M));
    
    pad(mat, mat_padded, N, M, 0);
    
    N = mat_padded.size();
    M = mat_padded[0].size();

    mat_padded_copy.resize(N,vector<float>(M));
    copy_matrix(mat_padded, mat_padded_copy, N, M);
    if (state == 1){
        // get the maximum element from the matrix mat_padded_copy
        int max_val = get_max_element(mat_padded_copy, N, M);

        // subtract matrix mat_padded_copy from the maximum element 
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                mat_padded_copy[i][j] = max_val - mat_padded_copy[i][j];
            }
        }
    }

    
    vector <vector <int> > ans_pos;
    hungarian_matching(mat_padded_copy, ans_pos, N, M);
    int cost = calculate_cost(mat_padded, ans_pos);

    // sort ans_pos by the first element of the vector
    sort(ans_pos.begin(), ans_pos.end(), cmp);

    for (int i = 0; i < ans_pos.size(); i++){
        vector<int> temp = ans_pos[i];
        if (temp[0] >= mat.size() || temp[1] >= mat[0].size()){
            continue;
        }
        indexes.push_back(temp[1]);
    }

    return cost;
}
