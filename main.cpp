// main.cpp


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

double genetic(vector<vector<int>>, int);
bool getSat(vector<vector<int>>, vector<vector<bool>>);

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


  /*THIS SECTION STILL NEEDS WORK!!!*/
  cout << "Rating Candidates... " << endl;
  for(int i = 0; i < 200; i++){
    for(int j = 0; j < 40; j++){
      if(getSat(cl[j], candidates[i]) == 1){
        scores[i] = scores[i] + 1;
      }
      else{
        scores[i] = scores[i];
      }
    }
    if(score[i] == 40){
      cout << "found a solution" << endl;

    }
  }

  // find the top quartile of our scores....
  double top_q = 0;
  for(int i = 0; i < 200; i++){
    if(scores[i] > top_q){
      top_q = scores[i];
    }
  }
  top_q = (3 * top_q)/4;

  // let natural selection run its course
  vector<int> ns;
  for(int i = 0; i < 200; i++){
    if(scores[i] < top_q){
      ns.push_back(i);
    }
  }
  for(int i = 0; i < ns.size(); i++){
    scores[ns[i]] = -999;
    candidates[ns[i]].clear();
  }

  // mutate the top candidates


}
