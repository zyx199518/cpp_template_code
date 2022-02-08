// 文件名：main.cpp
#include "pool_allocator.hpp"
#include "test_suite.hpp"

#include <list>
using std::list;

#ifndef DISABLE_GNU_POOL_ALLOCATOR
  #include <ext/pool_allocator.h>
  using __gnu_cxx::__pool_alloc;
  typedef list<size_t, __pool_alloc<size_t> > gnu_pool_list;
#endif

#ifndef DISABLE_BOOST_POOL_ALLOCATOR
  #include <boost/pool/pool_alloc.hpp>
  namespace b = boost;
  typedef list<size_t, b::fast_pool_allocator<size_t> > boost_pool_list;
#endif

#include <iostream>
#include <sstream>


using mylib::pool_allocator;

typedef list<size_t, pool_allocator<size_t> > pool_list;
typedef list<size_t> normal_list;

void print_test_result(test_result const &result)
{
    std::ostringstream oss_insertion, oss_deletion;
    float total = 0;
    for (test_result::const_iterator i = result.begin();
         i < result.end(); ++i) {
        oss_insertion<<'\t'<<i->first;
        oss_deletion<<'\t'<<i->second;
        total += i->first + i->second;
    }
    std::cout<<"Insertion time:"<<oss_insertion.str()<<std::endl
             <<"Deletion time :"<<oss_deletion.str()<<std::endl;
}

int main()
{
    std::cout<<"=========my pool  list========="<<std::endl;
    print_test_result(run_test_suit<pool_list>());

    std::cout<<mylib::pool_allocator_recycle()
             <<" bytes recycled."
             <<std::endl;

#ifndef DISABLE_GNU_POOL_ALLOCATOR
    std::cout<<"=========GNU pool list========="<<std::endl;
    print_test_result(run_test_suit<gnu_pool_list>());
#endif

#ifndef DISABLE_BOOST_POOL_ALLOCATOR
    std::cout<<"========boost pool list========"<<std::endl;
    print_test_result(run_test_suit<boost_pool_list>());
#endif

    std::cout<<"==========normal list=========="<<std::endl;
    print_test_result(run_test_suit<normal_list>());
}
