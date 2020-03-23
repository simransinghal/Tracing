# Jaeger Cpp Client Example for Distributed Tracing

This repo has example for tracing modules written in C++ using jaeger UI. To instrument the program with jaeger and run it, various jaeger dependencies made available. Also we need to setup jaeger backend and run it to see the traces on the jaeger UI. C++ OpenTracing binding for Jaeger is froked from [here](https://github.com/jaegertracing/jaeger-client-cpp). One can read about OpenTracing and Jaeger [here](https://medium.com/velotio-perspectives/a-comprehensive-tutorial-to-implementing-opentracing-with-jaeger-a01752e1a8ce).

## Clone Repository
```bash
git clone https://github.com/simransinghal/Tracing.git
cd Tracing
``` 

## Launch Jacker UI
For setting up Jaegar UI, Docker is required. [Install Docker](https://docs.docker.com/install/) on Linux using:-
```bash
sudo apt-get update
sudo snap install docker
sudo apt  install docker.io
```
We setup and run the [all-in-one jaeger docker image](https://www.jaegertracing.io/docs/1.6/getting-started/) to see JAegar UI.
```bash
sudo docker run -d --name jaeger   -e COLLECTOR_ZIPKIN_HTTP_PORT=9411   -p 5775:5775/udp   -p 6831:6831/udp   -p 6832:6832/udp   -p 5778:5778   -p 16686:16686   -p 14268:14268   -p 9411:9411   jaegertracing/all-in-one:1.6
```
You can then navigate to http://localhost:16686 to access the Jaeger UI.

## Building
Jaeger cpp client is built using CMake. It will automatically download needed dependencies using [Hunter](https://docs.hunter.sh/en/latest/).

To build:

```bash
    mkdir build
    cd build
    cmake ..
    make
```


## Merge-Sort
This program traces the Merge-Sort algorithm and its helper function like merging the array. The [Merge-Sort example](https://github.com/simransinghal/Tracing/blob/master/examples/App.cpp) program can be run inside the build directory with:
```bash
./app ../examples/config.yml
```
The traces show 2 spans: mergeSort, and merge

![merge1](https://github.com/simransinghal/Tracing/blob/master/screenshots/mergesort1.png)

![mergesort2](https://github.com/simransinghal/Tracing/blob/master/screenshots/mergesort2.png)

## References
1) https://medium.com/velotio-perspectives/a-comprehensive-tutorial-to-implementing-opentracing-with-jaeger-a01752e1a8ce
2) https://deepikascribbles.wordpress.com/2019/07/04/using-jaeger-cpp-client-for-distributed-tracing-in-ceph/
3) https://github.com/jaegertracing/jaeger-client-cpp

Note:- To Delete all Docker containers that are not currently running, use command ``` sudo docker rm -f $(sudo docker ps -a -q)```.
