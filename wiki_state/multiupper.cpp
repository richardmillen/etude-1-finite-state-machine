#include "multiupper.hpp"
#include "state.hpp"
#include "context.hpp"
#include "lowercase.hpp"

#include <iostream>
#include <string>
using namespace std;

#include <boost/algorithm/string.hpp>
using namespace boost::algorithm;

void multiupper_t::write(context_t& context, const string& name) {
	cout << to_upper_copy(name) << endl;
	if (++count_ > 1) {
		context.set(new lowercase_t());
	}
}
