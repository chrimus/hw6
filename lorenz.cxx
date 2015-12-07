#include <iostream>
#include <fstream>


using namespace std;

void func(double* const f, const double* para, double x, double y, double z);


int main(){
  double tstart = 0, tend = 100, dt = 0.01;	// define timesteps
  int N = (tend-tstart)/dt+1;			// calculate number of iteration
  double para[3];				// creates array for parameters
  para[0] = 10.0;				// defines parameters
  para[1] = 28.0;
  para[2] = 8/3.0;
  
  double x = 1, y = 1, z = 1;			// start values
  double k1[3], k2[3], k3[3], k4[3];		// creates arrays for differtent loops
  
  ofstream out("data.txt");			//opens filestream
  out << tstart << "\t" << x << "\t" << y << "\t" << z << endl;	// writes start values
  
  for(int i=1; i<(N+1); i++){			// for-loop for N iterations
    func(k1, para, x, y, z);			// calculate different loops...
    func(k2, para, x+dt/2*k1[0], y+dt/2*k1[1], z+dt/2*k1[2]);
    func(k3, para, x+dt/2*k2[0], y+dt/2*k2[1], z+dt/2*k2[2]);
    func(k4, para, x+dt*k3[0], y+dt*k3[1], z+dt*k3[2]);
    
    x += dt/6*(k1[0]+2*k2[0]+2*k3[0]+k4[0]);	// calculates different coordinates via RK
    y += dt/6*(k1[1]+2*k2[1]+2*k3[1]+k4[1]);
    z += dt/6*(k1[2]+2*k2[2]+2*k3[2]+k4[2]);
    
  out << tstart+i*dt << "\t" << x << "\t" << y << "\t" << z << endl;	// writes coordinates to file
  }
  
  out.close();
  return 0;
}

void func(double* const f, const double* para, double x, double y, double z){	//function to calculate loops
  f[0] = para[0]*(y-x);		// calculates loop-value for x
  f[1] = x*(para[1]-z)-y;	// calculates loop-value for y
  f[2] = x*y-para[2]*z;		// calculates loop-value for z
}