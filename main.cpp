#include <iostream>
#include <vector>

std::vector<std::vector<double>> Hilbert(int n){
    std::vector<std::vector<double>> H(n);


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            H[i].push_back((double)1.0 / 
                     ((i + 1) + (j + 1) - 1.0));
        }
    } 

    return H;
}

std::vector<std::vector<double>> expanded_a(std::vector<std::vector<double>> a, int n){
    std::vector<double> x(n);
    for(int i = 0; i < n; ++i)
        x[i] = 1;

    std::vector<double> b(n);
    for (int i = 0; i < n; ++i){
        double sum = 0;
        for (int j = 0; j < n; ++j){
            sum += a[i][j] * x[i];
        }
        a[i].push_back(sum);
    }
    return a;
}

void printArr(std::vector<std::vector<double> > &a){
  for (int i = 0; i < a.size(); i++){
    for (int j = 0; j < a[i].size(); j++){
      std::cout<<a[i][j]<<" ";    
    }
    std::cout<<"\n";
  }
}

void composition(std::vector<double> &i, std::vector<double> &j, double k){ //  i = j *k +i
  for (int d = 0; d < i.size(); d++){
    i[d] = i[d] + j[d]*k;         
  }
}

void divStr(std::vector<double> &d, double k){
  for (int i = 0; i<d.size(); i++){
    d[i] = d[i]/k;
  }
}

void  solve(std::vector<std::vector<double>> &a){     

  for (int k = 0; k<a.size(); k++){
    if (abs(a[k][k]) < 0.00000001){
      for (int i = k+1; i<a.size(); i++){
        if (a[i][k] > 0.00000001){
          std::swap(a[i], a[k]);
          break;
        }
      }
    }
  
    if (a[k][k] < 0.999999999 || a[k][k] > 1.000000001){ 
      divStr(a[k], a[k][k]);
    }
  
    for (int i= k+1; i<a.size(); i++){
      composition(a[i], a[k], -a[i][k]); 
    }
  }
  
  std::cout<<std::endl;
  
  for (int k = a.size()-1; k>=0; k--){
    for (int i = k-1; i>=0; i--){
      composition(a[i], a[k], -a[i][k]);
    }
  }
}

int main() {

  int n = 10;

  std::vector<std::vector<double>> a = Hilbert(n);
  a = expanded_a(a, n);

  printArr(a);
  
  solve(a);
  std::cout << "Solved" << std::endl;

  for (int i = 0; i < n; ++i){
    std::cout << a[i][n] << std::endl;
  }
  return 0;
}