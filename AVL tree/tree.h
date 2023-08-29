#include <iostream>
#include <fstream>
using namespace std;

class element_not_found : public exception { };
class bad_parameters_given : public exception { };
class critical_exception : public exception { };

template <typename Key, typename Info>
class Dictionary { //AVL Tree
private:
	struct Node{
		Key key;
		Info info;
		int height;
		Node* left;
		Node* right;

		Node(const Key& k, const Info& i) : key(k), info(i), height(1)
		{
			left = nullptr;
			right = nullptr;
		}
	}*root;

	friend void RetrieveWords(Dictionary<int, string> n, const string& filename);
	int size = 0;

	Node* copy_nodes(Node* src){ //copying node to another
		if (!src) return nullptr;
		Node* n = new Node(src->key, src->info);
		n->left = copy_nodes(src->left);
		n->right = copy_nodes(src->right);

		size++;
		height_repair(n);

		return n;
	}

	int height(Node* n) const{ //returning height of the tree
		if (n) return n->height;
		else return 0;
	}

	// balance factor for non-nullptrs
	int balance_factor_calculator(Node* n) { return height(n->right) - height(n->left); }

	Node* perform_balance(Node* n){
		if (!n) throw critical_exception();
		height_repair(n);

		if (balance_factor_calculator(n) == 2){
			if (balance_factor_calculator(n->right) < 0) n->right = rotate_right(n->right);
			return rotate_left(n);
		}

		if (balance_factor_calculator(n) == -2){
			if (balance_factor_calculator(n->left) > 0) n->left = rotate_left(n->left);
			return rotate_right(n);
		}

		return n; // no balancing needed
	}

	// rotating tree node
	Node* rotate_right(Node* n){
		if (n) return rotator(n, 'r');
		else throw critical_exception();
	}

	Node* rotate_left(Node* n){
		if (n) return rotator(n, 'l');
		else throw critical_exception();
	}

	Node* rotator(Node* n, char rotate){
		Node* x;
		if (rotate == 'r'){
			x = n->left;
			n->left = x->right;
			x->right = n;
		}
		else if (rotate == 'l'){
			x = n->right;
			n->right = x->left;
			x->left = n;
		}
		else throw bad_parameters_given();

		height_repair(n);
		height_repair(x);

		return x;
	}

	// repairs height of node, assuming left and right heights to be correct
	void height_repair(Node* n){
		int height_left = height(n->left);
		int height_right = height(n->right);

		if (height_left > height_right){
			 n->height = 1 + height_left;
		}
		else if (height_left < height_right){
			n->height = 1 + height_right;
		}
	}

	void cleanup(Node* n){
		if (n){
			cleanup(n->left);
			cleanup(n->right);
			delete n;
			size = 0;
		}
	}

	Node* exists(Node* n, const Key& k) const{ // checking for existance of node with such a key
		if (!n) { throw critical_exception(); }

		if (n->key == k) { return n; }

		if (n->key < k) { return exists(n->right, k); }
		else if (n->key > k) { return exists(n->left, k); }
		else throw element_not_found();
	}
	Node* remove(Node* n, const Key& k){ //removing node from tree
		if (!n) throw critical_exception();

		if (k < n->key) n->left = remove(n->left, k);
		else if (k > n->key) n->right = remove(n->right, k);
		else{ // key is found
			Node* ln = n->left;
			Node* rn = n->right;
			delete n;

			if (!rn) return ln;

			Node* min = find_min(rn);
			min->right = remove_min(rn);
			min->left = ln;
			size--;
			return perform_balance(min);
		}
		return perform_balance(n);
	}

	Node* find_min(Node* n) { return n->left ? find_min(n->left) : n; }

