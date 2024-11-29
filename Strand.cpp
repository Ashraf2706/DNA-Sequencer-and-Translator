#include "Strand.h"

// Name: Strand() - Default Constructor
// Desc: Used to build a new empty strand (m_head, m_tail = nullptr and size = 0)
// Preconditions: None
// Postconditions: Creates a new strand with a default name
Strand::Strand(){
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
  m_name = "N/A";
}


// Name: Strand(string) - Overloaded Constructor
// Desc: Used to build a new empty strand with the name passed
//       with m_head, m_tail = nullptr; size = 0;
// Preconditions: None
// Postconditions: Creates a new strand with passed name
Strand::Strand(string name){
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
  m_name = name;
}


// Name: ~Strand() - Destructor
// Desc: Used to destruct a strand
// Preconditions: There is an existing strand with at least one node
// Postconditions: Strand is deallocated (including all dynamically allocated nodes)
//                 to have no memory leaks!
Strand::~Strand(){
  Node *current = m_head;
  // iterate through and remove each node
  while(current != nullptr){
      m_head = current; //set m_head to current
      current = current -> m_next; //moves current to m_next
      delete m_head;// deletes m_head
  }
  //Resets all pointers
  m_name = "";
  m_head = nullptr; //sets m_head to null
  m_tail = nullptr; //sets m_tail to null 
  m_size = 0; //sets m_size to 0
  delete current; //deletes current
}


// Name: InsertEnd
// Desc: Takes in a char. Creates a new node.
//       Inserts node at the end of the strand. Increases size.
// Preconditions: Requires a strand
// Postconditions: Strand is larger.
void Strand::InsertEnd(char data){
  Node *temp = new Node(); //initialize temp node
  temp -> m_data = data;
  temp -> m_next = nullptr;

  //if the node added is first node, then set head and tail to new node
  if (m_head == nullptr){
    m_head = temp;
    m_tail = temp;
    m_size = 1;
  }else{
    // if node added is not first then set new tail with temp
    m_tail -> m_next = temp;
    m_tail = m_tail -> m_next;
    m_size++;
  }
}


// Name: GetName()
// Preconditions: Requires a strand
// Postconditions: Returns m_name;
string Strand::GetName(){
  return m_name;
}


// Name: GetSize()
// Preconditions: Requires a strand
// Postconditions: Returns m_size;
int Strand::GetSize(){
  return m_size;
}


// Name: ReverseSequence
// Preconditions: Reverses the strand
// Postconditions: Strand sequence is reversed in place; nothing returned
void Strand::ReverseSequence(){
  Node *head = m_head;
  Node *tail = m_tail;
  Node *current = m_head;
  Node *previous = nullptr;
  Node *next;

  while(current != nullptr){
    next = current -> m_next;
    current -> m_next = previous;
    previous = current;
    current = next;
  }
  m_head = tail;
  m_tail = head;
}


// Name: GetData
// Desc: Returns the data at a specific location in the strand.
//       Iterates to node and returns char.
// Preconditions: Requires a DNA sequence
// Postconditions: Returns a single char from a node
char Strand::GetData(int nodeNum){
  Node *temp = m_head; //set head to temp
  //iterate through for a number of times
  for (int i = 0; i < nodeNum; i++){
    if (i != 0){
      temp = temp -> m_next; // set temp to next until the loop ends
    }
  }
  char output = temp -> m_data;
  return output;
}


// Name: operator<<
// Desc: Overloaded << operator to return ostream from strand
//       Iterates over the entire strand and builds an output stream
//       (Called like cout << *m_DNA.at(i); in Sequencer)
// Preconditions: Requires a strand
// Postconditions: Returns an output stream (does not cout the output)
ostream &operator<< (ostream &output, Strand &myStrand){
  output << "***" << myStrand.m_name << "***" << endl;
  for (int i = 0; i < myStrand.GetSize() + 1; i++){
    if (i != 0){
      output << myStrand.GetData(i) << "->"; 
    }
  }
  output << "END" << endl;
  return output;
}
