#include "network.h"
#include "random.h"

#include <algorithm> 



void Network::resize(const size_t& n) { 
	
	values.clear();
	 
	for (unsigned int i(0); i<n; ++i)  { 
		values.push_back(RNG.normal(0,1));
	}
}

bool Network::add_link(const size_t& a, const size_t& b) {
	
	if ((a>=values.size()) or (b>=values.size()) or (a==b)) { return false; }
	
	
	for (std::multimap<size_t,size_t>::const_iterator i=links.begin(); i!=links.end(); ++i) {
		if ((i->first==a && i->second==b) or (i->first==b && i->second==a)) {	
			return false;
		}
	}
	
	links.insert(std::pair<size_t,size_t>(a,b));
	links.insert(std::pair<size_t,size_t>(b,a));
	
	return true;
}

size_t Network::random_connect(const double& mean_deg) { 

links.clear();
int count(0);

for (size_t n(0); n < values.size(); ++n) {
			
			size_t numbertargets = RNG.poisson(mean_deg);   
			
			std::vector<int> nodes(numbertargets);
			
			RNG.uniform_int(nodes,0,values.size());
			
			for (size_t i(0); i < nodes.size(); ++i) {
					
					if (add_link(n,nodes[i])) { ++count; }
				}
			}
			
	return count;
}

size_t Network::set_values(const std::vector<double>& newvalues) {
	
	int count(0);

	if (newvalues.size() > values.size()) {
		for (unsigned int i(0); i < values.size(); ++i)  {
			values[i]=newvalues[i];
			++ count;
		}
	}	
	
	if (newvalues.size() <= values.size()) {
		for (unsigned int i(0); i < newvalues.size(); ++i)  {
			values[i]=newvalues[i];
			++ count;
		}	
	}
	return count;
}

size_t Network::size() const {
	return values.size();
}

size_t Network::degree(const size_t &_n) const {
	size_t degree = links.count(_n);
	return degree;
}


double Network::value(const size_t &_n) const {
	
	if(_n<=values.size()) {
		return values[_n];
	}
	else { return 0; }
}

std::vector<size_t> Network::neighbors(const size_t& n) const {
		
		std::vector<size_t> neighbors;
		
		for (std::multimap<size_t,size_t>::const_iterator i=links.begin(); i!=links.end(); ++i) {
			if (i->first==n) { neighbors.push_back(i->second); }
		}
		return neighbors;
}

std::vector<double> Network::sorted_values() const {
	
	std::vector<double> sorted;
	
	for (size_t i(0); i<values.size(); ++i) {
		sorted.push_back(values[i]);
	}
	
	std::sort(sorted.begin(),sorted.end());
	std::reverse(sorted.begin(),sorted.end());
	
	return sorted;
}

