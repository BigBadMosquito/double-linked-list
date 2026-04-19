#include "linked_list_wish_rand.h"

    void LinkedListWithRand::deserialize(const std::string &filename)
    {
        std::ifstream file(filename, std::ios::in | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("Error: Cannot open file " + filename);
        }

        clear();

        std::string line;
        while (getline(file, line))
        {
            auto pos_separator = line.find(';');

            if (pos_separator == std::string::npos)
                throw std::invalid_argument("Couldn't convert: [" + std::string(line) + "]");

            std::string data = line.substr(0, pos_separator);
            std::string index = line.substr(pos_separator + 1);

            int rand_index{0};
            auto result = std::from_chars(index.data(), index.data() + index.size(), rand_index);
            if (result.ec != std::errc())
                throw std::invalid_argument("Couldn't convert: [" + line + "]");

            push_back(data);

            resolver.registerNode(tail_, rand_index);
        }

        if (resolver.getPendingCount() > 0)
        {
            std::cerr << "Warning: " << resolver.getPendingCount()
                      << " unresolved rand references" << std::endl;
        }
    }

    void LinkedListWithRand::serialize(const std::string &filename) const
    {
        std::ofstream file(filename, std::ios::out | std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("Error: Cannot create file " + filename);
        }

        auto current = head_;
        while (current)
        {
            int rand_index = -1;
            if (current->rand)
            {
                rand_index = resolver.getIndex(current->rand);
            }

            file << current->data << ";" << rand_index << "\n";
            current = current->next;
        }
    }

    void LinkedListWithRand::clear() noexcept
    {
        clearImpl();
        resolver.clear();
    }