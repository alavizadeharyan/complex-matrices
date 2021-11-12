#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <typeinfo>
#include <algorithm>
#include "complex.h"

complex::complex(){re = 0; im = 0;}

complex::complex(float real, float imaginary){
  re = real;
  im = imaginary;}

float complex::get_re(){
  return re;}

float complex::get_im(){
  return im;}

void complex::set_re(float a){
  re = a;}

void complex::set_im(float b){
  im = b;}

complex conjugate(complex z){
  complex conj(z.re,-z.im);
  return conj;}

complex conjugate(float a){
  complex conj(a,0);
  return conj;}

float abval(complex z){
  return sqrt((z.re*z.re)+(z.im*z.im));}

float abval(float a){
  if(a >= 0)
    return a;
  else
    return -a;}

std::string complex::to_string(){
  std::ostringstream stream;
  if(im>0 && im!=1 && re!=0)
    stream << re << "+" << im << "i";
  if(im>0 && im!=1 && re==0)
    stream << im << "i";
  if(im==1 && re!=0)
    stream << re << "+i";
  if(im==1 && re==0)
    stream << "i";
  if(im<0 && im!=-1 && re!=0)
    stream << re << im << "i";
  if(im<0 && im!=-1 && re==0)
    stream << im << "i";
  if(im==-1 && re!=0)
    stream << re << "-i";
  if(im==-1 && re==0)
    stream << "-i";
  if(im==0)
    stream << re;
  return stream.str();}

complex complex::operator+(complex z){
  complex s(z.re + re, z.im + im);
  return s;}

complex complex::operator+(float a){
  complex s(a + re, im);
  return s;}

complex operator+(float a, complex z){
  return z+a;}

complex complex::operator*(complex z){
  complex p(z.re*re - z.im*im, z.re*im + z.im*re);
  return p;}

complex complex::operator*(float a){
  complex p(a*re, a*im);
  return p;}

complex operator*(float a, complex z){
  return z*a;}

complex complex::operator/(complex z){
  complex z_inverse(z.re/(z.re*z.re+z.im*z.im), -z.im/(z.re*z.re+z.im*z.im));
  return *this*z_inverse;}

complex complex::operator/(float a){
  complex d(re/a, im/a);
  return d;}

complex operator/(float a, complex z){
  complex z_inverse(z.re/(z.re*z.re+z.im*z.im), -z.im/(z.re*z.re+z.im*z.im));
  return z_inverse*a;}

complex complex::operator-(complex z){
  complex m(re-z.re, im-z.im);
  return m;}

complex complex::operator-(float a){
  complex m(re-a, im);
  return m;}

complex operator-(float a, complex z){
  complex m(a-z.re, -z.im);
  return m;}

bool complex::operator== (complex z){
  if(re == z.re && im == z.im)
    return true;
  else
    return false;}

bool complex::operator== (float a){
  if(re == a && im == 0)
    return true;
  else
    return false;}

bool operator== (float a, complex z){
  return z == a;}

bool complex::operator!= (complex z){
  return !(*this == z);}

bool complex::operator!= (float a){
  return !(*this == a);}

bool operator!= (float a, complex z){
  return z != a;}

bool is_positive(complex z){
  if(z.re>0 && z.im==0)
    return true;
  else
    return false;}

bool is_positive(float a){
  return a > 0;}

complex inner_product(complex *a, complex *b, int n){
  complex inner_product;
  for(int i = 0 ; i < n ; i++)
    inner_product = inner_product + conjugate(a[i])* b[i];
  return inner_product;
}

complex string_to_complex(std::string str){
  if(count(str.begin(), str.end(), 'i') > 1){
    std::cout << "input error!" << std::endl;
    exit(0);}
  complex z;
  int i = str.length()-1;
  while( str[i] != '+'  &&  str[i] != '-'  &&  i > 0)
    i--;
  if(i == 0){
    if(str.find("i") == str.npos){
      z.set_re(std::stof(str));
      z.set_im(0);}
    else{
      if(str == "i" || str == "+i"){
	z.set_re(0);
	z.set_im(1);}
      else if(str == "-i"){
	z.set_re(0);
	z.set_im(-1);}
      else{
	str = str.replace(str.find("i"), 1, "");
	z.set_re(0);
	z.set_im(std::stof(str));}}}
  else{
    std::string re, im;
    if(str.substr(0,i).find('i') == str.substr(0,i).npos){
      re = str.substr(0,i);
      im = str.substr(i);}
    else{
      re = str.substr(i);
      im = str.substr(0,i);}
    if(im == "i" || im == "+i"){
      z.set_re(std::stof(re));
      z.set_im(1);}
    else if(im == "-i"){
      z.set_re(std::stof(re));
      z.set_im(-1);}
    else{
      im = im.replace(im.find("i"), 1, "");
      z.set_re(std::stof(re));
      z.set_im(std::stof(im));}}
  return z;}
    
    
