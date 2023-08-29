#include <iostream>

using namespace std;

template <typename Key, typename Info>
class Sequence{
private:
	struct Node{
		Key key;
		Info info;
		Node* Next;
	};
	Node* Head;					//declaring class
public:
	class iterator{				//declaring iterator
		Node* Current;

		iterator(Node* Curr) : Current(Curr) {};

	public:
	    iterator() : Current(nullptr) {};

		iterator(const iterator& src) : Current(src.Current) {};

        iterator& operator ++(){			//operator++
			skip();
			return *this;
		}

		iterator& operator ++(int){
			iterator Copy = *this;
			skip();
			return Copy;
		}

		iterator operator=(const iterator& src){		// copy operator
			Current = src.Current;
			return *this;
		}

		iterator operator+(int distance){						// adding to sequence operator
				if (distance < 0){
					cerr << "iterator operator+ - distance not valid" << endl;
					return *this;
				}
				for (int i = 0; Current && Current->Next && i < distance; i++){
                     Current = Current->Next;
                }
				return *this;
		}

		bool operator ==(const iterator& src){				// logic operators
			return Current == src.Current;
		}

		bool operator !=(const iterator& src){
			return Current != src.Current;
		}

		Node& operator*() const{
			return *Current;
		}

		Node* operator->(){
			return Current;
		}


		void skip(){											// skipping one node
			Current = Current ? Current->Next : nullptr;
		}

		void skip(int i){ 									// skiping to i node
            for (int j = 0; j < i; j++) skip();
        }

		bool is_empty(){
			if (Current){ 
                return false;
            }
            else return true;
		}

		Key key(){
			return Current->key;
		}

		Info info(){
			return Current->info;
		}

		friend class Sequence;
	};

	//ITERATOR END //

	// regular_iterator //
	iterator begin(){
        return iterator(Head);
        }
	iterator end(){
         return nullptr;
         }

	// const_iterator //
	iterator const_begin() const{
        return iterator(Head);
        }
	iterator const_end(){
        return nullptr;
        }

	/* CONSTRUCTORS */
	Sequence(){
        Head = nullptr; //default
        }
	~Sequence(){
        clear_all();    // default destructor
        }
	Sequence(const Sequence<Key, Info>& src){ // copy constructor
		Head = nullptr;
        CopyAll(src);
	}

	/* OPERATORS */
	Sequence<Key, Info>& operator=(const Sequence<Key, Info>& rhs){
		this->clear_all();
		CopyAll(rhs);
		return *this;
	}

	Sequence<Key, Info>& operator+(const Sequence<Key, Info>& rhs){
		Node* Temp = rhs.Head;
		while (Temp){
			this->add_back(Temp->key, Temp->info);
			Temp = Temp->Next;
		}
		return *this;
	}

	Sequence<Key, Info>& operator+=(const Sequence<Key, Info>& rhs){
		this->CopyAll(rhs);
		return *this;
	}

	void add_front(Key NewKey, Info NewInfo){ // adds an element to the front of the list
		Node* CreateNode = new Node;
		CreateNode->key = NewKey;
		CreateNode->info = NewInfo;
		CreateNode->Next = Head;
		Head = CreateNode;
	}

	void add_front(iterator& Current){
		add_front(Current->key, Current->info);
	}

	void add_back(Key NewKey, Info NewInfo){ // adds an element to the back of the list
		Node* CreateNode = new Node;
		CreateNode->key = NewKey;
		CreateNode->info = NewInfo;
		Node* Curr = Head;

		if (!Head) add_front(NewKey, NewInfo);
		else{
			while (Curr->Next){
                Curr = Curr->Next;
            }
			Curr->Next = CreateNode;
		}
		CreateNode->Next = nullptr;
	}

	void add_back(iterator& Current){							//adding node at the end
		if (Current.Current){
			add_back(Current->key, Current->info);
        }
    }

	void add_back(iterator& Current, int Lenght){
		for (int i = 0; i < Lenght; i++){
			add_back(Current);
        }
		Current++;
	}

	void add_after(Key NewKey, Info NewInfo, const Key ExistKey){ // adds an element after first found element with Key == newkey
		Sequence<Key, Info>::iterator Iter = Head;
		while(Iter != nullptr){
			if (Iter->key == ExistKey){
				Node* CreateNode = new Node();
				CreateNode->key = NewKey;
				CreateNode->info = NewInfo;
				CreateNode->Next = Iter->Next;
				Iter->Next = CreateNode;
            }
            Iter = Iter->Next;
        }
	}

	void remove_once_with_key(Key ExistKey){ // removes first element with Key == ExistKey
		Node *Current = Head, *Helper = nullptr;
		if (!Head) return;
		else{
			while (Current){
				if (Current->key == ExistKey){
					if (Current == Head) Head = Current->Next;
					else Helper->Next = Current->Next;

					delete Current;
					return;
				}
				Helper = Current;
				Current = Current->Next;
			}
		}
	}

