#include <iostream>
#include <vector>

template<typename Iter>
void quickSort(std::vector<typename Iter::value_type>& vec, Iter left, 
    Iter right) {

    auto size = std::distance(left, right);
    if (size <= 1) {
        return;
    }
    auto pivot = std::next(right, -1);
    if (size == 2 && *pivot < *left) {
        std::iter_swap(left, pivot);
    }
    auto wall = left;
    auto curr = left;

    while (curr != right) {
        if (*curr < *pivot) {
            std::iter_swap(wall, curr);
            wall++;
        }
        curr++;
    }

    std::iter_swap(pivot, wall);
    quickSort(vec, left, wall);
    quickSort(vec, wall + 1, right);

}

int main() {
    std::vector<int> myVec = { 6, 5, 2, 3, 2, 4, 34, 2434, 251, 4, 12, 4, 5,
    634, 523, 5, 4, 353, 3, 5, 345, 7, 86786, 8, 7, 9, 1 };
    quickSort(myVec, myVec.begin(), myVec.end());
    for (auto i = myVec.begin() ; i!= myVec.end(); i++) {std::cout << *i << " ";}
    return 0;
}