#include "complex.h"

class matrix
{
public:
  matrix();
  matrix(int, int);
  matrix(complex**, int, int);
  complex** get_matrix();
  int get_n_rows();
  int get_n_columns();
  std::string to_string(bool);
  matrix operator+(matrix);
  matrix operator-(matrix);
  matrix operator*(matrix);
  matrix operator*(complex);
  matrix operator*(float);
  friend matrix operator*(complex, matrix);
  friend matrix operator*(float, matrix);
  bool operator==(matrix);
  bool operator!=(matrix);
  friend matrix transpose(matrix);
  friend matrix conjugate(matrix);
  matrix submatrix(int ,int);
  complex det();
  matrix matrix_inverse();
  friend bool is_positive(matrix);
  friend bool jacobi_criterion(matrix);
  friend float frobenius_norm(matrix);
  float matrix_norm(matrix);
private:
  complex **M;
  int n_rows;
  int n_columns;
};

matrix string_to_matrix(std::string);