	Node* remove_min(Node* n){
		if (n->left == 0) return n->right;

		n->left = remove_min(n->left);

		return perform_balance(n);
	}
	//inserting node into tree
	Node* insert(Node* n, const Key& k, const Info& i){ 
		if (!n){
			size++;
			return new Node(k, i);
		}
		if (k < n->key) n->left = insert(n->left, k, i);
		else if (k > n->key) n->right = insert(n->right, k, i);
		else {
			n->info = i;
			return n;
		}
			return perform_balance(n);
	}
	Node* insertWord(Node* n, const Key& k, const Info& i){
		if (!n){
			size++;
			return new Node(k, i);
		}
		if (i < n->info) n->left = insertWord(n->left, k, i);
		else if (i > n->info) n->right = insertWord(n->right, k, i);
			else {
				n->key = n->key +1;
				return n;
			}
			return perform_balance(n);
	}
	//printing or drawing node
	void print_in_order(ostream& output) const{
		print_in_order(output, root);
	}
	void print_in_order(ostream& out, Node* n) const{
		if (!n) return;
		print_in_order(out, n->left);
		cout << "[" << n->key << "|" << n->info << "]  ";
		print_in_order(out, n->right);
	}
	void print_in_order(Node* n) const{
		if (!n) return;
		print_in_order(n->left);
		cout << "[" << n->key << "|" << n->info << "]  ";
		print_in_order(n->right);
	}
	void draw(Node* n, int step = 0, string mark = "T ") const{
		if (!n){
			cout << indent(step) << "X";
			return;
		}

		draw(n->right, step + 8, "{r} ");
		cout << endl;

		cout << indent(step) << mark << "k: " << n->key << " i: " << n->info << endl;

		draw(n->left, step + 8, "{l} ");

		cout << endl << indent(step);
	}

	string indent(int indent) const{
		string out;
		for (auto i = 0; i < indent; i++) out += "  ";
		return out;
	}

public:
	Dictionary() { root = nullptr; }
	Dictionary(const Dictionary& src) { root = copy_nodes(src.root); }
	~Dictionary() { cleanup(root); }

	//different operators
	Dictionary& operator =(Dictionary const& src){
		//if (*this == &src) return *this;

		cleanup(root);
		root = copy_nodes(src.root);
		return *this;
	}

	friend ostream& operator<<(ostream& output, const Dictionary<Key, Info>& src){
		src.print_in_order(output, src.root);
		return output;
	}

	const Info& operator[](const Key& k) const{
		Node* index = nullptr;
		try { index = exists(root, k); }
		catch (element_not_found){
			throw element_not_found();
		}// if not found 
		catch (critical_exception){
			throw critical_exception();
		}// if not found
		catch (...){
			cerr << "Reached uncontrolled path!" << endl;
		}
		return index->info;
	}

	void insertWord(const Key& k, const Info& i) { root = insertWord(root, k, i); }
	void insert(const Key& k, const Info& i) { root = insert(root, k, i); }

	void remove(const Key& k){
		try { root = remove(root, k); }
		catch (element_not_found) { throw element_not_found(); }
	}

	bool exists(const Key& k) const{
		try { exists(this->root, k); }
		catch (const element_not_found) { throw element_not_found(); }
		catch (const critical_exception) { throw critical_exception(); }
		catch (...) { cerr << "Reached an uncontrolled control path!" << endl; }
		return true;
	}

	void print() const{
		cout << "<-----------------------Tree Data----------------------->" << endl << endl;
		cout << "Size: " << get_size() << "\t\t Height: " << height(root) << endl;
		print_in_order(root);
		cout << endl << "---------------------------------------------------------" << endl << endl;
	}

	void draw() const
	{ if (root) draw(root); }
	int get_size() const { return size; }
};

bool inWord(string& word, ifstream& inFile){
	bool isWord(false);
    char c;
    if (inFile.is_open()){
        while (!inFile.eof()){ // first look for a word starting character
            inFile.get(c);
            if ((c>='a' && c<='z') || (c>='A' && c<='Z')){
                isWord= true;
                word= c;    // assign the word starting character
                c='\0';
                break;
            }
        }
        while (!inFile.eof()){ // then append remaining (following) characters to the word
            inFile.get(c);
            if ((c>='a' && c<='z') || (c>='A' && c<='Z')){
                word+= c;   // append the character to the word
                c='\0';
            } else {
                break;
            }
        }
    }
    return isWord;
}

template <typename Key, typename Info>
void retrieveWords(Dictionary<Key, Info> &n, const string& filename){
	ifstream inFile(filename);
    string word;
	int num =1;
    int wordCount(0);
    if (inFile.is_open()){
        cout << "Successfully opened file '" << filename << "'" << endl;
        while (inWord(word, inFile)){
            n.insertWord(num, word); //inserting word as a node into the tree
			wordCount++;
        };
        cout << endl << "wordCount (fileName[" << filename << "]()=" << wordCount << endl;
    } else {
        cout << "Can not open file '" << filename << "'" << endl;
    }
}
