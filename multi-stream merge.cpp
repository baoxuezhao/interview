#include <cstdio>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
using namespace std;

template<typename T>
class Iterator {
public:
    virtual bool HasNext() = 0;
    virtual T Next() = 0;
};

//for test
template<typename T>
class Stream : private Iterator<T> {
public:
    Stream(vector<T> _data) {data = _data; index = 0;}
    bool HasNext() {return index < data.size();}
    T Next() {return data[index++];}
    
private:
    vector<T> data;
    int index;
};

struct MyComparator{
    bool operator()(int x, int y) {
        return x > y;
    }
};

template<typename T, typename Comparator>
class MergeSort : private Iterator<T> {
public:
    MergeSort(vector< Stream<T> > _head) {
        head = _head;
        for (int i = 0; i < head.size(); i++) {
            if (head[i].HasNext())
                pq.push(make_pair(head[i].Next(), i));
        }
    }
    
    bool HasNext() {
        return !pq.empty();
    }
    
    T Next() {
        if (!HasNext()) return T();
        pair<T, int> cur = pq.top();
        pq.pop();
        T ret = cur.first;
        if (head[cur.second].HasNext())
            pq.push(make_pair(head[cur.second].Next(), cur.second));
        return ret;
    }
    
private:
    struct InnerCompare {
        bool operator() (const pair<T, int> &lhs, const pair<T, int> &rhs) {
            return Comparator()(lhs.first, rhs.first);
        }
    };
    priority_queue< pair<T, int> , vector<pair<T, int> >, InnerCompare> pq;
    vector< Stream<T> > head;
};

//int main() {
//    Stream<int> s1({20,50,100});
//    Stream<int> s2({10,30,60});
//    Stream<int> s3({10,20,20,20,30,200});
//    Stream<int> s4({70,80,80,90,100});
//    Stream<int> s5({});
//    Stream<int> s6({0});
//    MergeSort<int, MyComparator> ms({s1, s2, s3, s4, s5, s6});
//    while (ms.HasNext()) {
//        int val = ms.Next();
//        printf("%d ", val);
//    }
//    printf("\n");
//    return 0;
//}
