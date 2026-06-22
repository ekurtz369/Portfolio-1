#include <iostream>

using namespace std;

char board[7][7];

void make_board(int i) {
	if (i == 1) {

		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				board[i][j] = ' ';
			}
		}

		for (int i = 0; i < 7; i++) {
			board[0][i] = '#';
			board[6][i] = '#';
			board[i][6] = '#';
		}

		for (int i = 0; i < 5; i++) {
			board[i][0] = '#';
		}

		board[2][2] = '#';
		board[2][4] = '#';
		board[4][3] = '#';
		board[4][5] = '#';


		board[5][0] = '@';

		board[2][5] = '$';

		board[1][3] = 'v';
		board[3][5] = '<';
		board[5][2] = '^';
	}
}

void print_board(int i) {
	if (i == 1) {
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				cout << board[i][j];
			}
			cout << endl;
		}
	}
}


int main() {

	cout << "Welcome to Generic Spy Game! Please choose a map: " << endl;
	cout << "1) Easy" << endl << "2) [coming soon]" << endl << "3) [coming soon]" << endl << endl;

	string response;
	cin >> response;
	cout << endl;

	for (char& c : response) {
		c = tolower(c);
	}

	int map;
	int turns;
	if ((response == "1") || (response == "easy")) {
		map = 1;
		turns = 12;
	}

	make_board(map);
	print_board(map);

}