	void remove_all_with_key(Key ExistKey){ // removes all elements with Key == ExistKey
		bool Existance = find_key(ExistKey);
		while (Existance){
			remove_once_with_key(ExistKey);
			Existance = find_key(ExistKey);
		}
	}

	void remove_first(){ // removes first element in the list
		if (Head == nullptr) return;
		Node* Curr = Head;
		Head = Curr->Next;
		delete Curr;
	}

	void remove_last(){ // removes last element in the list
		if (Head == nullptr) return;
		Node *Current = Head, *Previous = nullptr;
		while (Current->Next){
			Previous = Current;
			Current = Current->Next;
		}
		Previous->Next = nullptr;
		delete Current;
	}

	bool find_key(Key ExistKey){ // Searches for Node with given Key [true - found; false - notfound]
		if (!Head) return false;
		Node* Current = Head;
		while (Current){
			if (Current->key == ExistKey) return true;
			else Current = Current->Next;
		}
		return false;
	}

	void clear_all(){ // removes all elements in the list
		if (Head == nullptr) return;
		Node* Curr = Head;
		while (Curr) remove_first();
	}

	bool is_empty(){ // checks whether list is empty or not [1 - empty; 0 - not empty]
		if (Head) return false;
		else return true;
	}

	bool is_key(const Key ExistKey){ // checks whether there exists a given key or not [1 - exists; 0 - not exists]
		if (!Head) return false;
		Node* Curr = Head;
		while (Curr){
			if (Curr->key == ExistKey) return true;
			Curr = Curr->Next;
		}
		return false;
	}

	int count(const Key ExistKey){ // counts all elements with given Key
		if (!Head) return 0;
		int counter = 0;
		Node* Curr = Head;
		while (Curr){
			if (Curr->key == ExistKey) counter++;
			Curr = Curr->Next;
		}
		return counter;
	}

	int count(){ // counts the number of elements in the list
		if (!Head) return 0;
		int counter = 0;
		Node* Curr = Head;

		while (Curr){
			counter++;
			Curr = Curr->Next;
		}
		return counter;
	}

	void print(){
		if (!Head){
			cout << "List is empty." << endl;
			return;
		}
        Sequence<Key, Info>::iterator iter = Head;
		while(iter != nullptr){
             cout << "Key: " << iter->key << "\t\t" << "Info: " << iter->info << endl;
             iter = iter->Next;
        }
	}

    void CopyAll(const Sequence<Key, Info>& Source){
        Node* temp = Source.Head;
        while (temp){
            this->add_back(temp->key, temp->info);
            temp = temp->Next;
        }
    }
	friend void split_by_key(const Sequence<Key, Info> &seq, Key start_key, int len1, int len2, int count,
	Sequence <Key, Info> &seq1, Sequence <Key, Info> &seq2);

	friend void split_by_pos(const Sequence<Key, Info> &seq, int start_pos, int len1, int len2, int count,
	Sequence <Key, Info> &seq1, Sequence <Key, Info> &seq2);
};

template <typename Key, typename Info>
void split_by_key(const Sequence<Key, Info> &seq, Key start_key, int len1, int len2, int count,
Sequence <Key, Info> &seq1, Sequence <Key, Info> &seq2){
	if(count < 1 || len1 < 1 || len2 < 1){
		cerr << "wrong starting count or length input" << endl;
	}
	typename Sequence<Key, Info>::iterator Iter= seq.const_begin();
	while(!Iter.is_empty()){
		if(Iter->key == start_key){
			break;
		}
		Iter++;
	}
	seq1.clear_all();
	seq2.clear_all();
	for (int k=0; k<count; k++){
		for (int i =0; i <len1; i++){
			seq1.add_back(Iter);
			Iter++;
		}
		for (int j=0; j<len2; j++){
			seq2.add_back(Iter);
			Iter++;
		}
	}
}

template <typename Key, typename Info>
void split_by_pos(const Sequence<Key, Info> &seq, int start_pos, int len1, int len2, int count,
Sequence <Key, Info> &seq1, Sequence <Key, Info> &seq2){
	typename Sequence<Key, Info>::iterator Iter= seq.const_begin();
	if(start_pos < 1 || count < 1 || len1 < 1 || len2 < 1){
		cerr << "wrong starting postion, length or count input" << endl;
	}
	Iter.skip(start_pos-1);
	seq1.clear_all();
	seq2.clear_all();
	for (int k=0; k<count; k++){
		for (int i =0; i <len1; i++){
			seq1.add_back(Iter);
			Iter++;
		}
		for (int j=0; j<len2; j++){
			seq2.add_back(Iter);
			Iter++;
		}
	}
}