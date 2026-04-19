#include "linked_list_wish_rand.h"

#include <chrono>

using namespace std;

int main(int argc, const char **argv)
{
    if (argc != 3)
    {
        cerr << "Usage: "s << argv[0] << " <in file> <out file>"s << endl;
        return 1;
    }

    LinkedListWithRand list_with_rand;
    cout << "=== ДЕСЕРИАЛИЗАЦИЯ из inlet.in ===" << endl;
    {
        auto start = std::chrono::high_resolution_clock::now();

        list_with_rand.deserialize(argv[1]);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
    }

    std::string out_file = argv[2];
    cout << "\n=== СЕРИАЛИЗАЦИЯ " << out_file << "===" << endl;

    {
        auto start = std::chrono::high_resolution_clock::now();

        list_with_rand.serialize(out_file);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
    }

    return 0;
}