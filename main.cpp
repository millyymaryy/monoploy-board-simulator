#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

static const int MAX_SPACES = 40;

// -------------------------------
// Data class (NOT a struct)
// -------------------------------
class MonopolySpace {
public:
string propertyName;
string propertyColor;
int value;
int rent;

    MonopolySpace() {
        propertyName = "";
        propertyColor = "";
        value = 0;
        rent = 0;
    }

    MonopolySpace(string propertyName, string propertyColor, int value, int rent) {
        /* TODO: Define overloaded constructor here */
        propertyName = this->propertyName;
        propertyColor = this->propertyColor;
        value = this->value;
        rent = this->rent;
    }

    string getName() {
        return propertyName;
    }

    string getColor() {
        return propertyColor;
    }

    int getValue() {
        return value;
    }

    int getRent() {
        return rent;
    }
    //make setter function
    bool isEqual(MonopolySpace other) {
        /* TODO: Define isEqual here (compare by name is fine if you enforce uniqueness) */
        if(propertyName == other.getName()){
            return true;
        }
        else {
            return false;
        }
    }

    void print() {
        /* TODO: Define print here */
        // Example style:
         cout << propertyName << " | " << propertyColor << " | $" << value << " | Rent " << rent;
        // Ex (what the output would look like:) hollyword | red | $20 | Rent 5
    }
};

// -------------------------------
// Template Node class (NOT a struct)
// -------------------------------
template <typename T>
class Node {
public:
T data;
Node<T>* nextNode;

    Node(T value) {
        data = value;
        nextNode = nullptr;
    }
};

// -------------------------------
// Template Circular Linked List class
// Spring 2026 version: traversable board
// -------------------------------
template <typename T>
class CircularLinkedList {
private:
Node<T>* headNode;
Node<T>* tailNode;

    // player cursor for traversal-based gameplay
    Node<T>* playerNode;

    int nodeCount;
    int passGoCount;

public:
CircularLinkedList() {
headNode = nullptr;
tailNode = nullptr;
playerNode = nullptr;

        nodeCount = 0;
        passGoCount = 0;
    }

    // -------------------------------
    // Board Construction Policy (Reminder)
    // -------------------------------
    // Spaces are added during board construction BEFORE gameplay.
    // You choose how to construct the board:
    // - hardcode spaces, read from file, or generate programmatically
    // The only non-negotiable requirement:
    // - enforce MAX_SPACES
    // - maintain circular integrity
    // -------------------------------

    // -------------------------------
    // Core A: Add a Space with Capacity Enforcement
    // -------------------------------
// TODO:
// - If nodeCount == MAX_SPACES return false (do not corrupt list)
// - Create new node
// - If empty list: head=tail=player=new, new->next=head
// - Else: tail->next=new, tail=new, tail->next=head
// - nodeCount++

    bool addSpace(T value) {
       if(nodeCount == MAX_SPACES){
        return false;
        }
        Node<T>* newNode = new Node<T>(value);
        if(headNode == nullptr){
            headNode = newNode;
            tailNode = newNode;
            playerNode = newNode;
            newNode->nextNode = headNode;
        }
        else {
        tailNode->nextNode = newNode;
        tailNode = newNode;
        tailNode->nextNode = headNode;
        }
        nodeCount++;
    return true;
    }

    // -------------------------------
    // Core B: Add Multiple Spaces at Once
    // -------------------------------
    int addMany(vector<T> values) {
        // TODO:
        // - Add sequentially until full
        // - Stop exactly when you reach MAX_SPACES
        // - Return number successfully added
        // - Do not corrupt pointers if capacity is exceeded
    int add = 0;
    for (int i=0;i<(int)values.size() && nodeCount < MAX_SPACES;i++) {
        if (addSpace(values[i])) {
            add++;
        }
        else {
            return add;
        }
    }
}

    // -------------------------------
    // Core C: Traversal-Based Player Movement
    // -------------------------------
    void movePlayer(int steps) {
        // TODO:
        // - Move playerNode forward 'steps' times, node-by-node
        // - Wrap naturally because list is circular
        // - Detect and track passing GO:
        //   increment passGoCount when a move crosses from tail back to head
        // - Must handle empty list safely
        if (playerNode == nullptr) { //empty list
            return;
        }
        for (int i = 0; i <steps; i++) {
            if (playerNode->nextNode == headNode) {
                passGoCount++;
            }
            playerNode = playerNode->nextNode; // playerNode = the next node 
        }
}

    // -------------------------------
    // Core D: Controlled Board Display
    // -------------------------------
    void printFromPlayer(int count) {
        // TODO:
        // - Print exactly 'count' nodes starting from playerNode
        // - Must not infinite loop
        // - Must handle empty list
        // - Output must be deterministic and readable
        if (playerNode == nullptr) { //empty list
            return;
        }
        Node<T>* curr = playerNode; // curr points to player node
        for (int i = 0; i < count; i++) { // start at i = 0, then if i is less than count inc by 1
            curr->data.print(); // print curr next node's data
            curr = curr->nextNode; // curr now equals the next node
        }
    }

