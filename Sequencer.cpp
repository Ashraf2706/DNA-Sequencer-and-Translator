#include "Sequencer.h"

// Name: Sequencer (constructor)
// Desc: Creates a new sequencer to hold one or more DNA/mRNA strands make of
//       multiples of three nucleotides
// Preconditions:  Populates m_fileName from passed information from call
//                 For example: ./proj3 proj3_data1.txt
// Postconditions: A sequencer created to populate DNA/mRNA strands
Sequencer::Sequencer(string fileName){
  m_fileName = fileName; 
}


// Name:  Sequencer (destructor)
// Desc: Deallocates all dynamic aspects of a Sequencer
// Preconditions: There are an existing DNA/mRNA strand(s) (linked list)
// Postconditions: All vectors are cleared of DNA and mRNA strands
//                 Indicates that the strands have been deallocated
Sequencer::~Sequencer(){
  cout << "Deleting DNA Strands" << endl;
  for (unsigned int i = 0; i < m_DNA.size(); i++){
    delete m_DNA[i];
  }
  cout << "Deleting mRNA Strands" << endl;
  for (unsigned int i = 0; i < m_mRNA.size(); i++){
    delete m_mRNA[i];
  }
}


// Name: StartSequencing
// Desc: Calls ReadFile and continually calls mainmenu until the user exits
// Preconditions: m_fileName has been populated
// Postconditions: m_DNA has been populated (after ReadFile concludes)
void Sequencer::StartSequencing(){
  ReadFile();
  int choice = 0;
  do{
    choice = MainMenu();
    switch(choice){
      case 1:
        DisplayStrands();
        break;
      case 2:
        ReverseSequence();
        break;
      case 3:
        Transcribe();
        break;
      case 4:
        Translate();
        break;
      case 5:
        cout << "Exiting program" << endl;
        break;
      default:
        cout << "Invalid choice. Please try again." << endl;
        break;  
    }
  }while(choice != 5);
}
  

// Name: DisplayStrands
// Desc: Displays each strand in both mDNA and mRNA
//       Displays numbered type (For example, DNA 1) then the name of the strand.
//       Finally displays the strand with arrows between each nucleotide
// Preconditions: At least one linked list is in mDNA (may have mRNA)
// Postconditions: Displays DNA strand from one of the vectors
void Sequencer::DisplayStrands(){
  int dnaCount = 0;
  int mrnaCount = 0;
  if (m_DNA.size() > 0){
    for (unsigned int i = 0; i < m_DNA.size(); i++){
      dnaCount++;
      cout << "DNA " << dnaCount << endl;
      cout <<  *m_DNA[i];
    }
  }
  if (m_mRNA.size() > 0){
    for (unsigned int i = 0; i < m_mRNA.size(); i++){
      mrnaCount++;
      cout << "mRNA " << mrnaCount << endl;
      cout <<  *m_mRNA[i];
    }
  }
}


// Name: ReadFile
// Desc: Reads in a file of DNA strands that has the name on one line then
//       the sequence on the next
//       All sequences will be an indeterminate length (always evenly divisible by three though).
//       There are an indeterminate number of sequences in a file.
//       Hint: Read in the entire sequence into a string then go char
//       by char until you hit a new line break. Then insert to the m_DNA vector
// Preconditions: Valid file name of characters (Filled with a name and then A, T, G, or C)
// Postconditions: Populates each DNA strand and puts in m_DNA
void Sequencer::ReadFile(){
  ifstream myfile(m_fileName);
  string line;
  int count;
  if (myfile.is_open()){
    while(getline(myfile, line)){
      // Split the line into name and DNA sequence
      string name = line.substr(0, line.find(","));
      string sequence = line.substr(line.find(",") + 1);
      count++;

      // Create new DNA strand and add to m_DNA vector
      Strand* new_dna = new Strand(name);
      for (unsigned int i = 0; i  < sequence.size(); i++){
        if(sequence[i] == 'A' or sequence[i] == 'T' or sequence[i] == 'G' or sequence[i] == 'C'){
        new_dna -> InsertEnd(sequence[i]);
        }
      }
      m_DNA.push_back(new_dna);
    }
    myfile.close();//closes file
    cout << "Opened File" << endl;
    cout << count << " strands loaded" << endl;
  }else{
    cout << "Error! Unable to open file" << m_fileName << endl;
    return;
  }
}


// Name:  MainMenu
// Desc: Displays the main menu and manages exiting.
//       Returns 5 if the user chooses to quit, else returns 0
// Preconditions: m_DNA populated
// Postconditions: Indicates the user has quit the program
int Sequencer::MainMenu(){
  int choice;
  cout << "What would you like to do?:" << endl;
  cout << "1. Display Strands" << endl;
  cout << "2. Reverse Strand" << endl;
  cout << "3. Transcribe DNA to mRNA" << endl;
  cout << "4. Translate mRNA to Amino Acids" << endl;
  cout << "5. Exit" << endl;
  cin >> choice;
  return choice;
}

