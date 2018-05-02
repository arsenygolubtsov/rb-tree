#include <iostream>
#include <sstream>
#include <string>

template <typename T>
class tree_t
{
private:
    struct node_t
    {
        node_t* parent;
        node_t* left;
        node_t* right;
        T value;
        bool color;
    };

private:
    node_t* root_;

public:
    tree_t()
    {
        root_ = nullptr;
    }
    
    node_t * grandparent(node_t * N){
        if(N != nullptr && N->parent != nullptr){
            return N->parent->parent;
        }
        else return nullptr;
    }
    
    node_t * uncle(node_t * N){
        node_t * g = grandparent(N);
        if(g == nullptr) return nullptr;
        if(N->parent == g->left) return g->right;
        else return g->left;
    }
    
    void insert(T value)
    {
        if (root_ == nullptr)
        {
            root_->parent = nullptr;
            root_ = new node_t;
            root_->value = value;
            root_->left = nullptr;
            root_->right = nullptr;
        }
        else
        {
            node_t* run_ = root_;
            while (run_ != nullptr)
            {
                if (value < run_->value)
                {
                    if (run_->left == nullptr)
                    {
                        run_->left = new node_t;
                        run_->left->parent = run_;
                        run_ = run_->left;
                        run_->value = value;
                        run_->left = nullptr;
                        run_->right = nullptr;
                        return;
                    }
                    else
                    {
                        run_ = run_->left;
                    }
                }
                else if (value >= run_->value)
                {
                    if (run_->right == nullptr)
                    {
                        run_->right = new node_t;
                        run_->right->parent = run_;
                        run_ = run_->right;
                        run_->value = value;
                        run_->left = nullptr;
                        run_->right = nullptr;
                        return;
                    }
                    else
                    {
                        run_ = run_->right;
                    }
                }
            }
        }
    }
    
    void rotate_left(node_t * N){
        node_t * node = N->right;
        node->parent = N->parent;
        if(N->parent != nullptr){
            if(N->parent->left = N){
                N->parent->left = node;
            }
            else N->parent->right = node;
        }
        N->right = node->left;
        if(node->left != nullptr){
            node->left->parent = n;
        }
        n->parent = node;
        node->left = N;
    }
    
    void rotate_right(node_t * N){
        node_t * node = N->left;
        node->parent = N->parent;
        if(N->parent != nullptr){
            if(N->parent->left == N){
                N->parent->left = node;
            }
            else N->parent->right = node;
        }
        N->left = node->right;
        if(node->right != nullptr){
            node->right->parent = n;
        }
        n->parent = node;
        node->right = N;
    }
    
    bool equal(node_t* a, node_t* b) const{
        if (a==nullptr && b==nullptr) return(true);
        else if (a!=nullptr && b!=nullptr)
        {
            return(
                    a->value == b->value &&
                    equal(a->left, b->left) &&
                    equal(a->right, b->right)
            );
        }
        else return(false);
    }
    
    auto operator==(tree_t const & other) const{
        node_t* a=root_; node_t* b=other.root_;
        return (equal(a, b));
    }
    
    bool find(T value) const
    {
        if (root_ == nullptr)
        {
            return false;
        }
        else
        {
            node_t* run_ = root_;
            while (run_ != nullptr)
            {
                if (run_->value == value)
                {
                    return true;
                }
                else if (run_->value < value)
                {
                    run_ = run_->right;
                }
                else if (run_->value > value)
                {
                    run_ = run_->left;
                }
            }
            return false;
        }
    }

    node_t* root() const
    {
        return root_;
    }

    ~tree_t()
    {
        if (root_ != nullptr)
        {
            del(root_);
        }
    }

    void del(node_t* run_)
    {
        if (run_ != nullptr)
        {
            if (run_->left != nullptr)
            {
                del(run_->left);
            }
            if (run_->right != nullptr)
            {
                del(run_->right);
            }
            delete run_;
        }
    }

    void print(std::ostream& stream, node_t* run_, size_t u) const
    {
        if (run_->right != nullptr)
        {
            u++;
            print(stream, run_->right, u);
            u--;
        }
        for (size_t k = 0; k < u; k++)
        {
            stream << "--";
        }
        stream << run_->value << std::endl;
        if (run_->left != nullptr)
        {
            u++;
            print(stream, run_->left, u);
            u--;
        }
    }
};
