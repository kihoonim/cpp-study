#include <algorithm>

template<typename Seq>
void make_unique_sequence(Seq& seq)
{
    using std::begin;
    using std::end;
    using std::distance;

    std::sort(begin(seq), end(seq));
    auto it = std::unique(begin(seq), end(seq));
    seq.resize(distance(begin(seq), it));
}

int main()
{

}