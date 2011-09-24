#define BOOST_ALL_DYN_LINK
#define BOOST_TEST_MODULE workers_rest_module

#include <boost/test/unit_test.hpp>

#include "worker.h"
#include "master.h"

BOOST_AUTO_TEST_CASE(workers_test_base_class) {
    /*
    Check that the base class is functioning properly
    If this fails the problem is in the base class not the inherited one
    */
    Worker test;
    test.work();
    BOOST_CHECK_EQUAL(test.get_result(), (void*)0);
    test.start_worker((void*)1);
    BOOST_CHECK_EQUAL(test.get_result(), (void*)1);
}

class testWorker: public Worker
{
public:
    void work();
private:
    std::string hello;
};

void testWorker::work() {
    hello = "Hello World.";
    this->result = (void*)&hello;
    this->finished = true;
}

BOOST_AUTO_TEST_CASE(workers_test_inherited_class) {
    /*
    Test a very simple inherited class. 
    */
    testWorker test;
    std::string expected = "Hello World.";
    std::string* result = NULL;
    test.work();
    result = (std::string*)test.get_result();
    BOOST_CHECK_EQUAL(result->c_str(), "Hello World.");
    
    result = NULL;
    test.start_worker((void*)1);
    result = (std::string*)test.get_result();
    BOOST_CHECK_EQUAL(result->c_str(), "Hello World.");
}
