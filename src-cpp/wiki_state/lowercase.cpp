#include "lowercase.hpp"
#include "context.hpp"
#include "multiupper.hpp"

#include <iostream>
#include <string>
using namespace std;

#include <boost/algorithm/string.hpp>
using namespace boost;

void lowercase_t::write(context_t& context, const string& name) {
	cout << to_lower_copy(name) << endl;
	context.set(new multiupper_t());
}
