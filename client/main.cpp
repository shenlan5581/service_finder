/*
*
*   test
*
*/


#include <iostream>
#include <string>
using namespace std;

#include "service_finder_c.h"
extern  k::service_finder_c FIND;


int main() 
{
  FIND._register("web","192","8080");

  while(1);
  
}
