// main.cpp


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

double genetic(vector<vector<int>>, int);

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
  genetic(clauses, var_count);
}

double genetic(vector<vector<int>> cl, int vars){

  // create a random sampling of candidate solutions
  vector<bool> candidate;
  vector<vector<bool>> candidates;

  // set up a scoreboard for 200 candidates
  cout << "Creating scoreboard" << endl;
  vector<int> scores;
  for(int i = 0; i < 200; i++){
    scores.push_back(0);
  }

  // create candidates
  cout << "Creating candidates" << endl;
  srand(time(NULL));
  for(int i = 0; i < 200; i++){
    for(int j = 0; j < vars; j++){
      candidate.push_back(rand() % 2);
    }
    candidates.push_back(candidate);
    candidate.clear();
  }
  // send our candidates off to prove themselves, track scores
  cout << "Rating Candidates... " << endl;
  for(int i = 0; i < 200; i++){
    for(int j = 0; j < 40; j++){
      for(int k = 0; k < 3; k++){
        cout << i << endl;
        cout << j << endl;
        cout << k << endl;
        cout << "next" << endl;
        if(candidates[i][cl[j][k]] == 1){
          scores[i] = scores[i] + 1;
        }
        else{
          scores[i] = scores[i];
        }
      }
    }
  }
}
