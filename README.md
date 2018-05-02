# readme
* It's a simple cpp to grab infiniband port_xmit_data file and measure the diff, validated with qperf on xi shi yi gou.
* easy to build, only need `ibpq.cc` and `date.h`. Then do: `g++ -Wall -g -std=c++11 -O0 ibpq.cc -o run`. 

## helper date.h
* I followed this SOP[How to convert std::chrono::time_point to calendar datetime string with fractional seconds?](https://stackoverflow.com/a/12844843/3984911)

## Baseline using `qperf`
* in server node: `qperf` start server.
* then in client node: `qperf 192.168.1.11 rc_rdma_read_bw rc_rdma_read_lat rc_rdma_write_bw rc_rdma_write_lat rc_rdma_write_poll_lat uc_rdma_write_bw uc_rdma_write_lat uc_rdma_write_poll_lat` (change 192.168.1.11 to server node ip)