// Name: ChooseDNA
// Desc: Asks the user to choose one strand to use from loaded DNA strands
// Preconditions: Populated m_DNA
// Postconditions: Returns index of chosen strand
int Sequencer::ChooseDNA(){
  cout << "Choose a DNA strand: " << endl;
  for (unsigned int i = 0; i < m_DNA.size(); i++){
    cout << i + 1 << ". " << m_DNA[i] -> GetName() << endl;
  }
  int option;
  cin >> option;
  return option - 1;
}


// Name: ChooseMRNA
// Desc: Asks the user to choose one strand to use from translated mRNA strands
// Preconditions: Populated m_mRNA
// Postconditions: Returns index of chosen strand
int Sequencer::ChooseMRNA(){
  cout << "Choose a mRNA strand: " << endl;
  for (unsigned int i = 0; i < m_mRNA.size(); i++){
    cout << i + 1 << ". " << m_mRNA[i] -> GetName() << endl;
  }
  int option;
  cin >> option;
  return option - 1;
}


// Name: ReverseSequence
// Desc: User chooses to reverse either DNA or mRNA to reverse
//       Then calls either ChooseDNA or ChooseMRNA which returns index of strand
//       Calls ReverseStrand on chosen location
// Preconditions: Populated m_DNA or m_mRNA
// Postconditions: Reverses a specific strand replacing in place
void Sequencer::ReverseSequence(){
  int reverseInput = 0;
  long unsigned int dnaInput = 0;
  long unsigned int mRnaInput = 0;
  bool reverseFlag = true;
  bool dnaFlag = true;
  bool mRnaFlag = true;
  while(reverseFlag){
    cout << "Which type of strand would you like to reverse?" << endl;
    cout << "1. DNA" << endl;
    cout << "2. mRNA" << endl;
    cin >> reverseInput;

    if(reverseInput == 1){
      if(m_DNA.size() == 1){
        m_DNA[0]->ReverseSequence();
        cout << "Done reversing DNA strand." << endl;
        reverseFlag = false;
      }else{
        while(dnaFlag){
          cout << "Which strand to work with?" << endl;
          cout << "Choose 1 - " << m_DNA.size() << endl;
          cin >> dnaInput;
          if(dnaInput >= 1 || dnaInput <= m_DNA.size()){
            m_DNA[dnaInput-1]->ReverseSequence();
            cout << "Done reversing DNA " << dnaInput << "'s strand." <<endl;
            dnaFlag = false;
            reverseFlag = false;
          }
        }
      }
    }else if(reverseInput == 2){
      if(m_mRNA.size() == 1){
        m_mRNA[0]->ReverseSequence();
        cout << "Done reversing MRNA strand." << endl;
        reverseFlag = false;
      }else if(m_mRNA.size() == 0){
        cout << "No mRNA to reverse; transcribe first" << endl;
        return;
      }else{
        while(mRnaFlag){
          cout << "Which sequence to reverse?" << endl;
          cout << "Choose 1 - " << m_mRNA.size() << endl;
          cin >> mRnaInput;
          if(mRnaInput >= 1 || mRnaInput <= m_mRNA.size()){
            m_mRNA[mRnaInput-1]->ReverseSequence();
            cout << "Done reversing MRNA " << mRnaInput << "'s strand." <<endl;
            mRnaFlag = false;
            reverseFlag = false;
          }
        }
      }
    }
  }
}
              

// Name: Transcribe
// Desc: Iterates through each DNA strand in m_DNA to transcribe to m_mRNA
// A->U, T->A, C->G, G->C (DNA to mRNA)
// Can be called multiple times (will result in multiple mRNA strands)
// Puts the transcribed mRNA strand into m_mRNA
// Note: if this function is called more than once on the same strands of DNA,
// it will add duplicate strands into m_mRNA!
// Preconditions: Populated m_DNA
// Postconditions: Transcribes each strand of m_DNA to m_mRNA
void Sequencer::Transcribe(){
  int count = 0;
  for(unsigned int i = 0; i < m_DNA.size(); i++){
    string name = m_DNA[i]->GetName();
    Strand* newStrand = new Strand(name);
    for (int j = 0; j < m_DNA[i]->GetSize(); j++) {
      char nucleotide = m_DNA[i]->GetData(j + 1);
      switch(nucleotide){
        case 'A':
          newStrand -> InsertEnd('U');
          break;
        case 'T':
          newStrand->InsertEnd('A');
          break;
        case 'C':
          newStrand->InsertEnd('G');
          break;
        case 'G':
          newStrand->InsertEnd('C');
          break;
        default:
          break;
      }
    }
    m_mRNA.push_back(newStrand);
    count++;
  }
  cout << count << " strands of DNA succeesfully transcribed into new mRNA strands" << endl;
}
  

