// jaeger client adapted from https://github.com/jaegertracing/jaeger-client-cpp
// MergeSort code adapted from https://www.tutorialspoint.com/cplusplus-program-to-implement-merge-sort

#include <iostream>

#include <yaml-cpp/yaml.h>

#include <jaegertracing/Tracer.h>

#include <bits/stdc++.h>

namespace {

	void setUpTracer(const char* configFilePath)
	{
		auto configYAML = YAML::LoadFile(configFilePath);
		auto config = jaegertracing::Config::parse(configYAML);
		auto tracer = jaegertracing::Tracer::make(
				"sorting-service", config, jaegertracing::logging::consoleLogger());
		opentracing::Tracer::InitGlobal(
				std::static_pointer_cast<opentracing::Tracer>(tracer));
	}

	void merge(int *array, int l, int m, int r, const std::unique_ptr<opentracing::Span>& parentSpan)
	{
		auto span = opentracing::Tracer::Global()->StartSpan(
				"merge", { opentracing::ChildOf(&parentSpan->context()) });
		int i, j, k;
		//size of left and right sub-arrays
		int nl = m-l+1; //size of left sub-array
		int nr = r-m; //size of right sub-array
		int larr[nl], rarr[nr];
		//fill left and right sub-arrays
		for(i = 0; i<nl; i++)
			larr[i] = array[l+i];
		for(j = 0; j<nr; j++)
			rarr[j] = array[m+1+j];
		i = 0; j = 0; k = l;
		//marge temp arrays to real array
		while(i < nl && j<nr) {
			if(larr[i] <= rarr[j]) {
				array[k] = larr[i];
				i++;
			}else{
				array[k] = rarr[j];
				j++;
			}
			k++;
		}
		while(i<nl) {       //extra element in left array
			array[k] = larr[i];
			i++; k++;
		}
		while(j<nr) {     //extra element in right array
			array[k] = rarr[j];
			j++; k++;
		}

	}

	void mergeSort(int *array, int l, int r)
	{
		auto span = opentracing::Tracer::Global() -> StartSpan("mergeSort");
		if(l < r) {
			int m = l+(r-l)/2;
			// Sort first and second arrays
			mergeSort(array, l, m);
			mergeSort(array, m+1, r);
			merge(array, l, m, r, span);
		}
	}

}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "usage: " << argv[0] << " <config-yaml-path>\n";
		return 1;
	}
	setUpTracer(argv[1]);

	int array[] = {56, 88, 101 , 95, 10, 50};
	int sizeOfArray = sizeof(array) / sizeof(array[0]);
	mergeSort(array, 0, sizeOfArray - 1);

	opentracing::Tracer::Global()->Close();
	return 0;
}
