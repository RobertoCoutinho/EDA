enum EntryType
{
    ACTIVE,
    EMPTY,
    DELETED
};
template <typename tkey, typename tvalue>
class Node
{
public:
    tkey key;
    tvalue value;
    EntryType status;
    Node()
    {
        status = EMPTY;
    }
};