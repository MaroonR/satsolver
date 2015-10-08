// main.cpp


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

void walksat(vector<vector<int>>, int);
vector<vector<bool>> genetic_init(vector<vector<int>>, int);
vector<vector<bool>> genetic(vector<vector<int>>, int, vector<vector<bool>>);
bool getSat(vector<int>, vector<bool>);
vector<bool> mutate(vector<bool>);

void print_vector(vector<bool> x){
  for(int i = 0; i < x.size(); i++){
    cout << "[" << x[i] << "] ";
  }
  cout << endl;
}
int main(){

  ifstream infile("tests/10.40.160707067.cnf");
  string line;

  int count = 0;
  int var_count = 0;
  int line_count = 1000000;

  // put all the clauses in a vector so that
  // they can be easily accessed later

  vector<vector<int>> clauses;
  vector<int> variables;
  while(getline(infile, line))
  {
    istringstream iss(line);
    string a, b;
    cout << "Reading line: " << line << endl;
    int param1, param2, param3;
    if (count == 0){
      cout << "Got CNF parameters" << endl;
      iss >> a >> b >> param1 >> param2;
      var_count = param1;
      line_count = param2;
    }
    else if (count > line_count){
      cout << "Finished reading lines, no more pushes will be made" << endl;
      break;
    }
    else{
      cout << "Pushing clause into vector" << endl;
      iss >> param1 >> param2 >> param3 >> a;
      variables.push_back(param1);
      variables.push_back(param2);
      variables.push_back(param3);
      clauses.push_back(variables);
      variables.clear();
    }
    count++;
  }

  //run formulas here
  walksat(clauses, var_count);
  return 0;
}


vector<bool> mutate(vector<bool> candidate){
  int num_of_mutations = rand() % 10 + 1; //only 10 possible slots to mutate
  int mutated_pos;
  vector<bool> mutant = candidate;
  vector<bool> mutated_positions;
  for(int i = 0; i < 10; i++){
    mutated_positions.push_back(0);  //set all values to unmutated
  }
  for (int i = 0; i < num_of_mutations; i++){
    mutated_pos = rand() % 10;
    while(mutated_positions[mutated_pos] == 1){
      mutated_pos = rand() % 10;   // try again
    }
    mutant[mutated_pos] = !mutant[mutated_pos];
    mutated_positions[mutated_pos] = 1;
  }
  return mutant;
}


void walksat(vector<vector<int>> clauses, int vars){

  //start with a random truth assignment for the 10 variables
  vector<bool> candidate;
  srand(time(NULL));
  for(int i = 0; i < vars; i++){
    candidate.push_back(rand() % 2);
  }
  cout << "Candidate Vector: " << endl;
  print_vector(candidate);

  //check candidate against the CNFs
  vector<bool> failed_cnf;
  for(int i = 0; i < clauses.size(); i++){
    failed_cnf.push_back(0);
  }

  //iterate through clauses
  for(int i = 0; i < clauses.size(); i++){
    if(getSat(clauses[i], candidate) == 1){
      failed_cnf[i] = 1;
    }
  }

  int flippos = 0;
  int temp = -1;
  int flipvar = 0;
  bool solnflag = 0;
  //failed_cnf now loaded with results from sat tests
  while(1){
    solnflag = 1;
    // find a failed cnf and flip a variable from that clause
    flippos = rand() % 10;
    while(flippos != temp && failed_cnf[abs(flippos)] != 0){
      // choose a clause
      flippos = rand() % 11;

    }
    temp = flippos;
    // choose a variable
    flipvar = rand() % 3;
    cout << "Flipping Variable from clause: " << flippos << endl;
    cout << "Flipping variable at clause[" <<flipvar<< "]" << endl;

    //////////     clauses:::clause:::variable  //// do the flip
    candidate[abs(clauses[flippos][flipvar])-1] = !candidate[abs(clauses[flippos][flipvar])-1];
    cout << "Changing variable " << abs(clauses[flippos][flipvar]);
    cout << " to: " << candidate[abs(clauses[flippos][flipvar])-1] << endl;
    cout << "New Candidate Created: " << endl;
    print_vector(candidate);

    //restart test, reset failed cnfs
    failed_cnf.clear();
    for(int i = 0; i < vars; i++){
      failed_cnf.push_back(0);
    }
    for(int i = 0; i < clauses.size(); i++){
      if(getSat(clauses[i], candidate) == 1){
        failed_cnf[i] = 1;
      }
    }
    cout << "Failed tests: ";
    for(int i = 0; i < failed_cnf.size(); i++){
      if(failed_cnf[i] == 0){
        solnflag = 0;
        cout << i;
      }
    }
    cout << endl;
    if(solnflag == 1){
      cout << "WalkSAT uncovered a solution!!" << endl;
      for(int i = 0; i < candidate.size(); i++){
        cout << "[" << candidate[i] << "] ";
      }
      cout << endl;
      break;
    }
  }

}



