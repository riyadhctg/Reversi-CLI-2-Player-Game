// youI.cpp : Defines the entry point for the console application.

// Developed by Riyadh Sharif 
// Utilized open source project by Grant Slatton
// All code is released to the public domain under the terms of [http://unlicense.org]

// Puzzle Solution for You.i Labs

#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <vector>
#include <utility>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Returns routes (direction and cooridnates)
vector< pair<int, int> > get_route(int reversi_board[][8], int x, int y, int pawn);

// Returns available steps
vector< pair<int, vector< pair<int, int> > > > get_steps(int reversi_board[][8], int pawn);

// Executes the step and flips the pawn
void make_move(int reversi_board[][8], int x, int y, int pawn, vector< pair<int, int> > routes);

// Prints Board UI in Console
void reversi_ui(int reversi_board[][8]);

// Returns Score
int score(int reversi_board[][8], int pawn);

// MAIN
int main() {

	int reversi_board[8][8];

	memset(reversi_board, 0, sizeof(reversi_board));

	reversi_board[3][3] = reversi_board[4][4] = -1;
	reversi_board[3][4] = reversi_board[4][3] = 1;

	int player_switch = -1;
	bool instructionOn = true;

	while(true) {

		reversi_ui(reversi_board);
		
		vector< pair<int, vector< pair<int, int> > > > steps= get_steps(reversi_board, player_switch);
		
		cout << "Valid steps: ";

		for(auto it=steps.begin(); it != steps.end(); it++){
			cout << " (" << (*it).first/8 << "," << (*it).first%8 << ") ";
		}

		cout << endl;

		if (instructionOn == true)
		{
			cout << "Instruction: Type in X value, put a gap, and type in Y value. Example: 2 4" << endl;
			instructionOn = false;
		}
		if(steps.size() == 0) {
			player_switch = -player_switch;
			steps = get_steps(reversi_board, player_switch);

			if(steps.size() == 0) {
				cout << "final score: " << score(reversi_board, -1) << endl;
				return 0;
			}
		} 

		else {
			int x, y;

			if(player_switch == -1) {
				cout << "Player 1: ";
				
				scanf("%d %d", &x, &y);

				for(auto it=steps.begin(); it != steps.end(); it++) {

					auto last_it = steps.end();

					if(x*8+y == ((*it).first)) {
						cout << "Executed move: " << x << "," << y << endl;
						make_move(reversi_board, x, y, player_switch, (*it).second);
						player_switch = -player_switch;
						break;
					}	

					if (x*8+y != ((*it).first)) 
					{
						if (it == --last_it)
						{
							cout << "Invalid step! Please try again." << endl;
							break;
						}
					}
					
				} 
			} 

			else if (player_switch == 1) {
				cout << "Player 2: ";
				scanf("%d %d", &x, &y);
				for(auto it=steps.begin(); it != steps.end(); it++) {
					
					auto last_it = steps.end();
					
					if(x*8+y == ((*it).first)) {
						cout << "Executed move: " << x << "," << y << endl;
						make_move(reversi_board, x, y, player_switch, (*it).second);
						player_switch = -player_switch;
						break;
					}

					if (x*8+y != ((*it).first)) 
					{
						if (it == --last_it)
						{
							cout << "Invalid step! Please try again." << endl;
							break;
						}
					}
					
				}


			}
		}
	}
	return 0;
}
//------//


