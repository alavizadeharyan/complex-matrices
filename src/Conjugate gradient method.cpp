#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "matrix.h"

int main(){
  std::cout << std::endl << std::string(36,'#') << std::endl
	    << "This program is aimed at solving the\n"
	    << "equation Ax = b using  the conjugate\n"
	    << "gradient method.\n"
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
  bool b_is_got, x_init_is_got;
  std::string str_A, str_b, str_x_init;
  matrix A, b, x_init, x, d, remainder, remainder_old;
  float alpha, beta, error;
  int counter;
  
  while (do_you_continue == "yes"){

    b_is_got = false;
    x_init_is_got = false;
    error = 1.00;
    counter = 1;
    
    std::cout << "\nPlease enter the matrix A. Note that\n"
	      << "A should be Hermitian positive definite.\n"
	      << "A = ";
    getline(std::cin, str_A);
    A = string_to_matrix(str_A);
    
    if(A.get_n_rows() != A.get_n_columns()){
      std::cout << "The matrix is not square!\n"
		<< "Do you want to continue (yes/no)? ";
      getline(std::cin, do_you_continue);
      continue;}

    if(A != conjugate(transpose(A))){
      std::cout << "Matrix is not Hermitian!\n"
		<< "Do you want to continue (yes/no)? ";
      getline(std::cin, do_you_continue);
      continue;}

    if(!is_positive(A)){
      std::cout << "Matrix is not positive definite!\n"
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
    remainder = b - A*x;
    d = remainder;

    std::cout << "\nPlease  enter  the  error value. The\n"
	      << "algorith  stops  once  the  criteria\n"
	      << "|Ax_k - b| < error value, is satisfied.\n"
	      << "error value = ";
    std::cin >> error;
    std::cin.ignore();

    while(frobenius_norm(remainder) > error){
      alpha = pow(frobenius_norm(remainder)/A.matrix_norm(d), 2);
      x = x + alpha * d;
      remainder_old = remainder;
      remainder = remainder - alpha*A*d;
      beta = pow(frobenius_norm(remainder)/frobenius_norm(remainder_old), 2);
      d = remainder - beta*d;
      std::cout << counter << ": " << x.to_string(true) << std::endl;
      counter++;}

    std::cout << "\nDo you want to  run the  program for\n"
	      << "differnet A and b (yes/no)? ";
    getline(std::cin, do_you_continue);
    
  } // end of while
  
  return 0;}
