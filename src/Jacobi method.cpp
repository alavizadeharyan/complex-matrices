#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "matrix.h"

int main(){
  std::cout << std::endl << std::string(36,'#') << std::endl
	    << "This program is aimed at solving the" << std::endl
	    << "equation Ax = b using Jacobi method." << std::endl
	    << std::string(36,'#') << std::endl << std::endl
	    << "For entering the matrices,  use  the\n"
	    << "format: [[A11,...,A1n],...[Am1,...,Amn]]\n"
	    << "For entering  the vectors,  you  can\n"
	    << "either use the matrix format, or the\n"
	    << "vector format as: [A1,...,An]\n"
	    << "You  can  also  use  spaces for more\n"
	    << "readability!\n"
	    << "The complex numbers are in the normal\n"
	    << "format: 1+2i, -2i+1, 1-2i, 1+.5i, ...\n\n\n";
  
  std::string do_you_continue = "yes";
  bool all_diagonal_elements_are_non_zero;
  bool b_is_got, x_init_is_got;
  std::string str_A, str_b, str_x_init;
  matrix A, b, x_init, x;
  int itterations = 1;
  
  while (do_you_continue == "yes"){

    all_diagonal_elements_are_non_zero = true;
    b_is_got = false;
    x_init_is_got = false;
    
    std::cout << "\nPlease enter the matrix A. Note that\n"
	      << "A should  have  no zero entry on its\n"
	      << "main diagonal and  it  must  satisfy\n"
	      << "the strong row (column) sum criterion.\n"
	      << "A = ";
    getline(std::cin, str_A);
    A = string_to_matrix(str_A);
    
    if(A.get_n_rows() != A.get_n_columns()){
      std::cout << "The matrix is not square!\n"
		<< "Do you want to continue (yes/no)? ";
      getline(std::cin, do_you_continue);
      continue;}
    
    for(int i = 0 ; i < A.get_n_rows() ; i++)
      if(A.get_matrix()[i][i] == 0)
	all_diagonal_elements_are_non_zero = false;
    if(!all_diagonal_elements_are_non_zero){
      std::cout << "Some elements on the diagonal are zero!\n"
		<< "Do you want to continue (yes/no)? ";
      getline(std::cin, do_you_continue);
      continue;}

    if(!jacobi_criterion(A)){
      std::cout << "Matrix does  not satisfy  the strong\n"
		<< "row (column) sum criterion!\n"
		<< "Do you want to continue (yes/no)? ";
      getline(std::cin, do_you_continue);
      continue;}

    while(!b_is_got){
      std::cout << "\nPlease enter vecor b.\n" << "b = ";
      getline(std::cin, str_b);
      b = string_to_matrix(str_b);
    
      if(!((b.get_n_columns() == 1 && b.get_n_rows() == A.get_n_rows()) ||
	   (b.get_n_rows() == 1 && b.get_n_columns() == A.get_n_rows()))){
	std::cout << "Vector b does  not  have  compatible\n"
		  << "dimensions!\n"
		  << "Do you want to continue (yes/no)? ";
	getline(std::cin, do_you_continue);
	if(do_you_continue != "yes")
	  b_is_got = true;}
      else
	b_is_got = true;}

    if(do_you_continue != "yes")
      continue;

    while(!x_init_is_got){
      std::cout << "\nPlease enter an  initialization  for\n"
		<< "vector x:\n" << "x_init = ";
      getline(std::cin, str_x_init);
      x_init = string_to_matrix(str_x_init);
    
      if(!((x_init.get_n_columns() == 1 && x_init.get_n_rows() == A.get_n_rows()) ||
	   (x_init.get_n_rows() == 1 && x_init.get_n_columns() == A.get_n_rows()))){
	std::cout << "Vector x does  not  have  compatible\n"
		  << "dimensions!\n"
		  << "Do you want to continue (yes/no)? ";
	getline(std::cin, do_you_continue);
	if(do_you_continue != "yes")
	  x_init_is_got = true;}
      else
	x_init_is_got = true;}

    if(do_you_continue != "yes")
      continue;

    if(b.get_n_rows() == 1)
      b = transpose(b);

    if(x_init.get_n_rows() == 1)
      x_init = transpose(x_init);

    x = x_init;

    std::cout << "How  many  times  do  you  want  the\n"
	      << "algorithm to be itterated? ";
    std::cin >> itterations;
    std::cin.ignore();

    complex **B = new complex* [A.get_n_rows()];
    complex **C = new complex* [A.get_n_rows()];
    for(int i = 0 ; i < A.get_n_rows() ; i++){
      B[i] = new complex [A.get_n_rows()];
      C[i] = new complex [A.get_n_rows()];}

    for(int i = 0 ; i < A.get_n_rows() ; i++)
      for(int j = 0 ; j < A.get_n_columns() ; j++)
	if(i == j)
	  B[i][j] = A.get_matrix()[i][j];
	else
	  C[i][j] = A.get_matrix()[i][j];

    matrix D(B, A.get_n_rows(), A.get_n_columns());
    matrix N(C, A.get_n_rows(), A.get_n_columns());

    for(int itter = 0 ; itter < itterations ; itter++){
      x = D.matrix_inverse()*(b-N*x);
      std::cout << itter << ": " << x.to_string(true) << std::endl;}

    std::cout << "error = |Ax_" << itterations << " - b| = "
	      << frobenius_norm(A*x-b) << std::endl;

    std::cout << "\nDo you want to  run the  program for\n"
	      << "differnet A and b (yes/no)? ";
    getline(std::cin, do_you_continue);
    
  } // end of while
  
  return 0;}
