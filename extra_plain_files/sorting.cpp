#include <iostream>
#include <boost/compute/algorithm/stable_sort_by_key.hpp>
#include <vector>
#include <cstddef>
#include <algorithm>
#include <boost/assert.hpp>
//#include <boost/chrono.hpp>
#include <ctime>
//#include <boost/test/included/unit_test.hpp>
#include <ratio>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/is_sorted.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/device.hpp>
#include <boost/compute/algorithm/detail/insertion_sort.hpp>
#include <boost/compute/async/future.hpp>
#include <boost/compute/event.hpp>
#include <boost/compute/algorithm/detail/radix_sort.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/sort/spreadsort/spreadsort.hpp>
#include <boost/compute/core.hpp>
//#include <boost/test/included/unit_test.hpp>
#include <boost/assert.hpp>
#include <algorithm>
#include <boost/compute/algorithm/stable_sort.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_gpu.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/math.hpp>
#include <chrono>
#include <boost/compute/algorithm/sort_by_key.hpp>
namespace compute = boost::compute;
using namespace std;
using namespace std::chrono;


void stableSort(int l, double laikai[], int p)
{
        compute::device device = compute::system::default_device();
        using boost::compute::int_;

    vector<int> host_vector(10*l);

    generate(host_vector.begin(), host_vector.end(), rand);

    compute::vector<int> device_vector(host_vector.size(), compute::system::default_context());
      compute::copy(
        host_vector.begin(), host_vector.end(), device_vector.begin(), compute::system::default_queue()
    );

        compute::system::default_queue().finish();

        high_resolution_clock::time_point t1 = high_resolution_clock::now();
	compute::stable_sort(device_vector.begin(), device_vector.end(), compute::system::default_queue());
        compute::system::default_queue().finish();

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        laikai[p]+=time_span.count();
	
}


void mergeSort(int &l, double laikai[], int p)
{
	compute::device device = compute::system::default_device();
        

	using boost::compute::int_;

    	compute::greater<int_> greater;
	compute::less<int_> less;

    vector<int> host_vector(10*l);
	//cout << host_vector.size() << endl;
    generate(host_vector.begin(), host_vector.end(), rand);

    compute::vector<int> device_vector(host_vector.size(), compute::system::default_context());
      compute::copy(
        host_vector.begin(), host_vector.end(), device_vector.begin(), compute::system::default_queue()
    );

	compute::system::default_queue().finish();

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	compute::detail::merge_sort_on_gpu(
        device_vector.begin(), device_vector.end(), greater, compute::system::default_queue()
);
	compute::system::default_queue().finish();

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	laikai[p]+=time_span.count();


}
void sortSort(int &l, double laikai[], int p)
{
        compute::device device = compute::system::default_device();
        using boost::compute::int_;

        compute::greater<int_> greater;
        compute::less<int_> less;

    vector<int> host_vector(10*l);
        //cout << host_vector.size() << endl;
    generate(host_vector.begin(), host_vector.end(), rand);

    compute::vector<int> device_vector(host_vector.size(), compute::system::default_context());
      compute::copy(
        host_vector.begin(), host_vector.end(), device_vector.begin(), compute::system::default_queue()

    );

	compute::system::default_queue().finish();

        high_resolution_clock::time_point t1 = high_resolution_clock::now();
	compute::sort(device_vector.begin(), device_vector.end(), compute::system::default_queue()
);
	compute::system::default_queue().finish();

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        laikai[p]+=time_span.count();
}
void stableSortByKey(int &l, double laikai[], int p)
{
        compute::device device = compute::system::default_device();
        using boost::compute::int_;

        compute::greater<int_> greater;
        compute::less<int_> less;

    vector<int> host_vector(10*l);
	vector<int>host_key_vector(10*l);
        //cout << host_vector.size() << endl;
    generate(host_vector.begin(), host_vector.end(), rand);
	generate(host_key_vector.begin(), host_key_vector.end(), rand);
	    compute::vector<int> device_vector(host_vector.size(),  compute::system::default_context());
	compute::vector<int>device_key_vector(host_key_vector.size(),  compute::system::default_context());
      compute::copy(
        host_vector.begin(), host_vector.end(), device_vector.begin(), compute::system::default_queue()
    );

        compute::system::default_queue().finish();

compute::copy(
        host_key_vector.begin(), host_key_vector.end(), device_key_vector.begin(), compute::system::default_queue()
    );
	compute::system::default_queue().finish();


        high_resolution_clock::time_point t1 = high_resolution_clock::now();
	compute::stable_sort_by_key(device_key_vector.begin(), device_key_vector.end(), device_vector.begin(), compute::system::default_queue());
         compute::system::default_queue().finish();

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        laikai[p]+=time_span.count();
}

