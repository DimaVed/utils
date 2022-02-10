#pragma once
#include "range.h"
#include <unordered_set>

template <typename It>
size_t ComputeUniqueItemsCount(Range<It> range) {
  return std::unordered_set<typename Range<It>::ValueType>{
      range.begin(), range.end()
  }.size();
}


//std::algorithm style split alogrithm
template <typename InIt, typename OutIt, typename T, typename F>
InIt split(InIt it, InIt end_it, OutIt out_it, T split_val, F bin_func)
{
while (it != end_it) {
auto slice_end (find(it, end_it, split_val));
*out_it++ = bin_func(it, slice_end);
if (slice_end == end_it) { return end_it; }
it = next(slice_end);
}
return it;
}

// example split algo
/*int main()
{
const string s {"a-b-c-d-e-f-g"};
auto binfunc ([](auto it_a, auto it_b) {
return string(it_a, it_b);
});
list<string> l;
split(begin(s), end(s), back_inserter(l), '-', binfunc);
copy(begin(l), end(l), ostream_iterator<string>{cout, "\n"});
return 0;
}*/

/
template <typename T>
class Paginator {


public:
	Paginator(T begin, T end, size_t page_size) {
		for (size_t left = distance(begin, end); left > 0; ) {
			size_t current_page_size = (std::min)(page_size, left);
			T current_page_end = next(begin, current_page_size);
			pages.push_back({ begin, current_page_end });

			left -= current_page_size;
			begin = current_page_end;
		}
	}

	auto begin() const {
		return pages.begin();
	}

	auto end() const {
		return pages.end();
	}

	size_t size() const {
		return pages.size();
	}
private:
	std::vector<IteratorRange<T>> pages;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator(begin(c), end(c), page_size);
}