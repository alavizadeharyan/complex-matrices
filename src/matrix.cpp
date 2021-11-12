#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <typeinfo>
#include "matrix.h"

matrix::matrix(){
  complex **A = new complex* [1];
  A[0] = new complex [1];
  M = A;
  n_rows = 1;
  n_columns = 1;}

matrix::matrix(int m, int n){
  complex **A = new complex* [m];
  for(int i = 0 ; i < m ; i++)
    A[i] = new complex [n];
  M = A;
  n_rows = m;
  n_columns = n;
}



matrix::matrix(complex **A, int m, int n){
  M = A;
  n_rows = m;
  n_columns = n;
}



complex** matrix::get_matrix(){
  return M;}



int matrix::get_n_rows(){
  return n_rows;}



int matrix::get_n_columns(){
  return n_columns;}



std::string matrix::to_string(bool vector_format){
  
  std::ostringstream stream;
  
  if(vector_format){
    if(n_rows != 1 && n_columns != 1){
      std::cout << "matrix can not be written in vector format!" << std::endl;
      exit(0);}

    stream << '[';
    
    if(n_rows == 1)
      for(int j = 0 ; j < n_columns ; j++)
	stream << M[0][j].to_string() << "  ";
    
    if(n_columns == 1)
      for(int i = 0 ; i < n_rows ; i++)
	stream << M[i][0].to_string() << "  ";

    stream << "\b\b]";}

  else{
    unsigned int max[n_columns];
    for(int j = 0 ; j < n_columns ; j++)
      max[j] = 1;
    for(int j = 0 ; j < n_columns ; j++)
      for(int i = 0 ; i < n_rows ; i++)
	if (M[i][j].to_string().length() > max[j])
	  max[j] = M[i][j].to_string().length();
    
    for(int i = 0 ; i < n_rows ; i++){
      for(int j = 0 ; j < n_columns ; j++){
	if(j == 0 && i == 0)
	  stream << "[[";
	if(j == 0 && i != 0)
	  stream << " [";
	stream << M[i][j].to_string()
	       << std::string(max[j]+2-M[i][j].to_string().length(), ' ');
	if(j == n_columns-1)
	  stream << "\b\b]";}
      if(i < n_rows-1)
	stream << '\n';}
    stream << ']';}
  return stream.str();}



matrix matrix::operator+(matrix A){
  if(n_rows != A.n_rows || n_columns != A.n_columns){
    std::cout << "incompatible dimensions!" << std::endl;
    exit(0);}

  complex **B = new complex* [n_rows];
  for(int i = 0 ; i < n_rows ; i++)
    B[i] = new complex [n_columns];

  for(int i = 0 ; i < n_rows ; i++)
    for(int j = 0 ; j < n_columns ; j++)
      B[i][j] = M[i][j]+A.M[i][j];

  matrix N(B, n_rows, n_columns);
  return N;}



matrix matrix::operator-(matrix A){
  if(n_rows != A.n_rows || n_columns != A.n_columns){
    std::cout << "incompatible dimensions!" << std::endl;
    exit(0);}

  complex **B = new complex* [n_rows];
  for(int i = 0 ; i < n_rows ; i++)
    B[i] = new complex [n_columns];

  for(int i = 0 ; i < n_rows ; i++)
    for(int j = 0 ; j < n_columns ; j++)
      B[i][j] = M[i][j]-A.M[i][j];

  matrix N(B, n_rows, n_columns);
  return N;}



matrix matrix::operator*(matrix A){
  if(n_columns != A.n_rows){
    std::cout << "incompatible dimensions!" << std::endl;
    exit(0);}

  complex **B = new complex* [n_rows];
  for(int i = 0 ; i < n_rows ; i++)
    B[i] = new complex [A.n_columns];

  for(int i = 0 ; i < n_rows ; i++)
    for(int j = 0 ; j < A.n_columns ; j++)
      for(int k = 0 ; k < n_columns ; k++)
	B[i][j] = B[i][j] + M[i][k]*A.M[k][j];

  matrix N(B, n_rows, A.n_columns);
  return N;}



matrix matrix::operator*(complex z){
  complex **A = new complex* [n_rows];
  for (int i = 0 ; i < n_rows ; i++)
    A[i] = new complex [n_columns];

  for(int i = 0 ; i < n_rows ; i++)
    for(int j = 0 ; j < n_columns ; j++)
      A[i][j] = M[i][j]*z;

  matrix N(A, n_rows, n_columns);
  return N;}



matrix matrix::operator*(float a){
  complex z(a,0);
  return *this*z;}



matrix operator*(complex z, matrix A){
  return A*z;}



matrix operator*(float a, matrix A){
  return A*a;}



