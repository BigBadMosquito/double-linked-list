#include "data_serializer.h"

DataSerializer::DataSerializer() {};

DataSerializer::~DataSerializer()
{
    clearHead();
    clearReaded();
}

void DataSerializer::read(const std::string &filename)
{
    std::ifstream file(filename, std::ios::in);
    if (!file.is_open())
    {
        throw std::runtime_error("Error: Cannot open file " + filename);
    }

    clearReaded();

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

        readed_data_.push_back({data, rand_index});
    }
}
/**
 * @brief Заполняет переданный список данными из прочитанного файла
 * @param head Указатель на головной узел списка (владение остается у вызывающего кода)
 * @note Создаваемые узлы будут удалены при удалении head вызывающим кодом
 */
void DataSerializer::deserializeAndLoadList(ListNode *head)
{
    if (!head)
        throw std::invalid_argument("Couldn't load List!");

    clearHead();
    head_ = head;

    int current_index = 0;
    // 1) заполняем лист от начала до конца
    for (const auto &line : readed_data_)
    {
        ListNode *new_node = new ListNode{tail_, nullptr, nullptr, line.data};
        if (tail_)
        {
            tail_->next = new_node;
        }
        else
        {
            head->next = new_node;
        }

        tail_ = new_node;
        if (line.rand_index != -1)
            pending_rands_[line.rand_index].push_front(new_node);

        node_to_index_[new_node] = current_index;

        current_index++;
    }

    current_index = 0;
    auto current_node = head->next;
    // 2) раскидываем rand по списку
    while (current_node)
    {
        if (pending_rands_.find(current_index) != pending_rands_.end())
        {
            for (auto node : pending_rands_[current_index])
            {
                node->rand = current_node;
            }
        }

        current_node = current_node->next;
        current_index++;
    }
}

/**
 * @brief Заполняет файл по данным и последнему загруженному списку
 * @param head Хранится для дальнейшей многократной сериализации в файлы
 */
void DataSerializer::serialize(const std::string &filename) const
{
    if (!head_ || !head_->next)
    {
        throw std::runtime_error("Nothing to serialize - list is empty");
    }

    std::ofstream file(filename, std::ios::out | std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Error: Cannot create file " + filename);
    }

    auto current = head_->next;
    while (current)
    {
        int rand_index = -1;
        if (current->rand)
        {
            rand_index = getIndex(current->rand);
        }

        file << current->data << ";" << rand_index << "\n";
        current = current->next;
    }
}

int DataSerializer::getIndex(ListNode *node) const
{
    auto it = node_to_index_.find(node);
    if (it != node_to_index_.end())
    {
        return it->second;
    }
    return -1;
}

void DataSerializer::clearHead() noexcept
{
    head_ = nullptr;
    tail_ = nullptr;
}

void DataSerializer::clearReaded() noexcept
{
    readed_data_.clear();
    node_to_index_.clear();
    pending_rands_.clear();
}