// Name: Translate
// Desc: Iterates through a chosen mRNA strand and converts to amino acids
// For every three nucleotides in strand, passes them three at a time to Convert
// Displays each amino acid but does not store the amino acids in the class
// Preconditions: Populated m_mRNA
// Postconditions: Translates a specific strand of mRNA to amino acids
void Sequencer::Translate(){
  if(m_mRNA.size() == 0){
    cout << "No mRNA to translate; transcribe first" << endl;
    return;
  }
  long unsigned int mrnaChoice = ChooseMRNA();
  if(mrnaChoice >= 0 && mrnaChoice < m_mRNA.size()){
    Strand* mrnaStrand = m_mRNA[mrnaChoice];
    string nucleotides;
    for (int i = 0; i < mrnaStrand->GetSize(); i++) {
      nucleotides += mrnaStrand->GetData(i+1);
      if((i + 1) % 3 == 0){
        string aminoAcid = Convert(nucleotides);
        cout << nucleotides << "->"<< aminoAcid << endl;
        nucleotides = "";
      }
    }
    cout << endl;
  }
}


// Name: Convert (Provided)
// Desc: Converts codon (three nodes) into an amino acid
// Preconditions: Passed exactly three U, A, G, or C
// Postconditions: Returns the string name of each amino acid
string Sequencer::Convert(const string trinucleotide){
  if((trinucleotide=="AUU")||(trinucleotide=="AUC")||(trinucleotide=="AUA"))
    return ("Isoleucine");
  else if((trinucleotide=="CUU")||(trinucleotide=="CUC")||(trinucleotide=="CUA")||
	  (trinucleotide=="CUG")|| (trinucleotide=="UUA")||(trinucleotide=="UUG"))
    return ("Leucine");
  else if((trinucleotide=="GUU")||(trinucleotide=="GUC")||
	  (trinucleotide=="GUA")||(trinucleotide=="GUG"))
    return ("Valine");
  else if((trinucleotide=="UUU")||(trinucleotide=="UUC"))
    return ("Phenylalanine");
  else if((trinucleotide=="AUG"))
    return ("Methionine (START)");
  else if((trinucleotide=="UGU")||(trinucleotide=="UGC"))
    return ("Cysteine");
  else if((trinucleotide=="GCU")||(trinucleotide=="GCC")||
	  (trinucleotide=="GCA")||(trinucleotide=="GCG"))
    return ("Alanine");
  else if((trinucleotide=="GGU")||(trinucleotide=="GGC")||
	  (trinucleotide=="GGA")||(trinucleotide=="GGG"))
    return ("Glycine");
  else if((trinucleotide=="CCU")||(trinucleotide=="CCC")||
	  (trinucleotide=="CCA")||(trinucleotide=="CCG"))
    return ("Proline");
  else if((trinucleotide=="ACU")||(trinucleotide=="ACC")||
	  (trinucleotide=="ACA")||(trinucleotide=="ACG"))
    return ("Threonine");
  else if((trinucleotide=="UCU")||(trinucleotide=="UCC")||
	  (trinucleotide=="UCA")||(trinucleotide=="UCG")||
	  (trinucleotide=="AGU")||(trinucleotide=="AGC"))
    return ("Serine");
  else if((trinucleotide=="UAU")||(trinucleotide=="UAC"))
    return ("Tyrosine");
  else if((trinucleotide=="UGG"))
    return ("Tryptophan");
  else if((trinucleotide=="CAA")||(trinucleotide=="CAG"))
    return ("Glutamine");
  else if((trinucleotide=="AAU")||(trinucleotide=="AAC"))
    return ("Asparagine");
  else if((trinucleotide=="CAU")||(trinucleotide=="CAC"))
    return ("Histidine");
  else if((trinucleotide=="GAA")||(trinucleotide=="GAG"))
    return ("Glutamic acid");
  else if((trinucleotide=="GAU")||(trinucleotide=="GAC"))
    return ("Aspartic acid");
  else if((trinucleotide=="AAA")||(trinucleotide=="AAG"))
    return ("Lysine");
  else if((trinucleotide=="CGU")||(trinucleotide=="CGC")||(trinucleotide=="CGA")||
	  (trinucleotide=="CGG")||(trinucleotide=="AGA")||(trinucleotide=="AGG"))
    return ("Arginine");
  else if((trinucleotide=="UAA")||(trinucleotide=="UAG")||(trinucleotide=="UGA"))
    return ("Stop");
  else
    cout << "returning unknown" << endl;
  return ("Unknown");
}
