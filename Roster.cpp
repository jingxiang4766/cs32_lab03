#include "Roster.h"

#include <cstdlib>
#include <fstream>
#include <cassert>

Roster::Roster() {
  // initialize to empty array

  this->numStudents = 0;
  for (int i=0; i<ROSTER_MAX; i++) {
    this->students[i] = NULL;
  }

}

void Roster::resetRoster() {
 // To avoid memory leaks:
  //  Recycle memory for all allocated students on roster
  
  while (this->numStudents > 0) {
    delete this->students[this->numStudents - 1];
    this->numStudents --;
  }

}

void Roster::addStudentsFromFile(std::string filename) {
  std::ifstream ifs; // the stream we will use for the input file
  ifs.open(filename);
  
  if (ifs.fail()) {
    std::cerr << "Could not open input file: "
	      << filename << std::endl;
    exit(2); 
  }

  // ifs is an instance of ifstream
  // ifstream inherits from istream, 
  //   i.e. ifs is-a istream

  this->addStudentsFromStream(ifs);

}

void Roster::addStudentsFromStream(std::istream &is) {

  this->resetRoster();

  std::string thisLine;
  // Try to read past the header line.
  getline(is,thisLine);
  if ( is.eof() || is.fail() ) {
    std::cerr << "Unable to read first line of input stream" << std::endl;
    exit(3);
  }

  getline(is,thisLine);
  while (  !is.eof() && !is.fail() ) {
    // If we get here, it means the most recent attempt to read succeeded!
    // So do something with thisLine
    
    Student *sPtr = new Student(thisLine);
    this->students[this->numStudents] = sPtr;
    this->numStudents++;
    
    // try to read another line
    getline(is,thisLine);
  } // end while

}

int Roster::getNumStudents() const { 
  return this->numStudents;
}

Student Roster::getStudentAt(int index) const { 
  return Student(this->students[index]->getPerm(),this->students[index]->getLastName(),this->students[index]->getFirstAndMiddleNames()); 
}

std::string Roster::toString() const {
  std::string result = "{\n";
  if (numStudents == 0){
	  result += "}";
	  return result;
  }
  for (int i = 0; i < numStudents; i++){ 
  /*
  result += "[";
  result += getStudentAt(i).getPerm();
  result += ",";
  result += getStudentAt(i).getLastName();
  result += ",";
  result += getStudentAt(i).getFirstAndMiddleNames();
  result += "],\n";
  */
  result += getStudentAt(i).toString();

  if (i < numStudents-1)
  result += ",\n";
  else result += "\n";

  }
  result += "}\n";
  return result;

}

void Roster::sortByPerm() {
  // SELECTION SORT
  for (int i = numStudents; i > 0; i--){
	sortByPermHelper(i);
/*
	  maxIndex = 0;
	  maxPerm = getStudentAt(i).getPerm();
	  for (int j = 0; j < i; j++){
		if (getStudentAt(j).getPerm()  > maxPerm){
			maxPerm = getStudentAt(j).getPerm();
			maxIndex = j;
		}
          }
*/
  }
}

int Roster::indexOfMaxPermAmongFirstKStudents(int k) const {
  int maxIndex(0), maxPerm(getStudentAt(0).getPerm());
  for (int i = 0; i < k; i++){
	if (getStudentAt(i).getPerm() > maxPerm){
		maxIndex = i;
		maxPerm = getStudentAt(i).getPerm();
	}
  }
  return maxIndex;
}

void Roster::sortByPermHelper(int k) {
  // swaps max perm from [0..k-1] with elem [k-1]

  int im = indexOfMaxPermAmongFirstKStudents(k);
  Student* temp = students[im];
  this->students[im] = this->students[k-1];
  this->students[k-1] = temp;
  
  
  // now swap the pointers between index im and index k-1
  
  // THIS IS STILL A STUB !!!
  
}
