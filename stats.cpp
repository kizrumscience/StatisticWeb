#include "stats.h"

#include <string>
#include <algorithm>

using namespace std;

string_view Find(string_view& line) {
	size_t first_space = line.find_first_not_of(' ');
	line.remove_prefix(first_space);
	size_t space = line.find(' ');
	string_view result = line.substr(0, space);
	if (space != line.npos) {
		line.remove_prefix(space + 1);
	}
	return result;
}

HttpRequest ParseRequest(string_view line) {
	return { Find(line), Find(line), Find(line) };
}

void Stats::AddMethod(string_view method) {
	auto it = methods_stats.find(method);
	if (it == methods_stats.end()) {
		it = methods_stats.find("UNKNOWN");
	}
	++methods_stats[it->first];
}

void Stats::AddUri(string_view method) {
	auto it = uri_stats.find(method);
	if (it == uri_stats.end()) {
		it = uri_stats.find("unknown");
	}
	++uri_stats[it->first];
}

const map<string_view, int>& Stats::GetMethodStats() const {
	return methods_stats;
}

const map<string_view, int>& Stats::GetUriStats() const {
	return uri_stats;
}