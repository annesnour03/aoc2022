#include "../helper.h"

class TreeNode {
   public:
    unsigned size = 0;
    std::string name;
    bool is_dir;
    TreeNode* parent;
    std::vector<TreeNode*> children;
    TreeNode(std::string name, int size, bool is_dir) {
        this->name = name;
        this->size = size;
        this->is_dir = is_dir;
    }
    bool add_child(TreeNode* node) {
        if (!node)
            return false;
        this->children.push_back(node);
        node->parent = this;
        return true;
    }
    bool has_children() {
        return this->children.size() > 0;
    }

    TreeNode* find_child(std::string name) {
        for (auto child : this->children) {
            if (name == child->name)
                return child;
        }
        cout << "NO CHILD FOUND FOR " << name << endl;
        return nullptr;
    }
};
class Tree {
   public:
    TreeNode* root;
    Tree() {
        this->root = nullptr;
    }
    ~Tree() {
        destroy_tree(root);
    }
    void destroy_tree(TreeNode* node) {
        for (TreeNode* child : node->children) {
            destroy_tree(child);
        }
        delete node;
    }

    bool is_empty() {
        return root == nullptr;
    }
    void print_tree() {
        print_tree(this->root);
    }
    void print_tree(TreeNode* node) {
        cout << node->name << " " << node->size << endl;
        for (auto child : node->children) {
            print_tree(child);
            cout << endl;
        }
    }
};
int get_nested_size(TreeNode* node) {
    unsigned sum = 0;
    if (!node->has_children())
        return node->size;
    for (auto child : node->children) {
        sum += get_nested_size(child);
    }
    return sum;
}
int res = 0;
void solve(TreeNode* t, std::vector<unsigned>& out) {
    for (auto child : t->children) {
        solve(child, out);
        int size = get_nested_size(child);
        if (child->is_dir) {
            res += size;
            out.push_back(size);
        }
    }
}
int main(int argc, char* argv[]) {
    std::string input = "input.sample";
    if (argc > 1) {
        input = argv[1];
    }
    std::fstream file(input);
    std::string line;
    std::vector<std::string> parsed_data;
    Tree* main = new Tree;
    TreeNode* root = new TreeNode("/", 0, true);
    main->root = root;
    TreeNode* current = root;
    int i = 0;
    while (std::getline(file, line)) {
        if (!i++)
            continue;
        if (line == "$ ls")
            continue;
        std::string dirname;
        if (line == "$ cd ..") {
            current = current->parent;
            continue;
        }
        if (line[0] == '$') {
            dirname = split(line, ' ')[2];
            current = current->find_child(dirname);
            continue;
        }

        // add children
        std::string type = split(line, ' ')[0];
        std::string entry_name = split(line, ' ')[1];
        unsigned size = 0;
        std::string dir = "dir";
        bool is_dir = true;
        if (type != dir) {
            is_dir = false;
            size = std::stoi(split(line, ' ')[0]);
        }
        TreeNode* n = new TreeNode(entry_name, size, is_dir);
        current->add_child(n);
    }
    const int used_space = get_nested_size(main->root);
    const int unused_space = 70000000 - used_space;
    const int needed_to_delete = 30000000 - unused_space;
    std::vector<unsigned> out;

    solve(main->root, out);
    std::sort(out.begin(), out.end());
    auto a = std::lower_bound(out.begin(), out.end(), needed_to_delete);
    cout << *a << endl;
    delete main;

    return 0;
}