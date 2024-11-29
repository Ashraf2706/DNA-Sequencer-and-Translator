
# UMBC DNA Sequencer and Translator

## Overview
This project implements a DNA sequencer and translator in C++. It allows the user to read DNA sequences from a file, display the sequences, reverse sequences, transcribe DNA to mRNA, and translate mRNA into amino acids. The program utilizes a linked-list structure to represent DNA and mRNA strands, enabling dynamic manipulation and efficient memory management.

## Features
1. **DNA Sequencing**:
   - Reads DNA sequences from a file.
   - Displays DNA strands with arrows between nucleotides.
   - Supports reversing DNA sequences.

2. **Transcription**:
   - Converts DNA to mRNA by applying specific nucleotide mappings (e.g., A -> U, T -> A, G -> C, C -> G).

3. **Translation**:
   - Converts mRNA sequences into amino acids by mapping codons (three nucleotides) to their respective amino acids.

4. **Linked-List Representation**:
   - DNA and mRNA strands are represented using a linked-list structure, allowing dynamic memory allocation and flexibility.

5. **Menu-Driven Interface**:
   - A simple console-based interface guides the user through sequencing, transcription, and translation operations.

## Files
### Source Files
- **`Strand.cpp` & `Strand.h`**:
  - Implements the `Strand` class for managing linked lists representing DNA and mRNA strands.
- **`Sequencer.cpp` & `Sequencer.h`**:
  - Implements the `Sequencer` class for managing DNA and mRNA sequences, transcription, and translation operations.
- **`proj3_data2.txt`**:
  - Example input file containing DNA sequences.

## Installation
1. **Ensure all files are in the same directory**.
2. Compile the application using a C++ compiler:
   ```bash
   g++ -o dna_sequencer Strand.cpp Sequencer.cpp
   ```
3. Run the application:
   ```bash
   ./dna_sequencer proj3_data2.txt
   ```

## How to Use
### Input File Format
- DNA sequences should be stored in a text file with each line containing:
  - **Name**: The name of the DNA strand.
  - **Sequence**: The DNA sequence.
- Example (`proj3_data2.txt`):
  ```
  Artic Fox,T,A,C,C,T,A,C,T,T,A,C,G,A,T,G,T,G,T,A,G,C,A,C,A,T,C,T,G,G,A,T,G,C,T,C,C,T,T,C,T,A,C,G,C,G,G,T,A,A,T,A,T,C,C,T,G,T,G,G,A,T,G,G,A,C,G,G,A,G,C,T,A,C,C,G,C,T,T,T,C,T,T,G,C,G,G,A,G,G,T,G,A,T,C,A,C,C,T,G,A,C,T
  ```

### Menu Options
- **Main Menu**:
  - `1. Display Strands`: Displays all DNA and mRNA strands with their names and nucleotide sequences.
  - `2. Reverse Strand`: Reverses a selected DNA or mRNA strand.
  - `3. Transcribe DNA to mRNA`: Transcribes all DNA strands into mRNA strands.
  - `4. Translate mRNA to Amino Acids`: Translates a selected mRNA strand into its corresponding amino acids.
  - `5. Exit`: Exits the program.

### Example Output
- **DNA Strand Display**:
  ```
  ***Artic Fox***
  T->A->C->C->...->END
  ```
- **Transcription**:
  ```
  Transcribing DNA strand "Artic Fox"...
  1 strands of DNA successfully transcribed into new mRNA strands.
  ```
- **Translation**:
  ```
  UCU->Serine
  GCC->Alanine
  AUG->Methionine (START)
  ```

## Classes and Functions
### `Strand`
- **Description**: Represents a linked list for DNA or mRNA strands.
- **Key Methods**:
  - `InsertEnd(char data)`: Adds a nucleotide to the end of the strand.
  - `ReverseSequence()`: Reverses the strand in place.
  - `GetData(int nodeNum)`: Retrieves the nucleotide at a specified position.
  - `operator<<`: Overloads the `<<` operator for displaying strands.

### `Sequencer`
- **Description**: Manages DNA and mRNA strands, transcription, and translation.
- **Key Methods**:
  - `StartSequencing()`: Reads DNA strands from a file and processes user inputs.
  - `ReadFile()`: Reads DNA sequences from a file and stores them in the program.
  - `Transcribe()`: Converts DNA strands to mRNA strands.
  - `Translate()`: Converts mRNA strands to amino acids.
  - `Convert(string codon)`: Maps a codon (three nucleotides) to an amino acid.

## Dependencies
- Standard C++ libraries:
  - `<iostream>`
  - `<fstream>`
  - `<string>`
  - `<vector>`
  - `<cstdlib>`

## Notes
- DNA strands are read from the input file and must only contain valid nucleotides (A, T, G, C).
- mRNA transcription maps DNA nucleotides as follows:
  - A -> U
  - T -> A
  - C -> G
  - G -> C
- Translated amino acids are based on standard codon mappings.

## Author
- **Ashraf Kawooya**
- **Date**: 3/14/2023
- **Course**: CMSC 202, UMBC

## License
This project is for educational purposes and does not include any warranty or guarantee.
