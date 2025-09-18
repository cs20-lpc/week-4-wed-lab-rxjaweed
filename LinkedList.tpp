using namespace std;

template <typename T>
LinkedList<T>::LinkedList()
: head(nullptr), length(0) { }

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& copyObj) 
: head(nullptr), length(0) {
    copy(copyObj);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
void LinkedList<T>::append(const T& elem) {
    Node* n = new Node(elem);

    if (head == nullptr) {
        head = n;
    } else {
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = n;
    }
    this->length++;
}

template <typename T>
void LinkedList<T>::clear() {
    Node* prev = nullptr;
    while (head != nullptr) {
        prev = head;
        head = head->next;
        delete prev;
    }
    this->length = 0;
}

template <typename T>
void LinkedList<T>::copy(const LinkedList<T>& copyObj) {
    if (copyObj.head == nullptr) return;

    head = new Node(copyObj.head->value);
    Node* currentNew = head;
    Node* currentOld = copyObj.head->next;

    while (currentOld != nullptr) {
        Node* newNode = new Node(currentOld->value);
        currentNew->next = newNode;
        currentNew = newNode;
        currentOld = currentOld->next;
    }
    this->length = copyObj.length;
}

template <typename T>
T LinkedList<T>::getElement(int position) const {
    if (position < 0 || position >= this->length) {
        throw string("getElement: error, position out of bounds");
    }
    
    Node* curr = head;
    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }
    return curr->value;
}

template <typename T>
int LinkedList<T>::getLength() const {
    return this->length;
}

template <typename T>
void LinkedList<T>::insert(int position, const T& elem) {
    if (position < 0 || position > this->length) {
        cout << "Insert: error, position out of bounds" << endl;
        return;
    }

    Node* newNode = new Node(elem);

    if (position == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* nodePtr = head;
        for (int i = 0; i < position - 1; i++) {
            nodePtr = nodePtr->next;
        }
        newNode->next = nodePtr->next;
        nodePtr->next = newNode;
    }
    this->length++;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
void LinkedList<T>::remove(int position) {
    if (head == nullptr) {
        cout << "Remove: error, list is empty" << endl;
        return;
    }
    if (position < 0 || position >= this->length) {
        cout << "Remove: error, position out of bounds" << endl;
        return;
    }

    Node* temp;

    if (position == 0) {
        temp = head;
        head = head->next;
    } else {
        Node* nodePtr = head;
        for (int i = 0; i < position - 1; i++) {
            nodePtr = nodePtr->next;
        }
        temp = nodePtr->next;
        nodePtr->next = temp->next;
    }

    delete temp;
    this->length--;
}

template <typename T>
void LinkedList<T>::replace(int position, const T& elem) {
    if (position < 0 || position >= this->length) {
        throw string("replace: error, position out of bounds");
    }
    Node* curr = head;
    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }
    curr->value = elem;
}

template <typename T>
ostream& operator<<(ostream& outStream, const LinkedList<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    } else {
        typename LinkedList<T>::Node* curr = myObj.head;
        while (curr != nullptr) {
            outStream << curr->value;
            if (curr->next != nullptr) {
                outStream << " --> ";
            }
            curr = curr->next;
        }
        outStream << endl;
    }
    return outStream;
}
