class Node
{
    std::shared_ptr<Node> left, right;
    std::week_ptr<Node> parent;
    
    std::shared_ptr<Node> func()
    {
        auto par = parent.lock();
    };
};