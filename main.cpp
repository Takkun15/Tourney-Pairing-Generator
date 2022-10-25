#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

class Player {
  public:
    string name;
    int win, loss, tie, points;
    float bounty;

    Player(string name, int win, int loss, int tie, int points, float bounty) {
      this->name = name;
      this->win = win;
      this->loss = loss;
      this->tie = tie;
      this->points = points;
      this->bounty = bounty;
    }
};

priority_queue<Player> ranking;
int current_round, total_rounds;

bool operator<(Player const& p1, Player const& p2) {
  return ((p1.points == p2.points) ? (p1.bounty < p2.bounty) :(p1.points < p2.points));
}

void load_data(char* fileName) {
  ifstream myFile(fileName);
  if(myFile.fail()) { throw invalid_argument("Error: specified files does not exist"); }

  string line;
  getline(myFile, line);
  istringstream ss(line);
  string current, total;
  getline(ss, current, ',');
  getline(ss, total, ',');
  current_round = stoi(current);
  total_rounds = stoi(total);
  
  while(getline(myFile, line)) {
    istringstream ss(line);
    string name, win, loss, tie, points, bounty;
    getline(ss, name, ',');
    getline(ss, win, ',');
    getline(ss, loss, ',');
    getline(ss, tie, ',');
    getline(ss, points, ',');
    getline(ss, bounty, ',');
    ranking.push(Player(name, stoi(win), stoi(loss), stoi(tie), stoi(points), stof(bounty)));
  }
  myFile.close();
}

vector<pair<Player, Player>> get_pairings(priority_queue<Player> pq, string *bye) {
  vector<pair<Player, Player>> pairings;
  while(!pq.empty()) {
    if(pq.size() > 1) {
      Player p1 = pq.top();
      pq.pop();
      pairings.push_back(make_pair(p1, pq.top()));
      pq.pop();
    }
    else {
      *bye = pq.top().name;
      pq.pop();
    }
  }
  return pairings;
}

void print_pairings(vector<pair<Player, Player>> pairings, string bye) {
  cout << endl << "Pairings for round " << current_round << ':' << endl;
  int table = 1;
  for(pair<Player, Player> p: pairings) {
    cout << "Table " << table++ << ": " << p.first.name << " vs " << p.second.name << endl;
  }
  cout << bye << " has a bye this round\n";
}

void print_ranks(priority_queue<Player> pq) {
  cout << endl << "Rankings after round " << current_round << ":\n";
  int rank = 1;
  while(!pq.empty()) {
    Player p = pq.top();
    cout << "Rank " << rank++ << ": " << p.name << " (" << p.win << "-" << p.loss << "-" << p.tie << ") Points: " << p.points << " Bounty: " << p.bounty << endl;
    pq.pop();
  }
}

void get_winner(vector<pair<Player, Player>> pairings) {
  cout << "Who won out of the following pairs?\n" << "Enter '1' for player 1, '2' for player 2, '3' for tie\n";
  for(pair<Player, Player> p: pairings) {
    int win = 0;
    cout << "1. " << p.first.name << " 2. " << p.second.name << endl;
    cin >> win;
    if(win == 1) {
      p.first.win++;
      p.second.loss++;
      p.first.points += 2;
      p.first.bounty += p.second.bounty;
    }
    else if(win == 2) {
      p.first.loss++;
      p.second.win++;
      p.second.points += 2;
      p.second.bounty += p.first.bounty;
    }
    else {
      p.first.tie++;
      p.second.tie++;
      p.first.points++;
      p.second.points++;
      p.first.bounty += p.second.bounty/2;
      p.second.bounty += p.first.bounty/2;
    }
  }
  priority_queue<Player> temp = ranking;
  ranking = priority_queue<Player>();
  while(!temp.empty()) {
    ranking.push(temp.top());
    temp.pop();
  }
}

void run_tourney() {
  while(current_round <= total_rounds) {
    string input = "";
    cout << endl << "To begin pairing, enter 'pair'\n";
    while(input != "pair") {
      cin >> input;
    }
    string bye;
    vector<pair<Player, Player>> pairings = get_pairings(ranking, &bye);
    print_pairings(pairings, bye);
    cout << endl << "When the current round has concluded, enter '.'\n";
    while(input != ".") {
      cin >> input;
    }
    get_winner(pairings);
    print_ranks(ranking);
    current_round++;
  }
}

int main(int argc, char** argv) {
  cout << "YGO Pairing System 0.0.1\n";
  cout << "Reading in data from " << argv[1] << endl;
  cout << "To begin, enter 'b'\n";
  string input = "";
  while(input != "b") {
    cin >> input;
  }

  load_data(argv[1]);
  run_tourney();

  return 0;
}