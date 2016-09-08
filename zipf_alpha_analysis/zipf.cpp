#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {

  if (argc != 4)
    return 1;
    
  double alpha = 0;
  int O = 0;
  double perc = 0.0;
  
  alpha = atof(argv[1]);
  O = atoi(argv[2]);
  perc = atof(argv[3]);
  
  
  /*
  bool alpha_done = false;
  while (!alpha_done) { 
  cout << "Please input alpha in range 0.5 to 3: ";
  cin >> alpha;
    if (alpha >= 0.5 && alpha <=3)
      alpha_done = true;
    else {
      cout << "invalid input" << endl;
    }
  }
  bool O_done = false;
  while (!O_done) { 
  cout << "Please input integer O in range 100 to 10000000000: ";
  cin >> O;
    if (O >= 100 && O <= 10000000000)
      O_done = true;
    else {
      cout << "invalid input" << endl;
    }
  }
  bool perc_done = false;
  while (!perc_done) { 
  cout << "Please input fraction of content to be cached in range 0 to 1 (exclusive): ";
  cin >> perc;
    if (perc > 0 && perc < 1)
      perc_done = true;
    else {
      cout << "invalid input" << endl;
    }
  }
  */
  
  long double Y = 0;
  
  for (int j = 1; j <= O; j++) {
    Y += 1/(pow(double(j),alpha));
  }
  
  long double x = 0.0;
  
  int k;
  
  for (k = 1; k <= O; k++) {
    x += (1/pow(double(k),alpha))/Y;
    if (x >= perc) break;
  }
  /*
  cout << "O = " << O << endl;
  cout << "Fraction of content = " << perc << endl; 
  */
  cout << "alpha:\t" << alpha << "\tk:\t" <<  k << endl;
  
  return 0;
}

