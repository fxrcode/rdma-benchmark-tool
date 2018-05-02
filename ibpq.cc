#include <fstream>
#include <sstream>
#include "date.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace date;
using namespace std;
using namespace std::chrono;
// g++ -Wall -g -std=c++11 -O0 ibpq.cc -o run

// const string MLX0_1_PATH = "./counters0";	
// const string MLX1_1_PATH = "./counters1";	

const string MLX0_1_PATH = "/sys/class/infiniband/mlx4_0/ports/1/counters/port_xmit_data";
const string MLX1_1_PATH = "/sys/class/infiniband/mlx4_1/ports/1/counters/port_xmit_data";

const double MilliSec =  1; // 1 ms  // MilliSec
std::string::size_type sz = 0;   // alias of size_t
const double GB = 1024 * 1024 * 1024;

inline unsigned long long int getcnt(ifstream &is) {
	string line;
	unsigned long long int cnt = 0;
	if (is.good()) {
		getline(is, line);
		// cout << "line:" << line << endl;
		cnt = stoull(line, &sz, 0);
	}
	is.clear();
	is.seekg(0, ios::beg);
    return cnt;
}

int main(int argc, char** argv)
{
    printf("FOREVER LOOP to get port_xmit_data diff at each %f ms\n", MilliSec);
    unsigned long long int prev, curr, diff;
    double dif0gbps, dif1gbps;

    // ifstream file0(MLX0_1_PATH);
    // ifstream file1(MLX1_1_PATH);
    
    for (;;) {
   		ifstream file0(MLX0_1_PATH);
   		ifstream file1(MLX1_1_PATH);

	    prev = getcnt(file0);
		auto t1 = chrono::high_resolution_clock::now();

	    this_thread::sleep_for(chrono::microseconds((int)(MilliSec*1000)));
		curr = getcnt(file0);
		auto t2 = chrono::high_resolution_clock::now();

		diff = curr - prev;

	    // floating-point duration: no duration_cast needed
	    std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
	    double dt = fp_ms.count();
	    dif0gbps = diff*4/GB/dt*1000;

	    // if (dif0gbps > 1.0)	
	    cout <<  date::format("%F %T", time_point_cast<microseconds>(system_clock::now())) << ", diff0GBps = " << dif0gbps << ", Spent " << fp_ms.count() << " ms." << endl;

	    prev = getcnt(file1);
		t1 = chrono::high_resolution_clock::now();

	    this_thread::sleep_for(chrono::microseconds((int)(MilliSec*1000)));

		curr = getcnt(file1);
		t2 = chrono::high_resolution_clock::now();

		diff = curr - prev;

	    // floating-point duration: no duration_cast needed
	    fp_ms = t2 - t1;
	    dt = fp_ms.count();
	    dif1gbps = diff*4/GB/dt*1000;

	    // if (dif1gbps > 1.0)	
	    cout <<  date::format("%F %T", time_point_cast<microseconds>(system_clock::now())) << ", diff1GBps = " << dif1gbps << ", Spent " << fp_ms.count() << " ms." << endl;

		cout <<  date::format("%F %T", time_point_cast<microseconds>(system_clock::now())) << ", sumGBps = " << dif0gbps + dif1gbps << endl;

	    file0.close();
	    file1.close();
    }

    return 0; 
}
