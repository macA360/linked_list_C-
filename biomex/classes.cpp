// Include the iostream standard library for input and output operations
#include <iostream>

// Node class definition
class Node {
public:
    Node* next;  // Pointer to the next node in the list

    // Constructor initializes the next pointer to nullptr, indicating the end of the list segment
    Node() : next(nullptr) {}

    // Virtual destructor ensures derived class destructors are called, allowing for proper resource cleanup
    virtual ~Node() {}


    // Pure virtual method for printing the node data. Must be overridden by derived classes.
    virtual void printData() const = 0; // Make Node an abstract class
 
};


class FloatNode : public Node {
public:
    float data;  // The normalized data value stored in the node

    // Constructor normalizes the input value and assigns it to the node's data member
    FloatNode(float value) : data(normalize(value)) {}

    // Overrides the printData method to print the node's data as a floating-point value
    void printData() const override {
        std::cout << data << " (float)" << std::endl;
    }

private:
    // Normalize the input value
    static float normalize(float value) {
        const float mean = 10.0f;  // Example mean value for normalization
        const float stdDev = 2.0f; // Example standard deviation for normalization

        return (value - mean) / stdDev;
    }
};

class IntNode : public Node {
public:
    int data;  // The data stored in the node

    // Constructor that takes a float, normalizes and quantizes it
    IntNode(float value) : data(normalizeAndQuantize(value)) {}

    // Override the printData method to handle int data
    void printData() const override {
        std::cout << data << " (int)" << std::endl;
    }

private:
    // Normalize the input value and then quantize it
    static int normalizeAndQuantize(float value) {
        const float mean = 10.0f;       // Example mean value for normalization
        const float stdDev = 2.0f;      // Example standard deviation for normalization
        const float scale = 0.1f;       // Example scale for quantization
        const int zeroPoint = 128;      // Example zero point for quantization

        float normalized = (value - mean) / stdDev;
        return static_cast<int>(normalized / scale) + zeroPoint;
    }
};

class LinkedList {
private:
    Node* head;  // Pointer to the first node in the list

public:
    // Constructor
    LinkedList() : head(nullptr) {}

    // Destructor to free the allocated nodes
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Appends a new node to the list. The node type (float or int) depends on the isQuantized flag.
    void append(float value, bool isQuantized) {
        Node* newNode;
        if (isQuantized) {
            newNode = new IntNode(value);
        }
        else {
            newNode = new FloatNode(value);
        }

        if (head == nullptr) {
            head = newNode;  // List was empty, new node becomes the head
        }
        else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;  // Append the new node at the end
        }
    }

    // Iterates through the list and prints the data of each node using the overridden printData method.
    void printList() const {
        Node* current = head;
        while (current != nullptr) {
            current->printData();
            current = current->next;
        }
    }
    // can add other methods for list operations if needed
};


int main() {
    LinkedList myList;

    // Appending nodes with float values
    std::cout << "Appending non-quantized (float) nodes:" << std::endl;
    myList.append(12.3f, false); // Append a float node
    myList.append(45.6f, false);
    myList.append(78.9f, false);

    // Print the list contents after appending nodes
    std::cout << "\nContents of the non-quantized (float) list:" << std::endl;
    myList.printList();
    

    // Appending nodes with quantized (int) values
    std::cout << "\nAppending quantized (int) nodes:" << std::endl;
    myList.append(12.3f, true); // Append an int node
    myList.append(45.6f, true);
    myList.append(78.9f, true);

    // Print the list contents after appending nodes
    std::cout << "\nAll contents of the linked list:" << std::endl;
    myList.printList();
    
    return 0;
}