bool matrix::operator==(matrix A){
  bool is_equal = true;
  if(n_rows != A.n_rows || n_columns != A.n_columns)
    is_equal = false;
  else
    for(int i = 0 ; i < n_rows ; i++)
      for(int j = 0 ; j < n_columns ; j++)
	if(M[i][j] != A.M[i][j])
	  is_equal = false;
  return is_equal;}



bool matrix::operator!=(matrix A){
  return !(*this == A);}



matrix transpose(matrix A){
  complex **N = new complex* [A.n_columns];
  for (int j = 0 ; j < A.n_columns ; j++)
    N[j] = new complex [A.n_rows];

  for(int j = 0 ; j < A.n_columns ; j++)
    for(int i = 0 ; i < A.n_rows ; i++)
      N[j][i] = A.M[i][j];

  matrix B(N, A.n_columns, A.n_rows);
  return B;}



matrix conjugate(matrix A){
  complex **N = new complex* [A.n_rows];
  for (int i = 0 ; i < A.n_rows ; i++)
    N[i] = new complex [A.n_columns];

  for(int i = 0 ; i < A.n_rows ; i++)
    for(int j = 0 ; j < A.n_columns ; j++)
      N[i][j] = conjugate(A.M[i][j]);

  matrix B(N, A.n_rows, A.n_columns);
  return B;}



matrix matrix::submatrix(int k,int l){
  if(k >= n_rows){
    std::cout << k << " is out of range." << std::endl;
    exit(0);}
  if(l >= n_columns){
    std::cout << l << " is out of range." << std::endl;
    exit(0);}
  
  complex **A = new complex* [n_rows-1];
  for(int i = 0 ; i < n_rows-1 ; i++)
    A[i] = new complex [n_columns-1];
  
  for(int i = 0 ; i < n_rows ; i++)
    for(int j = 0 ; j < n_columns ; j++){
      if(i < k  &&  j < l)
	A[i][j]=M[i][j];
      if(i < k  &&  j > l)
	A[i][j-1]=M[i][j];
      if(i > k  &&  j < l)
	A[i-1][j]=M[i][j];
      if(i > k  &&  j > l)
	A[i-1][j-1]=M[i][j];}
  matrix N(A, n_rows-1, n_columns-1);
  return N;}



complex matrix::det(){
  if(n_rows != n_columns){
    std::cout << "matrix is not square!" << std::endl;
    exit(0);}

  if(n_rows == 1)
    return M[0][0];

  else{
    complex determinant;
    for(int j = 0 ; j < n_rows ; j++){
      if(j%2 == 0)
	determinant = determinant + M[0][j] * (*this).submatrix(0,j).det();
      else
	determinant = determinant - M[0][j] * (*this).submatrix(0,j).det();}
    return determinant;}
}



matrix matrix::matrix_inverse(){
    if(n_rows != n_columns){
    std::cout << "matrix is not square!" << std::endl;
    exit(0);}

    if((*this).det() == 0){
    std::cout << "the matrix is not invertible!" << std::endl;
    exit(0);}

    complex **A = new complex* [n_rows];
    for(int i = 0 ; i < n_rows ; i++)
      A[i] = new complex [n_columns];

    for(int i = 0 ; i < n_rows ; i++)
      for(int j = 0 ; j < n_columns ; j++){
	if((i+j)%2 == 0)
	  A[j][i] = (*this).submatrix(i,j).det();
	else
	  A[j][i] = (-1)*((*this).submatrix(i,j).det());}
    
    matrix N(A, n_rows, n_columns);
    return (1/(*this).det())*N;}



/* The following function is to determine whether a matrix
is positive define or not! It is based on the Sylvester's
criterion and works only for Hermitian matrices.*/
bool is_positive(matrix A){
  if(A.n_rows != A.n_columns){
    std::cout << "matrix is not square!" << std::endl;
    exit(0);}

  // Check whether the matrix is Hermitian.
  if(A != conjugate(transpose(A))){
    std::cout << "matrix is not Hermitian!" << std::endl;
    exit(0);}

  matrix B = A;
  bool is_positive_definite = is_positive(B.det());
  for(int i = 1 ; i < A.n_rows ; i++){
    if(!is_positive_definite)
      return false;
    else{
      B = B.submatrix(B.n_rows-1, B.n_columns-1);
      is_positive_definite = is_positive(B.det());}}
  return is_positive_definite;}