void sortSortByKey(int &l, double laikai[], int p)
{
        compute::device device = compute::system::default_device();
        using boost::compute::int_;

        compute::greater<int_> greater;
        compute::less<int_> less;

    vector<int> host_vector(10*l);
        vector<int>host_key_vector(10*l);
        //cout << host_vector.size() << endl;
    generate(host_vector.begin(), host_vector.end(), rand);
        generate(host_key_vector.begin(), host_key_vector.end(), rand);
            compute::vector<int> device_vector(host_vector.size(), compute::system::default_context());
        compute::vector<int>device_key_vector(host_key_vector.size(), compute::system::default_context());
      compute::copy(
        host_vector.begin(), host_vector.end(), device_vector.begin(), compute::system::default_queue()

    );

        compute::system::default_queue().finish();

compute::copy(
        host_key_vector.begin(), host_key_vector.end(), device_key_vector.begin(), compute::system::default_queue()

    );
       compute::system::default_queue().finish();

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
        compute::sort_by_key(device_key_vector.begin(), device_key_vector.end(), device_vector.begin(), compute::system::default_queue()
);
        compute::system::default_queue().finish();

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        laikai[p]+=time_span.count();
}
void radixSortByKey(int &l, double laikai[], int p)
{
        compute::device device = compute::system::default_device();
        using boost::compute::int_;

        compute::greater<int_> greater;
        compute::less<int_> less;

    vector<int> host_vector(10*l);
        vector<int>host_key_vector(10*l);
        //cout << host_vector.size() << endl;
    generate(host_vector.begin(), host_vector.end(), rand);
        generate(host_key_vector.begin(), host_key_vector.end(), rand);
            compute::vector<int> device_vector(host_vector.size(), compute::system::default_context());
        compute::vector<int>device_key_vector(host_key_vector.size(), compute::system::default_context());
      compute::copy(
        host_vector.begin(), host_vector.end(), device_vector.begin(), compute::system::default_queue()
    );

        compute::system::default_queue().finish();

compute::copy(
        host_key_vector.begin(), host_key_vector.end(), device_key_vector.begin(), compute::system::default_queue()
    );
        compute::system::default_queue().finish();

        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        compute::detail::radix_sort_by_key(device_key_vector.begin(), device_key_vector.end(), device_vector.begin(),compute::system::default_queue());
        compute::system::default_queue().finish();

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        laikai[p]+=time_span.count();
}

void radixSort(int &l, double laikai[], int p)
{
//	cout << "hi " << endl;
	compute::device device = compute::system::default_device();
  //      cout << "hi " << endl;
	
        using boost::compute::int_;
    vector<int> host_vector(10*l);

    generate(host_vector.begin(), host_vector.end(), rand);

    compute::vector<int> device_vector(host_vector.size(), compute::system::default_context());
      compute::copy(
        host_vector.begin(), host_vector.end(), device_vector.begin(), compute::system::default_queue()
    );

	compute::system::default_queue().finish();
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
	compute::detail::radix_sort(device_vector.begin(), device_vector.end(), compute::system::default_queue());
       compute::system::default_queue().finish();
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        laikai[p]+=time_span.count();
}





int main()
{
	
	int l=10;
//vector<int> host_vector(10);
	compute::device device = compute::system::default_device();
	cout << device.name() << endl;
	double timers[6]={0};
	for(int g=0;g<1000;g++){
	for(int p=0;p<6;p++)

		{
		//mergeSort(l, timers, p);
		//radixSort(l, timers, p);
		//stableSort(l, timers, p);
		//stableSortByKey(l, timers, p);
		//sortSort(l, timers,p);
		sortSortByKey(l, timers, p);
		//radixSortByKey(l, timers, p);
		l*=10;
		}
	
	l=10;		
	}


	cout <<"sort_by_key " << " " <<" laikas" << endl;
	for(int i=0;i<6;i++){
	cout  << l*10 <<" " << timers[i]/1000 << endl;
	l*=10;
	}



    return 0;
}
