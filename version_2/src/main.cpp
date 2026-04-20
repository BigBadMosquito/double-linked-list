#include "data_serializer.h"

#include <chrono>

using namespace std;

void ClearList(ListNode *head)
{
    ListNode *current = head;
    while (current)
    {
        ListNode *next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
}

int main(int argc, const char **argv)
{
    if (argc != 3)
    {
        cerr << "Usage: "s << argv[0] << " <in file> <out file>"s << endl;
        return 1;
    }

    DataSerializer data_serializer;

    ListNode *head = new ListNode();

    try
    {
        data_serializer.read(argv[1]);

        cout << "=== ДЕСЕРИАЛИЗАЦИЯ из inlet.in ===" << endl;
        {
            auto start = std::chrono::high_resolution_clock::now();

            data_serializer.deserializeAndLoadList(head);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
        }

        std::string out_file = argv[2];
        cout << "\n=== СЕРИАЛИЗАЦИЯ " << out_file << "===" << endl;

        {
            auto start = std::chrono::high_resolution_clock::now();

            data_serializer.serialize(out_file);

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
        }

        ClearList(head);
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        ClearList(head);

        return EXIT_FAILURE;
    }

    return 0;
}

/*

        data_serializer.read(argv[1]);
        data_serializer.deserializeAndLoadList(head);

        cout << "\n=== ДЕСЕРИАЛИЗАЦИЯ " << argv[1] << "===" << endl;

*/
