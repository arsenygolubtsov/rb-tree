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
    node_t* root() const
    {
        return root_;
    }
    
    tree_t()
    {
        root_ = nullptr;
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
    
    tree_t(std::initializer_list<T> keys){
        root_=nullptr;
        int n = keys.size();
        const int* param = keys.begin();
        for (int i=0; i < n; i++){
            insert(param[i]);
        }
    }
    
    void insert(T value)
    {
        if (root_ == nullptr)
        {
            root_ = new node_t;
            root_->parent = nullptr;
            root_->value = value;
            root_->left = nullptr;
            root_->right = nullptr;
            root_->color = false;
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
                        run_->color = true;
                        run_->left = nullptr;
                        run_->right = nullptr;
                        insert_case1(run_);
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
                        run_->color = true;
                        run_->left = nullptr;
                        run_->right = nullptr;
                        insert_case1(run_);
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
    
    void rotate_left(node_t * N){
        node_t * node = N->right;
        node->parent = N->parent;
        if(N->parent != nullptr){
            if(N->parent->left == N){
                N->parent->left = node;
            }
            else N->parent->right = node;
        }
        N->right = node->left;
        if(node->left != nullptr){
            node->left->parent = N;
        }
        if(N->parent == nullptr) root_ = node;
        N->parent = node;
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
            node->right->parent = N;
        }
        if(N->parent == nullptr) root_ = node;
        N->parent = node;
        node->right = N;
    }
    
    void insert_case1(node_t * N){
        if(N->parent == nullptr) N->color = false;
        else insert_case2(N);
    }
    
    void insert_case2(node_t * N){
        if(N->parent->color == false) return;
        else insert_case3(N);
    }
    
    void insert_case3(node_t * N){
        node_t * u = uncle(N), * g;
        if(u != nullptr && u->color == true){
            N->parent->color = false;
            u->color = false;
            g = grandparent(N);
            g->color = true;
            insert_case1(g);
        }
        else insert_case4(N);
    }
    
    void insert_case4(node_t * N){
        node_t * g = grandparent(N);
        if(N == N->parent->right && N->parent == g->left){
            rotate_left(N->parent);
            N = N->left;
        }
        else if(N == N->parent->left && N->parent == g->right){
            rotate_right(N->parent);
            N = N->right;
        }
        insert_case5(N);
    }
    
    void insert_case5(node_t * N){
        node_t * g = grandparent(N);
        N->parent->color = false;
        g->color = true;
        if(N == N->parent->left && g->left == N->parent) rotate_right(g);
        else rotate_left(g);
    }
    bool remove(T value){
    if(root_ == nullptr){
        return false;
    }
    else{
        node_t* param1 = nullptr;
        node_t* param2 = root_;
        while(1){
            if(param2->value == value){
                break;
            }
            else if(value > param2->value){
                param1 = param2;
                param2 = param2->right;
            }
            else if(value < param2->value){
                param1 = param2;
                param2 = param2->left;
            }
            if(param2 == nullptr){
                return false;
            }
        }
        if(param2->left == nullptr && param2->right == nullptr){
            if(param2 == root_){
                node_t* node = root_;
                root_ = nullptr;
                delete node;
            }
            else{
                if(param1->left == param2){
                    if (param2->color == false) delete_case1(param2);
                    if(param2->parent->left == param2) param2->parent->left = nullptr;
                    else if(param2->parent->right == param2) param2->parent->right = nullptr;
                    delete param2;
                }
                if(param1->right == param2){
                    if (param2->color == false) delete_case1(param2);
                    if(param2->parent->left == param2) param2->parent->left = nullptr;
                    else if(param2->parent->right == param2) param2->parent->right = nullptr;
                    delete param2;
                }
            }
        }
        else if((param2->left != nullptr && param2->right == nullptr) || (param2->left == nullptr && param2->right != nullptr)){
            if(param2 == root_){
                node_t* node = root_;
                if(param2->left != nullptr){
                    root_ = param2->left;
                    root_->parent = nullptr;
                }
                else if(param2->right != nullptr){
                    root_ = param2->right;
                    root_->parent = nullptr;
                }
                delete node;
            }
            else{
                if(param1->left == param2){
                    if(param2->left != nullptr){
                        param1->left = param2->left;
                        param2->left->parent = param1;
                        if (param2->color == false) {
		                    if (param1->left->color == true) param1->left->color = false;
	                    	else delete_case1(param1->left);
	                    }
                        delete param2;
                    }
                    else if(param2->right != nullptr){
                        param1->left = param2->right;
                        param2->right->parent = param1;
                        if (param2->color == false) {
		                    if (param1->left->color == true) param1->left->color = false;
	                    	else delete_case1(param1->left);
	                    }
                        delete param2;
                    }
                }
                else if(param1->right == param2){
                    if(param2->left != nullptr){
                        param1->right = param2->left;
                        param2->left->parent = param1;
                        if (param2->color == false) {
		                    if (param1->right->color == true) param1->right->color = false;
	                    	else delete_case1(param1->right);
	                    }
                        delete param2;
                    }
                    else if(param2->right != nullptr){
                        param1->right = param2->right;
                        param2->right->parent = param1;
                        if (param2->color == false) {
		                    if (param1->right->color == true) param1->right->color = false;
	                    	else delete_case1(param1->right);
	                    }
                        delete param2;
                    }
                }
            }
        }
        else if(param2->left != nullptr && param2->right != nullptr){
            node_t* node = param2;
            param1 = param2;
            param2 = param2->right;
            if(param2->left == nullptr){
                if(param2->right == nullptr){
                    bool tr = node->color;
                    node->value = param2->value;
                    node->color = param2->color;
                    node->right = nullptr;
                    delete param2;
                    if(tr == false){
                        if(node->color == true) node->color = false;
                        else delete_case1(node);
                    }
                }
                else{
                    bool tr = node->color;
                    node->value = param2->value;
                    node->color = param2->color;
                    node->right = param2->right;
                    param2->right->parent = node;
                    delete param2;
                    if(tr == false){
                        if(node->color == true) node->color = false;
                        else delete_case1(node);
                    }
                }
            }
            else{
                while(param2->left != nullptr){
                    param1 = param2;
                    param2 = param2->left;
                }
                if(param2->right == nullptr){
                    bool tr = node->color;
                    node->value = param2->value;
                    node->color = param2->color;
                    param1->left = nullptr;
                    delete param2;
                    if(tr == false){
                        if(node->color == true) node->color = false;
                        else delete_case1(node);
                    }
                }
                else{
                    bool tr = node->color;
                    node->value = param2->value;
                    node->color = param2->color;
                    param1->left = param2->right;
                    param2->right->parent = param1;
                    delete param2;
                    if(tr == false){
                        if(node->color == true) node->color = false;
                        else delete_case1(node);
                    }
                }
            }
        }
        return true;
    }
}

node_t * sibling(node_t * n){
	if(n == n->parent->left) return n->parent->right;
	else return n->parent->left;
}

void delete_case1(node_t * n){
	if(n->parent != nullptr) delete_case2(n);
}

void delete_case2(node_t * n){
	node_t * s = sibling(n);
	if(s == nullptr) return;
	if(s->color == true){
		n->parent->color = true;
		s->color = false;
		if(n == n->parent->left) rotate_left(n->parent);
		else rotate_right(n->parent);
	}
	delete_case3(n);
}

void delete_case3(node_t * n){
	node_t * s = sibling(n);
	if (s->left == nullptr || s->right == nullptr) return;
	if((n->parent->color == false) && (s->color == false) && (s->left->color == false) && (s->right->color == false)){
		s->color = true;
		delete_case1(n->parent);
	}
	else delete_case4(n);
}

void delete_case4(node_t * n){
	node_t * s = sibling(n);
	if((n->parent->color == true) && (s->color == false) && (s->left->color == false) && (s->right->color == false)){
		s->color = true;
		n->parent->color = false;
	}
	else delete_case5(n);
}

void delete_case5(node_t * n){
	node_t * s = sibling(n);
	if(s->color == false){
		if((n == n->parent->left) && (s->right->color == false) && (s->left->color == true)){
			s->color = true;
			s->left->color = false;
			rotate_right(s);
		}
		else if((n == n->parent->right) && (s->left->color == false) && (s->right->color == true)){
			s->color = true;
			s->right->color = false;
			rotate_left(s);
		}
	}
	delete_case6(n);
}

void delete_case6(node_t * n){
	node_t * s = sibling(n);
	s->color = n->parent->color;
    n->parent->color = false;
	if(n == n->parent->left){
        s->right->color = false;
		rotate_left(n->parent);
	}
	else{
		s->left->color = false;
		rotate_right(n->parent);
	}
}
	
};

template <typename T>
bool read(tree_t <T> & tree, std::istream& stream)
{
    char op;
    T value;
    if (stream >> op && (op == '=' || op == '+' || op == '?' || op == 'q'))
    {
        if (op == '=')
        {
            tree.print(std::cout, tree.root(), 1);
        }
        else if (op == 'q')
        {
            return false;
        }
        else if ((op == '+' || op == '?') && stream >> value)
        {
            if (op == '+')
            {
                tree.insert(value);
            }
            else if (op == '?')
            {
                std::cout << tree.find(value) << std::endl;
            }
        }
    }
    return true;
}