// Returns routes (direction and cooridnates)
vector< pair<int, int> > get_route(int reversi_board[][8], int x, int y, int pawn) {
	vector< pair<int, int> > routes;
	if(reversi_board[x][y]) {
		return routes;
	}

	if((y < 6) && (reversi_board[x][y+1] == -pawn)) {
			
		for(int i=y+2; i < 8; i++) {
			if(!reversi_board[x][i]) {
				break;
			} else if(reversi_board[x][i] == pawn) {
				routes.push_back(make_pair<int, int>(0, x*8+i));
				break;
			}
		}

	}

	if((y < 6) && (x < 6) && (reversi_board[x+1][y+1] == -pawn)) {
		
		for(int i=0; (x+i+2 < 8) && (y+i+2 < 8); i++) {
			if(!reversi_board[x+i+2][y+i+2]) {
				break;
			} else if(reversi_board[x+i+2][y+i+2] == pawn) {
				routes.push_back(make_pair<int, int>(1, (x+i+2)*8+(y+i+2)));
				break;
			}
		}
	}

	if((y < 6) && (x > 1) && (reversi_board[x-1][y+1] == -pawn)) {
		
		for(int i=0; (x-i-2 >= 0) && (y+i+2 < 8); i++) {
			
			if(!reversi_board[x-i-2][y+i+2]) {
				break;
			} else if(reversi_board[x-i-2][y+i+2] == pawn) {
				routes.push_back(make_pair<int, int>(7, (x-i-2)*8+(y+i+2)));
				break;
			}
		}
	}

	if((x < 6) && (reversi_board[x+1][y] == -pawn)) {
		for(int i=x+2; i < 8; i++) {
			if(!reversi_board[i][y]) {
				break;
			} else if(reversi_board[i][y] == pawn) {
				routes.push_back(make_pair<int, int>(2, i*8+y));
				break;
			}
		}
	}

	if((y > 1) && (x < 6) && (reversi_board[x+1][y-1] == -pawn)) {
		for(int i=0; (x+i+2 < 8) && (y-i-2 >= 0); i++) {
			if(!reversi_board[x+i+2][y-i-2]) {
				break;
			} else if(reversi_board[x+i+2][y-i-2] == pawn) {
				routes.push_back(make_pair<int, int>(3, (x+i+2)*8+(y-i-2)));
				break;
			}
		}
	}

	if((y > 1) && (reversi_board[x][y-1] == -pawn)) {
		for(int i=y-2; i >= 0; i--) {
			if(!reversi_board[x][i]) {
				break;
			} else if(reversi_board[x][i] == pawn) {
				routes.push_back(make_pair<int, int>(4, x*8+i));
				break;
			}
		}
	}

	if((y > 1) && (x > 1) && (reversi_board[x-1][y-1] == -pawn)) {
		for(int i=0; (x-i-2 >= 0) && (y-i-2 >= 0); i++) {
			if(!reversi_board[x-i-2][y-i-2]) {
				break;
			} else if(reversi_board[x-i-2][y-i-2] == pawn) {
				routes.push_back(make_pair<int, int>(5, (x-i-2)*8+(y-i-2)));
				break;
			}
		}
	}

	if((x > 1) && (reversi_board[x-1][y] == -pawn)) {
		for(int i=x-2; i >= 0; i--) {
			if(!reversi_board[i][y]) {
				break;
			} else if(reversi_board[i][y] == pawn) {
				routes.push_back(make_pair<int, int>(6, i*8+y));
				break;
			}
		}
	}
	return routes;
}
//---End of Function get_route----//

// Generates all steps for a player on the current Reversi board
vector< pair<int, vector< pair<int, int> > > > get_steps(int reversi_board[][8], int pawn) {
	
	vector< pair<int, vector< pair<int, int> > > > steps;
	
	for(int i=0; i < 8; i++) {
		for(int j=0; j < 8; j++) {
			steps.push_back(make_pair<int, vector< pair<int, int> > >(i*8+j, get_route(reversi_board, i, j, pawn)));
			if(!steps.back().second.size()) {
				steps.pop_back();
			}
		}
	}
	
	return steps;
}
//---End of Function get_steps----//

// Executes the step and flips the pawn
void make_move(int reversi_board[][8], int x, int y, int pawn, vector< pair<int, int> > routes) {

	for(auto it=routes.begin(); it != routes.end(); it++) {
		int i = x;
		int j = y;

		while((i != ((*it).second/8)) || (j != ((*it).second&7))) {
			
			reversi_board[i][j] = pawn;
			if(i < ((*it).second/8)) {
				i++;
			} else if((i > (*it).second/8)) {
				i--;
			}
			if(j < ((*it).second&7)) {
				j++;
			} else if(j > ((*it).second&7)) {
				j--;
			}
		}
	}
}
//---End of Function make_move----//

// Prints Board UI in Console
void reversi_ui(int reversi_board[][8]) {
	
	for(int i=7; i >= 0; i--) {
		
		cout << i << " ";
		for(int j=0; j < 8; j++) {
			if(!reversi_board[j][i]) {
				cout << " - " ;
			} else if(reversi_board[j][i] == 1) {
				cout << " O ";
			} else {
				cout << " X ";
			}
		}
		
		cout << endl;
	}
	
	cout << "  ";
	
	for(int i=0; i < 8; i++) {
		cout << " " << i << " ";
	}
	
	cout << endl << endl;
}
//---End of Function reversi_ui----//

// Returns final score
int score(int reversi_board[][8], int pawn) {
	int sum = 0;
	for(int i=0; i < 8; i++) {
		for(int j=0; j < 8; j++) {
			sum += reversi_board[i][j];
		}
	}
	return sum * pawn;
}
//---End of Function score---//