    // Optional helper: print full board once (one full cycle)
    void printBoardOnce() {
        // TODO:
        // - Traverse exactly one full cycle and print each node
        if (headNode == nullptr) { //empty list
            cout >> "Board is empty" << endl;
            return;
        }
        Node<T>* curr = headNode; // curr points to the head node
        curr->data.print(); // print out the data from the next node after curr (head)
        curr = curr->nextNode; // curr now equals the next node
        while (curr != headNode) { //keep going until curr = head again
            curr->data.print(); //then print curr's next data
            curr = curr->nextNode; // curr now equals the next node
        }

    }

    // -------------------------------
    // Advanced Option A (Level 1): removeByName
    // -------------------------------
    bool removeByName(string name) {
        // TODO:
        // - Delete FIRST matching node
        // - Must handle:
        //   - deleting head
        //   - deleting tail
        //   - deleting the only-node list
        // - Maintain circular link tail->next=head
        // - If playerNode points to deleted node, move playerNode to a safe node
        // - nodeCount--
    if (headNode == nullptr) {
        return false;
    }
    Node<T>* curr = headNode;
    Node<T>* prev = tailNode;

    do {
        if (curr->data.getName() == name) {
            // Case 1: only one node in the list
            if ( curr == headNode && curr == tailNode) {
                if (playerNode == curr) {
                    playerNode = nullptr;
                }
                delete curr;
                headNode = nullptr;
                tailNode = nullptr;
                nodeCount--;
                return true;
            }
            if (playerNode == curr) {
                playerNode = curr->nextNode;
            }
            // Case 2: deleting head
            if (curr == headNode) {
                headNode = headNode->nextNode;
                tailNode->nextNode = headNode;
            }
            // Case 3: deleting tail
            if (curr == tailNode) {
                tailNode = prev;
                tailNode->nextNode = headNode;
            }

        }
    }

    }

    // -------------------------------
    // Advanced Option A (Level 1): findByColor
    // -------------------------------
    vector<string> findByColor(string color) {
        // TODO:
        // - Traverse ring exactly once
        // - Collect matching names in vector<string>
        // - Return matches
        cout << "findByColor unwritten" << endl;
        vector<string> matches;
        return matches;
    }

    // -------------------------------
    // Advanced Option B (Level 2): Mirror the Board (Circular Reversal)
    // -------------------------------
    void mirrorBoard() {
        // TODO:
        // - Reverse the direction of the circular list by reversing next pointers
        // - Preserve circular structure
        // - Correctly handle empty list and single-node list
        // - Player cursor must remain on the same logical space after reversal
        cout << "mirrorBoard unwritten" << endl;
    }

    // -------------------------------
    // Edge-case helper: countSpaces O(n)
    // -------------------------------
    int countSpaces() {
        // TODO:
        // - Must be O(n), traverse exactly once with correct stop condition
        // - Do NOT rely on nodeCount for this method
        cout << "countSpaces unwritten" << endl;
        return 0;
    }

    // -------------------------------
    // Cleanup
    // -------------------------------
    void clear() {
        // TODO:
        // - Safely delete all nodes
        // - Tip: if tailNode exists, break the cycle first: tailNode->nextNode = nullptr
        // - Then delete like a normal singly linked list
        cout << "clear unwritten" << endl;
    }
};

// -------------------------------
// Main: playable loop demo
// -------------------------------
int rollDice2to12() {
return (rand() % 6 + 1) + (rand() % 6 + 1);
}

int main() {
srand(static_cast<unsigned>(time(nullptr)));

    CircularLinkedList<MonopolySpace> board;

    // -------------------------------
    // Board Construction Phase
    // -------------------------------
    // You decide how to build the board:
    // - hardcode spaces, load from file, or generate spaces programmatically
    // The only requirement: never exceed MAX_SPACES and keep the list circular.
    //
    // Example (hardcoded) usage:
    // vector<MonopolySpace> spaces;
    // spaces.push_back(MonopolySpace("GO","None",0,0));
    // ...
    // board.addMany(spaces);
    //
    // NOTE: This starter calls addSpace once to show the intended API,
    // but your final submission should build a meaningful board.
    board.addSpace(MonopolySpace("GO", "None", 0, 0));

    // -------------------------------
    // Playable Traversal Loop
    // -------------------------------
    /*for (int turn = 1; turn <= 10; turn++) {
        int roll = rollDice2to12();
        cout << "\nTurn " << turn << " | Rolled: " << roll << endl;

        board.movePlayer(roll);

        cout << "Board view from player (next 5 spaces):" << endl;
        board.printFromPlayer(5);

        cout << "Times passed GO so far: " << board.getPassGoCount() << endl;
    }*/

    // -------------------------------
    // Advanced Feature Demos (students choose path)
    // -------------------------------
    // Option A examples:
    // board.removeByName("Baltic Avenue");
    // vector<string> brownProps = board.findByColor("Brown");
    //
    // Option B example:
    // board.mirrorBoard();

    board.addSpace(MonopolySpace("H", "Pink", 5, 1));
    board.addSpace(MonopolySpace("I", "Purple", 10, 2));
    board.addSpace(MonopolySpace("J", "Blue", 15, 3));

    return 0;
}