#include<string>

class complex
{
public:
  complex();
  complex(float, float);
  float get_re();
  float get_im();
  void set_re(float);
  void set_im(float);
  friend complex conjugate(complex);
  complex operator+(complex);
  complex operator+(float);
  friend complex operator+(float, complex);
  complex operator*(complex);
  complex operator*(float);
  friend complex operator*(float, complex);
  complex operator/(complex);
  complex operator/(float);
  friend complex operator/(float, complex);
  complex operator-(complex);
  complex operator-(float);
  friend complex operator-(float, complex);
  friend float abval(complex);
  bool operator== (complex);
  bool operator== (float);
  friend bool operator== (float, complex);
  bool operator!= (complex);
  bool operator!= (float);
  friend bool operator!= (float, complex);
  friend bool is_positive(complex);
  std::string to_string();
private :
  float re;
  float im;
};

bool is_positive(float);
complex conjugate(float);
float abval(float);
complex string_to_complex(std::string);
complex inner_product(complex* , complex* , int);
