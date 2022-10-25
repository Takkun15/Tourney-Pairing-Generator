# Tourney-Pairing-Generator
A program to generate round pairings for Yu-Gi-Oh! tournaments. Uses the Swiss tournament system and can be applied to other TCGs.
Data will be saved at the end of each round to the original csv file to prevent accidental data loss.


##Required Files
A csv file under the following format must be included in the same directory as the main executable program

```
Current Round Number, Total Rounds
Player 1 name, wins, loss, ties, bounty
Player 2 name, wins, loss, ties, bounty
Player 3...
```


## Usage
Startup command:

```
./main.exe tourney.csv
```

Immediately after program runs: enter "b" to begin
Before each round of the tournament: enter "pair" to generate the pairings for that round
After each round of the tournament: enter "." to run the result input prompt
During the result input prompt: enter 1, 2, or 3 to record win for the 1st player, 2nd player, or tie for the displayed match-up


## Troubleshooting & FAQ
- The program has crashed/stopped running mid-tournmanet. What do I do?

  Run the program again with the same csv file as the input file. All the previous data should be saved at the end of each round and they loaded automatically upon the next startup of the program.
  
 - The program gives and error of 'std::invalid_argument'.

  Unfortunately the input file is under the csv file format, where commas are used to denote end of each data cell. As a result, commas are not supported by the program and must not be included in the csv file outside of its intended function.
