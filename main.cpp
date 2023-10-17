#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

/*bool compare(int x, int y){
    return !(x % 2 == 0 && x < y);
}*/

void mass(std::string input_filename){
    std::ifstream file(input_filename);
    if(!file){
        std::cout << "Error opening file" << std::endl;
        return;
    }
    int n, a, b;
    file >> n;
    file >> a;
    file >> b;
    std::vector<int> v(n);
    for(int i = 0; i < n; i++){
        file >> v[i];
    }
    file.close();

    std::cout << "Present vector: " << std::endl;
    std::copy(v.begin(), v.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    auto it = std::remove_if(v.begin(), v.end(),
                             [&](int x){return x >= a && x <= b;});
    v.erase(it, v.end());
    printf("Massive without [%i, %i]:\n", a, b);
    std::copy(v.begin(), v.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    auto max = std::max_element(v.begin(), v.end());
    auto max_even = std::find_if(max, v.end(),
                                 [](int x){return x % 2 == 0;});
    v.erase(max_even);
    std::cout << "Massive after delete of element:" << std::endl;
    std::copy(v.begin(), v.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "Position of excluded element: " << std::distance(v.begin(), max_even) << std::endl;
    std::cout << "Excluded element: " << *max_even << std::endl;

    std::cout << "Count of positive numbers: ";
    std::cout << std::count_if(v.begin(), v.end(),
                               [](int x){return x > 0;}) << std::endl;
    std::cout << "Count of negative numbers: ";
    std::cout << std::count_if(v.begin(), v.end(),
                               [](int x){return x < 0;}) << std::endl;
}

int main(int argc, char **argv) {
    if(argc != 2){
        std::cout << "Incorrect count of arguments" << std::endl;
        return -1;
    }
    mass(argv[1]);
    return 0;
}
