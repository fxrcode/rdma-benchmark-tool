# readme
* It's a simple cpp to grab infiniband port_xmit_data file and measure the diff, validated with qperf on xi shi yi gou.
* easy to build, only need `ibpq.cc` and `date.h`. Then do: `g++ -Wall -g -std=c++11 -O0 ibpq.cc -o run`. 

# helper date.h
* I followed this SOP[How to convert std::chrono::time_point to calendar datetime string with fractional seconds?](https://stackoverflow.com/a/12844843/3984911)
