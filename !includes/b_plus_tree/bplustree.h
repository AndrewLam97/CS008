#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <climits>
using namespace std;

bool DEBUG = true;

template <typename T>
class BPTree;

template <typename T>
class Node
{
private:
  static const int MINIMUM = 1;
  static const int MAXIMUM = 2;
  bool IS_LEAF;
  int *key, size;
  Node **ptr;
  friend class BPTree;

public:
  Node();
};

template <typename T>
class BPTree
{
  static const int MINIMUM = 1;
  static const int MAXIMUM = 2;
  Node *root;
  void insertInternal(int, Node *, Node *);
  void removeInternal(int, Node *, Node *);
  Node *findParent(Node *, Node *);

public:
  BPTree();
  bool contains(int);
  void insert(int);
  void remove(int);
  void display(Node *);
  Node *getRoot();
  void cleanUp(Node *);
  ~BPTree();
};
template <typename T>
Node::Node()
{
  //dynamic memory allocation
  key = new int[MAXIMUM];
  ptr = new Node *[MAXIMUM + 1];
}
template <typename T>
BPTree::BPTree()
{
  root = NULL;
}
template <typename T>
bool BPTree::contains(int x)
{
  //search logic
  if (root == NULL)
  {
    //empty
    if(DEBUG)cout << "Tree empty\n";
    return false;
  }
  else
  {
    Node *cursor = root;
    //in the following while loop, cursor will travel to the leaf node possibly consisting the key
    while (cursor->IS_LEAF == false)
    {
      for (int i = 0; i < cursor->size; i++)
      {
        if (x < cursor->key[i])
        {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1)
        {
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    //in the following for loop, we search for the key if it exists
    for (int i = 0; i < cursor->size; i++)
    {
      if (cursor->key[i] == x)
      {
        //if(DEBUG)cout << "Found\n";
        return true;
      }
    }
    //if(DEBUG)cout << "Not found\n";
    return false;
  }
}
template <typename T>
void BPTree::insert(int x)
{
  //insert logic
  if (root == NULL)
  {
    root = new Node;
    root->key[0] = x;
    root->IS_LEAF = true;
    root->size = 1;
    if(DEBUG)cout << "Created root\nInserted " << x << " successfully\n";
  }
  else
  {
    if(contains(x)){
      cout << "Element already present" << endl;
      return;
    }
    Node *cursor = root;
    Node *parent;
    //in the following while loop, cursor will travel to the leaf node possibly consisting the key
    while (cursor->IS_LEAF == false)
    {
      parent = cursor;
      for (int i = 0; i < cursor->size; i++)
      {
        if (x < cursor->key[i])
        {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1)
        {
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    //now cursor is the leaf node in which we'll insert the new key
    if (cursor->size < MAXIMUM)
    {
      //if cursor is not full
      //find the correct position for new key
      int i = 0;
      while (x > cursor->key[i] && i < cursor->size)
        i++;
      //make space for new key
      for (int j = cursor->size; j > i; j--)
      {
        cursor->key[j] = cursor->key[j - 1];
      }
      cursor->key[i] = x;
      cursor->size++;
      cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
      cursor->ptr[cursor->size - 1] = NULL;
      if(DEBUG)cout << "Inserted " << x << " successfully\n";
    }
    else
    {
      //if(DEBUG)cout << "Inserted " << x << " successfully\n";
      //if(DEBUG)cout << "Overflow in leaf node!\nSplitting leaf node\n";
      //overflow condition
      //create new leaf node
      Node *newLeaf = new Node;
      //create a virtual node and insert x into it
      int virtualNode[MAXIMUM + 1];
      for (int i = 0; i < MAXIMUM; i++)
      {
        virtualNode[i] = cursor->key[i];
      }
      int i = 0, j;
      while (x > virtualNode[i] && i < MAXIMUM)
        i++;
      //make space for new key
      for (int j = MAXIMUM + 1; j > i; j--)
      {
        virtualNode[j] = virtualNode[j - 1];
      }
      virtualNode[i] = x;
      newLeaf->IS_LEAF = true;
      //split the cursor into two leaf nodes
      cursor->size = (MAXIMUM + 1) / 2; //1
      newLeaf->size = MAXIMUM + 1 - (MAXIMUM + 1) / 2; //2
      //make cursor point to new leaf node
      cursor->ptr[cursor->size] = newLeaf;
      //make new leaf node point to the next leaf node
      newLeaf->ptr[newLeaf->size] = cursor->ptr[MAXIMUM];
      cursor->ptr[MAXIMUM] = NULL;
      //now give elements to new leaf nodes
      for (i = 0; i < cursor->size; i++)
      {
        cursor->key[i] = virtualNode[i];
      }
      for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++)
      {
        newLeaf->key[i] = virtualNode[j];
      }
      //modify the parent
      if (cursor == root)
      {
        //if cursor is a root node, we create a new root
        Node *newRoot = new Node;
        newRoot->key[0] = newLeaf->key[0];
        newRoot->ptr[0] = cursor;
        newRoot->ptr[1] = newLeaf;
        newRoot->IS_LEAF = false;
        newRoot->size = 1;
        root = newRoot;
        if(DEBUG)cout << "Created new root\n";
      }
      else
      {
        //insert new key in parent node
        insertInternal(newLeaf->key[0], parent, newLeaf);
      }
    }
  }
}
template <typename T>
void BPTree::insertInternal(int x, Node *cursor, Node *child)
{
  if (cursor->size < MAXIMUM)
  {
    //if cursor is not full
    //find the correct position for new key
    int i = 0;
    while (x > cursor->key[i] && i < cursor->size)
      i++;
    //make space for new key
    for (int j = cursor->size; j > i; j--)
    {
      cursor->key[j] = cursor->key[j - 1];
    } //make space for new pointer
    for (int j = cursor->size + 1; j > i + 1; j--)
    {
      cursor->ptr[j] = cursor->ptr[j - 1];
    }
    cursor->key[i] = x;
    cursor->size++;
    cursor->ptr[i + 1] = child;
    if(DEBUG)cout << "Inserted key in an Internal node successfully\n";
  }
  else
  {
    //if(DEBUG)cout << "Internal MAXIMUM Reached\n";
    if(DEBUG)cout << "Overflow in internal node! Splitting internal node\n";
    //cout << "Initial cursor keys [" << cursor->key[0] << " " << cursor->key[1] << cursor->key[2] << endl;

    //if overflow in internal node
    //create new internal node
    Node *newInternal = new Node;
    //create virtual Internal Node;
    int virtualKey[MAXIMUM + 1];
    Node *virtualPtr[MAXIMUM + 2];
    for (int i = 0; i < MAXIMUM; i++)
    {
      virtualKey[i] = cursor->key[i];
    }
    //copy ptrs from cursor
    for (int i = 0; i < MAXIMUM + 1; i++)
    {
      virtualPtr[i] = cursor->ptr[i];
    }
    int i = 0, j;
    while (x > virtualKey[i] && i < MAXIMUM)
      i++;
      //cout << "i: "<<i<<endl;
    //make space for new key
    for (int j = MAXIMUM + 1; j > i; j--)
    {
      virtualKey[j] = virtualKey[j - 1];
    }
    //cout << "VIRTUALKEY i:" << i << ": " << x << endl;
    virtualKey[i] = x;
    //cout << "VIRTUALKEY:" << virtualKey[0] << " " << virtualKey[1] << " "<< virtualKey[2] << " " << endl;

    //make space for new ptr
    for (int j = MAXIMUM + 2; j > i + 1; j--)
    {
      virtualPtr[j] = virtualPtr[j - 1];
    }
    //reset virtkey[i]
    virtualKey[i] = x;
    int temp = i;
    //cout << "temp " << temp << endl;

    //cout << "VIRTUALKEY:" << virtualKey[0] << " " << virtualKey[1] << " "<< virtualKey[2] << " " << endl;

    //cout << "Inserting child to virtualPtr i+1, i: " << i << endl; 
    //cout << "Child contains" << child->key[0] << " " << child->key[1] << endl;
    virtualPtr[i + 1] = child;
    newInternal->IS_LEAF = false;
    //split cursor into two nodes
    cursor->size = (MAXIMUM + 1) / 2;
    newInternal->size = MAXIMUM - (MAXIMUM + 1) / 2;
    //give elements and pointers to the new node
    for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++)
    {
      newInternal->key[i] = virtualKey[j];
    }
    //cout << "VIRTUALKEY:" << virtualKey[0] << " " << virtualKey[1] << " "<< virtualKey[2] << " " << endl;

    for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++)
    {
      //cout << "Assigning virtualPtr["<<j<<"] to newInt->ptr["<<i<<endl;
      newInternal->ptr[i] = virtualPtr[j];
    }
    // m = cursor->key[cursor->size]
    //NEW give cursor new elements from virtualKey
    //cout << "i:"<<i<<" j"<<j<<endl;
    for(i=temp;i<cursor->size+1;i++){
      //cout << "Copying from virtualKey" << virtualKey[i] << endl;
      cursor->key[i] = virtualKey[i];
    }

    //GIVE CURSOR CHILD PTR FROM VIRTPTR
    cursor->ptr[1] = virtualPtr[1];

    //cout << "Post COPY: cursor keys [" << cursor->key[0] << " " << cursor->key[1] << cursor->key[2] << endl;
    //cout << "Cursor Size: " << cursor->size << endl;
    if (cursor == root)
    {
      //if cursor is a root node, we create a new root
      Node *newRoot = new Node;
      //cout << "Cursor/Root size: " <<  cursor->size << ", Cursor/Root keys [" << cursor->key[0] << " " << cursor->key[1] << " " << cursor->key[2] << endl;
      //cout << "newInt size: " <<  newInternal->size << ", newInt keys [" << newInternal->key[0] << " " << newInternal->key[1] << " " << newInternal->key[1] << endl;
      //cout << "New root key: " << cursor->key[cursor->size] << endl;
      newRoot->key[0] = cursor->key[cursor->size];
      //newRoot->key[0] = cursor->key[0];
      newRoot->ptr[0] = root;
      newRoot->ptr[1] = newInternal;
      newRoot->IS_LEAF = false;
      newRoot->size = 1;
      root = newRoot;
      //if(DEBUG)cout << "Created new root\n";
    }
    else
    {
      //recursion
      //find depth first search to find parent of cursor
      insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
    }
  }
}
template <typename T>
Node *BPTree::findParent(Node *cursor, Node *child)
{
  //finds parent using depth first traversal and ignores leaf nodes as they cannot be parents
  //also ignores second last level because we will never find parent of a leaf node during insertion using this function
  Node *parent;
  if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF)
  {
    return NULL;
  }
  for (int i = 0; i < cursor->size + 1; i++)
  {
    if (cursor->ptr[i] == child)
    {
      parent = cursor;
      return parent;
    }
    else
    {
      parent = findParent(cursor->ptr[i], child);
      if (parent != NULL)
        return parent;
    }
  }
  return parent;
}
template <typename T>
void BPTree::remove(int x)
{
  //delete logic
  if (root == NULL)
  {
    if(DEBUG)cout << "Tree empty\n";
  }
  else
  {
    Node *cursor = root;
    Node *parent;
    int leftSibling, rightSibling;
    //in the following while loop, cursor will will travel to the leaf node possibly consisting the key
    while (cursor->IS_LEAF == false)
    {
      for (int i = 0; i < cursor->size; i++)
      {
        parent = cursor;
        leftSibling = i - 1;  //leftSibling is the index of left sibling in the parent node
        rightSibling = i + 1; //rightSibling is the index of right sibling in the parent node
        if (x < cursor->key[i])
        {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1)
        {
          leftSibling = i;
          rightSibling = i + 2;
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    //in the following for loop, we search for the key if it exists
    bool found = false;
    int pos;
    for (pos = 0; pos < cursor->size; pos++)
    {
      if (cursor->key[pos] == x)
      {
        found = true;
        break;
      }
    }
    if (!found) //if key does not exist in that leaf node
    {
      if(DEBUG)cout << "Not found\n";
      return;
    }
    //deleting the key
    for (int i = pos; i < cursor->size; i++)
    {
      cursor->key[i] = cursor->key[i + 1];
    }
    cursor->size--;
    if (cursor == root) //if it is root node, then make all pointers NULL
    {
      if(DEBUG)cout << "Deleted " << x << " from leaf node successfully\n";
      for (int i = 0; i < MAXIMUM + 1; i++)
      {
        cursor->ptr[i] = NULL;
      }
      if (cursor->size == 0) //if all keys are deleted
      {
        if(DEBUG)cout << "Tree died\n";
        delete[] cursor->key;
        delete[] cursor->ptr;
        delete cursor;
        root = NULL;
      }
      return;
    }
    cursor->ptr[cursor->size] = cursor->ptr[cursor->size + 1];
    cursor->ptr[cursor->size + 1] = NULL;
    if(DEBUG)cout << "Deleted " << x << " from leaf node successfully\n";
    if (cursor->size >= (MAXIMUM + 1) / 2) //no underflow
    {
      return;
    }
    if(DEBUG)cout << "Underflow in leaf node!\n";
    //underflow condition
    //first we try to transfer a key from sibling node
    //check if left sibling exists
    if (leftSibling >= 0)
    {
      Node *leftNode = parent->ptr[leftSibling];
      //check if it is possible to transfer
      if (leftNode->size >= (MAXIMUM + 1) / 2 + 1)
      {
        //make space for transfer
        for (int i = cursor->size; i > 0; i--)
        {
          cursor->key[i] = cursor->key[i - 1];
        }
        //shift pointer to next leaf
        cursor->size++;
        cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
        cursor->ptr[cursor->size - 1] = NULL;
        //transfer
        cursor->key[0] = leftNode->key[leftNode->size - 1];
        //shift pointer of leftsibling
        leftNode->size--;
        leftNode->ptr[leftNode->size] = cursor;
        leftNode->ptr[leftNode->size + 1] = NULL;
        //update parent
        parent->key[leftSibling] = cursor->key[0];
        if(DEBUG)cout << "Transferred " << cursor->key[0] << " from left sibling of leaf node\n";
        return;
      }
    }
    if (rightSibling <= parent->size) //check if right sibling exist
    {
      Node *rightNode = parent->ptr[rightSibling];
      //check if it is possible to transfer
      if (rightNode->size >= (MAXIMUM + 1) / 2 + 1)
      {
        //shift pointer to next leaf
        cursor->size++;
        cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
        cursor->ptr[cursor->size - 1] = NULL;
        //transfer
        cursor->key[cursor->size - 1] = rightNode->key[0];
        //shift pointer of rightsibling
        rightNode->size--;
        rightNode->ptr[rightNode->size] = rightNode->ptr[rightNode->size + 1];
        rightNode->ptr[rightNode->size + 1] = NULL;
        //shift conent of right sibling
        for (int i = 0; i < rightNode->size; i++)
        {
          rightNode->key[i] = rightNode->key[i + 1];
        }
        //update parent
        parent->key[rightSibling - 1] = rightNode->key[0];
        if(DEBUG)cout << "Transferred " << cursor->key[cursor->size - 1] << " from right sibling of leaf node\n";
        return;
      }
    }
    //must merge and delete a node
    if (leftSibling >= 0) //if left sibling exist
    {
      Node *leftNode = parent->ptr[leftSibling];
      // transfer all keys to leftsibling and then transfer pointer to next leaf node
      for (int i = leftNode->size, j = 0; j < cursor->size; i++, j++)
      {
        leftNode->key[i] = cursor->key[j];
      }
      leftNode->ptr[leftNode->size] = NULL;
      leftNode->size += cursor->size;
      leftNode->ptr[leftNode->size] = cursor->ptr[cursor->size];
      if(DEBUG)cout << "Merging two leaf nodes\n";
      removeInternal(parent->key[leftSibling], parent, cursor); // delete parent node key
      delete[] cursor->key;
      delete[] cursor->ptr;
      delete cursor;
    }
    else if (rightSibling <= parent->size) //if right sibling exist
    {
      Node *rightNode = parent->ptr[rightSibling];
      // transfer all keys to cursor and then transfer pointer to next leaf node
      for (int i = cursor->size, j = 0; j < rightNode->size; i++, j++)
      {
        cursor->key[i] = rightNode->key[j];
      }
      cursor->ptr[cursor->size] = NULL;
      cursor->size += rightNode->size;
      cursor->ptr[cursor->size] = rightNode->ptr[rightNode->size];
      if(DEBUG)cout << "Merging two leaf nodes\n";
      removeInternal(parent->key[rightSibling - 1], parent, rightNode); // delete parent node key
      delete[] rightNode->key;
      delete[] rightNode->ptr;
      delete rightNode;
    }
  }
}
template <typename T>
void BPTree::removeInternal(int x, Node *cursor, Node *child)
{
  //deleting the key x first
  //checking if key from root is to be deleted
  cout << "-----Removing Internal-----" << endl;
  cout << "Cursor Key: " << cursor->key[0] << endl;
  cout << "Cursor Size:" << cursor->size << endl;
  if (cursor == root)
  {
    if (cursor->size == 1) //if only one key is left, change root
    {
      if (cursor->ptr[1] == child)
      {
        delete[] child->key;
        delete[] child->ptr;
        delete child;
        root = cursor->ptr[0];
        delete[] cursor->key;
        delete[] cursor->ptr;
        delete cursor;
        if(DEBUG)cout << "Changed root node\n";
        return;
      }
      else if (cursor->ptr[0] == child)
      {
        delete[] child->key;
        delete[] child->ptr;
        delete child;
        root = cursor->ptr[1];
        delete[] cursor->key;
        delete[] cursor->ptr;
        delete cursor;
        if(DEBUG)cout << "Changed root node\n";
        return;
      }
    }
  }
  int pos;
  for (pos = 0; pos < cursor->size; pos++)
  {
    if (cursor->key[pos] == x)
    {
      break;
    }
  }
  //shift keys in cursor left from pos
  for (int i = pos; i < cursor->size; i++)
  {
    cursor->key[i] = cursor->key[i + 1];
  }
  //now deleting the pointer child
  for (pos = 0; pos < cursor->size + 1; pos++)
  {
    if (cursor->ptr[pos] == child)
    {
      break;
    }
  }
  for (int i = pos; i < cursor->size + 1; i++)
  {
    cursor->ptr[i] = cursor->ptr[i + 1];
  }
  cursor->size--;
  if (cursor->size >= ((MAXIMUM + 1) / (MINIMUM))) //no underflow,
  {
    if(DEBUG)cout << "Deleted " << x << " from internal node successfully\n";
    return;
  }
  if(DEBUG)cout << "Underflow in internal node!\n";
  //underflow, try to transfer first
  if (cursor == root)
    return;
  Node *parent = findParent(root, cursor);


  int leftSibling, rightSibling;
  //finding left n right sibling of cursor
  for (pos = 0; pos < parent->size + 1; pos++)
  {
    if (parent->ptr[pos] == cursor)
    {
      leftSibling = pos - 1;
      rightSibling = pos + 1;
      break;
    }
  }
  //try to transfer
  if (leftSibling >= 0) //if left sibling exists
  {
    Node *leftNode = parent->ptr[leftSibling];
    //check if it is possible to transfer
    //if (leftNode->size >= (MAXIMUM + 1) / 2)
    if (leftNode->size > (MAXIMUM + 1) / 2)
    {
      //make space for transfer of key
      for (int i = cursor->size; i > 0; i--)
      {
        cursor->key[i] = cursor->key[i - 1];
      }
      //transfer key from left sibling through parent
      cursor->key[0] = parent->key[leftSibling];
      parent->key[leftSibling] = leftNode->key[leftNode->size - 1];
      //transfer last pointer from leftnode to cursor
      //make space for transfer of ptr
      for (int i = cursor->size + 1; i > 0; i--)
      {
        cursor->ptr[i] = cursor->ptr[i - 1];
      }
      //transfer ptr
      cursor->ptr[0] = leftNode->ptr[leftNode->size];
      cursor->size++;
      leftNode->size--;
      if(DEBUG)cout << "Transferred " << cursor->key[0] << " from left sibling of internal node\n";
      return;
    }
  }
  if (rightSibling <= parent->size) //check if right sibling exist
  {
    Node *rightNode = parent->ptr[rightSibling];
    //check if it is possible to transfer
    //if (rightNode->size >= (MAXIMUM + 1) / 2)
    if (rightNode->size > (MAXIMUM + 1) / 2)
    {
      //transfer key from right sibling through parent
      cursor->key[cursor->size] = parent->key[pos];
      parent->key[pos] = rightNode->key[0];
      for (int i = 0; i < rightNode->size - 1; i++)
      {
        rightNode->key[i] = rightNode->key[i + 1];
      }
      //transfer first pointer from rightnode to cursor
      //transfer ptr
      cursor->ptr[cursor->size + 1] = rightNode->ptr[0];
      for (int i = 0; i < rightNode->size; ++i)
      {
        rightNode->ptr[i] = rightNode->ptr[i + 1];
      }
      cursor->size++;
      rightNode->size--;
      if(DEBUG)cout << "Transferred " << cursor->key[0] << " from right sibling of internal node\n";
      return;
    }
  }
  //transfer wasnt posssible hence do merging
  if (leftSibling >= 0)
  {
    //leftnode + parent key + cursor
    Node *leftNode = parent->ptr[leftSibling];
    leftNode->key[leftNode->size] = parent->key[leftSibling];
    for (int i = leftNode->size + 1, j = 0; j < cursor->size; j++)
    {
      leftNode->key[i] = cursor->key[j];
    }
    for (int i = leftNode->size + 1, j = 0; j < cursor->size + 1; j++)
    {
      leftNode->ptr[i] = cursor->ptr[j];
      cursor->ptr[j] = NULL;
    }
    leftNode->size += cursor->size + 1;
    cursor->size = 0;
    //delete cursor
    removeInternal(parent->key[leftSibling], parent, cursor);
    if(DEBUG)cout << "Merged with left sibling\n";
  }
  else if (rightSibling <= parent->size)
  {
    //cursor + parent key + rightnode
    Node *rightNode = parent->ptr[rightSibling];
    cursor->key[cursor->size] = parent->key[rightSibling - 1];
    for (int i = cursor->size + 1, j = 0; j < rightNode->size; j++)
    {
      cursor->key[i] = rightNode->key[j];
    }
    for (int i = cursor->size + 1, j = 0; j < rightNode->size + 1; j++)
    {
      cursor->ptr[i] = rightNode->ptr[j];
      rightNode->ptr[j] = NULL;
    }
    cursor->size += rightNode->size + 1;
    rightNode->size = 0;
    //delete cursor
    removeInternal(parent->key[rightSibling - 1], parent, rightNode);
    if(DEBUG)cout << "Merged with right sibling\n";
  }
}
template <typename T>
void BPTree::display(Node *cursor)
{
  //depth first display
  if (cursor != NULL)
  {
    for (int i = 0; i < cursor->size; i++)
    {
      cout << cursor->key[i] << " ";
    }
    if(cursor->IS_LEAF) cout << "*";
    cout << "\n";
    if (cursor->IS_LEAF != true)
    {
      for (int i = 0; i < cursor->size + 1; i++)
      {
        display(cursor->ptr[i]);
      }
    }
  }
}
template <typename T>
Node *BPTree::getRoot()
{
  return root;
}
template <typename T>
void BPTree::cleanUp(Node *cursor)
{
  //clean up logic
  if (cursor != NULL)
  {
    if (cursor->IS_LEAF != true)
    {
      for (int i = 0; i < cursor->size + 1; i++)
      {
        cleanUp(cursor->ptr[i]);
      }
    }
    for (int i = 0; i < cursor->size; i++)
    {
      if(DEBUG)cout << "Deleted key from memory: " << cursor->key[i] << "\n";
    }
    delete[] cursor->key;
    delete[] cursor->ptr;
    delete cursor;
  }
}
template <typename T>
BPTree::~BPTree()
{
  //calling cleanUp routine
  cleanUp(root);
}