bool jacobi_criterion(matrix A){
  if(A.n_rows != A.n_columns){
    std::cout << "matrix is not square!" << std::endl;
    exit(0);}

  bool row_jacobi_criterion = true;
  bool column_jacobi_criterion = true;
  float sum;
  for(int i = 0 ; i < A.n_rows ; i++){
    sum = 0;
    for(int j = 0 ; j < A.n_columns ; j++)
      if(i != j)
	sum = sum + abval(A.M[i][j]);
    if(sum >= abval(A.M[i][i]))
      row_jacobi_criterion = false;}
  
  for(int j = 0 ; j < A.n_columns ; j++){
    sum = 0;
    for(int i = 0 ; i < A.n_rows ; i++)
      if(i != j)
	sum = sum + abval(A.M[i][j]);
    if(sum >= abval(A.M[j][j]))
      column_jacobi_criterion = false;}
  return row_jacobi_criterion || column_jacobi_criterion;}



/* The following function gets a string in the format
of a matrix [[A11,...,A1n],...,[Am1,...,Amn]] or a
vector [A1,...,An] and converts it into a matrix object.
Note that in case the input has a vector format, the
returned matrix is of dimension 1xn! */
matrix string_to_matrix(std::string input){

  // removing the spaces
  for(unsigned int i = 0 ; i < input.length() ; i++)
    while(input[i] == ' ')
      input = input.replace(i,1,"");

  // checking the structure of input
  if(input[0] != '[' || input[input.length()-1] != ']'){
    std::cout << "input error!" << std::endl;
    exit(0);}

  // checking whether the input has a matrix format and
  // removing the first and the last brackets, if so.
  if(input[1] == '[')
    input = input.substr(1,input.length()-2);
  
  // comparison between left and right brackets
  int left_brackets = count(input.begin(), input.end(), '[');
  int right_brackets = count(input.begin(), input.end(), ']');
  if(left_brackets != right_brackets){
    std::cout << "input error!" << std::endl;
    exit(0);}

  int n_rows = left_brackets;
  std::string *rows = new std::string [n_rows];
  
  for(int i = 0 ; i < n_rows ; i++){
    rows[i] = input.substr(0, input.find(']')+1);
    if(i < n_rows - 1){
      if(input[input.find(']')+1] != ','){
	std::cout << "input error!" << std::endl;
	exit(0);}
      input = input.substr(input.find(']')+2);}
  }

  int first_row_commas = count(rows[0].begin(), rows[0].end(), ',');
  const std::string allowed_chars = "0123456789i,.+-[]";

  // checking the structure of each row
  for(int i = 0 ; i < n_rows ; i++){
    if(rows[i][0] != '['){
      std::cout << "input error!" << std::endl;
      exit(0);}
    if(count(rows[i].begin(), rows[i].end(), ',') != first_row_commas){
      std::cout << "input error!" << std::endl;
      exit(0);}
    for(unsigned int j = 0 ; j < rows[i].length() ; j++){
      if(allowed_chars.find(rows[i][j]) == allowed_chars.npos){
	std::cout << "input error!" << std::endl;
	exit(0);}}
  }

  int n_columns = first_row_commas + 1;
  complex **M = new complex* [n_rows];
  for(int i = 0 ; i < n_rows ; i++)
    M[i] = new complex [n_columns];

  for(int i = 0 ; i < n_rows ; i++){
    rows[i] = rows[i].substr(1,rows[i].length()-2); // removing brackets
    rows[i] += ',';
    for(int j = 0 ; j < n_columns ; j++){
      M[i][j] = string_to_complex(rows[i].substr(0,rows[i].find(',')));
      rows[i] = rows[i].substr(rows[i].find(',')+1);}}
  matrix A(M, n_rows, n_columns);
  return A;}


float frobenius_norm(matrix A){
  complex sum;
  for(int i = 0 ; i < A.n_rows ; i++)
    for(int j = 0 ; j < A.n_columns ; j++)
      sum = sum + A.M[i][j] * conjugate(A.M[i][j]);
  float a = abval(sum);
  return sqrt(a);}


float matrix::matrix_norm(matrix b){
  if(b.n_rows != 1  &&  b.n_columns != 1){
    std::cout << "matrix has not vector format!" << std::endl;
    exit(0);}

  if(!is_positive(*this)){
    std::cout << "matrix is not positive definite!" << std::endl;
    exit(0);}

  complex sum;
  
  if(b.n_rows == 1){
    if(b.n_columns != n_columns){
      std::cout << "incompatible matrix dimensions!" << std::endl;
      exit(0);}
    for(int i = 0 ; i < n_rows ; i++)
      for(int j = 0 ; j < n_columns ; j++)
	sum = sum + b.M[0][i]*M[i][j]*conjugate(b.M[0][j]);}

  if(b.n_columns == 1){
    if(b.n_rows != n_rows){
      std::cout << "incompatible matrix dimensions!" << std::endl;
      exit(0);}
    for(int i = 0 ; i < n_rows ; i++)
      for(int j = 0 ; j < n_columns ; j++)
	sum = sum + b.M[i][0]*M[i][j]*conjugate(b.M[j][0]);}
  float a = abval(sum);
  return sqrt(a);

}