bool getSat(vector<int> clause, vector<bool> candidate){
  // need to extract values from candidate at positions denoted by clause
  // also need to figure out correct logic statement based on negatives

  int pos1 = clause[0];
  int pos2 = clause[1];
  int pos3 = clause[2];

  bool vX = candidate[abs(pos1)];
  bool vY = candidate[abs(pos2)];
  bool vZ = candidate[abs(pos3)];

  if(pos1 < 0){
    vX = !vX;
  }
  if(pos2 < 0){
    vY = !vY;
  }
  if(pos3 < 0){
    vZ = !vZ;
  }

  bool result = vX && vY && vZ;

  return result;
}

// vector<vector<bool>> genetic_rec(vector<vector<int>> cl, int vars){
//
//   //solution/most fit candidate variable
//   vector<bool> winner;
//
//   // create a random sampling of candidate solutions
//   vector<bool> candidate;
//   vector<vector<bool>> candidates;
//
//   // create candidates pool
//   cout << "Creating candidates" << endl;
//   srand(time(NULL));
//   for(int i = 0; i < 200; i++){
//     for(int j = 0; j < vars; j++){
//       candidate.push_back(rand() % 2);
//     }
//     candidates.push_back(candidate);
//     candidate.clear();
//   }
//
//   // some debug statements
//   cout << "Here's the pool so far..." << endl;
//   for(int i = 0; i < candidates.size(); i++){
//     for (int j = 0; j < 10; j++){
//       cout << "[" << candidates[i][j] << "] ";
//     }
//     cout << endl;
//   }
//   cout << candidates.size() << endl;
//
//   // set up a scoreboard for our 200 candidates, with starting score = 0
//   cout << "Creating scoreboard" << endl;
//   vector<int> scores;
//   for(int i = 0; i < 200; i++){
//     scores.push_back(0);
//   }
//   // send our candidates off to prove themselves, track scores
//   cout << "Rating Candidates... " << endl;
//   // iterate through candidates
//   for(int i = 0; i < 200; i++){
//     // iterate throuhg clauses
//     for(int j = 0; j < 40; j++){
//       // Does the current candidate validate the current clause?
//       if(getSat(clauses[j], candidates[i]) == 1){
//         scores[i] = scores[i] + 1;
//       }
//     }
//     // In the event that we find a best-possible candidate, we'll immediately
//     // print this and return the current set of candidates.
//     if(scores[i] == 40){
//       cout << "found a solution" << endl;
//       for(int j = 0; j < 10; j++){
//         cout << "[" << candidates[i][j] << "] ";
//       }
//       cout << endl;
//       return candidates;
//     }
//   }
//   // find the top quartile candidates
//   vector<int> sorted_scores = scores;
//   sort(sorted_scores.begin(), sorted_scores.end());
//   //size of scores is 200, and median value lies between indicies 150 and 151
//   double topq_score = (sorted_scores[150] + sorted_scores[151])/2;
//
//   // let natural selection run its course >:D
//   vector<int> ns;
//   for(int i = 0; i < 200; i++){
//     if(scores[i] < topq_score){
//       ns.push_back(i);
//     }
//   }
//   for(int i = 0; i < ns.size(); i++){
//     scores[ns[i]] = -999;
//     }
//
//
//   vector<vector<bool>> newgen_cands;
//   cout << "Here are our leading candidates" << endl;
//   int newcount = 0;
//   // print out our top candidates (debug)
//   for(int i = 0; i < candidates.size(); i++){
//     for (int j = 0; j < 10; j++){
//       if(scores[i] != -999)
//       cout << "[" << candidates[i][j] << "] ";
//
//     }
//     if(scores[i] != -999){
//       newgen_cands.push_back(candidates[i]);
//       cout << scores[i] << endl;
//       newcount++;
//     }
//   }
//   cout << "Total of " << newcount <<  " candidates" << endl;
//
//   //get number of needed new candidates (mutants to-be)
//   int needed_candidates = 200 - newgen_cands.size();
//
//   // how to decide which candidates are mutated... for now it'll just be
//   // random, in the way that we'll cycle through newgen_cands until we have
//   // enough candidates
//   int count1 = 0;  //we have so many counts right now
//   while(newgen_cands.size() < 200){
//     newgen_cands.push_back(mutate(newgen_cands[count1]));
//   }
//
//   cout << "Here's the pool so far..." << endl;
//   for(int i = 0; i < newgen_cands.size(); i++){
//     for (int j = 0; j < 10; j++){
//       cout << "[" << newgen_cands[i][j] << "] ";
//     }
//     cout << endl;
//   }
//   cout << newgen_cands.size() << endl;
//   cout << "wtf" << endl;
//
//
//
//
// }
