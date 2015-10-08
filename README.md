SAT Solver
--------------------

Basic program to demonstrate three common algorithms used in satisfiability testing.

### WalkSAT

WalkSAT starts with a randomly generated candidate, which is then checked against the
given clauses. A randomly failed claused is then selected, along with a chosen
variable. This variable is then flipped, and the tests are ran again. The variable
is chosen so that the new candidate has the least previously satisfied clauses
turn unsatisfied.

### Genetic

The Genetic Algorithm starts with a pool of candidates. A scoreboard is created to 
represent the 'fitness' of each candidate. The 90th percentile of all candidates
is found, and everything with a lower level of fitness is culled. The population
is then refilled with mutated versions of the surviving members. This process
is repeated until a perfect candidate is found. 

