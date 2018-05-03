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

const string MLX0_1_XMIT = "/sys/class/infiniband/mlx4_0/ports/1/counters/port_xmit_data";
const string MLX1_1_XMIT = "/sys/class/infiniband/mlx4_1/ports/1/counters/port_xmit_data";
const string MLX0_1_RCV = "/sys/class/infiniband/mlx4_0/ports/1/counters/port_rcv_data";
const string MLX1_1_RCV = "/sys/class/infiniband/mlx4_1/ports/1/counters/port_rcv_data";

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
    double dif0Xgbps, dif1Xgbps, dif0Rgbps, dif1Rgbps;

    // ifstream file0(MLX0_1_PATH);
    // ifstream file1(MLX1_1_PATH);
    
    for (;;) {
   		ifstream fp0_xmit(MLX0_1_XMIT);
   		ifstream fp1_xmit(MLX1_1_XMIT);
   		ifstream fp0_rcv(MLX0_1_RCV);
   		ifstream fp1_rcv(MLX1_1_RCV);

   		/* MLX0_1_XMIT */
	    prev = getcnt(fp0_xmit);
		auto t1 = chrono::high_resolution_clock::now();

	    this_thread::sleep_for(chrono::microseconds((int)(MilliSec*1000)));
		curr = getcnt(fp0_xmit);
		auto t2 = chrono::high_resolution_clock::now();

		diff = curr - prev;

	    // floating-point duration: no duration_cast needed
	    std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
	    double dt = fp_ms.count();
	    dif0Xgbps = diff*4/GB/dt*1000;

	    // if (dif0gbps > 1.0)	
	    cout <<  date::format("%F %T", time_point_cast<microseconds>(system_clock::now())) << ", dif0Xgbps = " << dif0Xgbps << ", Spent " << fp_ms.count() << " ms." << endl;


   		/* MLX1_1_XMIT */
	    prev = getcnt(fp1_xmit);
		t1 = chrono::high_resolution_clock::now();

	    this_thread::sleep_for(chrono::microseconds((int)(MilliSec*1000)));

		curr = getcnt(fp1_xmit);
		t2 = chrono::high_resolution_clock::now();

		diff = curr - prev;

	    // floating-point duration: no duration_cast needed
	    fp_ms = t2 - t1;
	    dt = fp_ms.count();
	    dif1Xgbps = diff*4/GB/dt*1000;

	    // if (dif1gbps > 1.0)	
	    cout <<  date::format("%F %T", time_point_cast<microseconds>(system_clock::now())) << ", dif1Xgbps = " << dif1Xgbps << ", Spent " << fp_ms.count() << " ms." << endl;


	    /* MLX0_1_RCV */
	    prev = getcnt(fp0_rcv);
		t1 = chrono::high_resolution_clock::now();

	    this_thread::sleep_for(chrono::microseconds((int)(MilliSec*1000)));
		curr = getcnt(fp0_rcv);
		t2 = chrono::high_resolution_clock::now();

		diff = curr - prev;

	    // floating-point duration: no duration_cast needed
	    fp_ms = t2 - t1;
	    dt = fp_ms.count();
	    dif0Rgbps = diff*4/GB/dt*1000;

	    // if (dif0gbps > 1.0)	
	    cout <<  date::format("%F %T", time_point_cast<microseconds>(system_clock::now())) << ", dif0Rgbps = " << dif0Rgbps << ", Spent " << fp_ms.count() << " ms." << endl;


   		/* MLX1_1_RCV */
	    prev = getcnt(fp1_rcv);
		t1 = chrono::high_resolution_clock::now();

	    this_thread::sleep_for(chrono::microseconds((int)(MilliSec*1000)));

		curr = getcnt(fp1_rcv);
		t2 = chrono::high_resolution_clock::now();

		diff = curr - prev;

	    // floating-point duration: no duration_cast needed
	    fp_ms = t2 - t1;
	    dt = fp_ms.count();
	    dif1Rgbps = diff*4/GB/dt*1000;

	    // if (dif1gbps > 1.0)	
	    cout <<  date::format("%F %T", time_point_cast<microseconds>(system_clock::now())) << ", dif1Rgbps = " << dif1Rgbps << ", Spent " << fp_ms.count() << " ms." << endl;


	    fp0_xmit.close();
	    fp1_xmit.close();
	    fp0_rcv.close();
	    fp1_rcv.close();
    }

    return 0; 
}
