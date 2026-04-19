#include "linked_list_wish_rand.h"

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
    list_with_rand.deserialize(argv[1]);

    std::string out_file = argv[2];
    cout << "\n=== СЕРИАЛИЗАЦИЯ " << out_file << "===" << endl;
    list_with_rand.serialize(out_file);

    cout << "\n=== Проверка: читаем outlet.out ===" << endl;
    ifstream check(out_file);
    string line;
    while (getline(check, line))
    {
        cout << line << endl;
    }
}