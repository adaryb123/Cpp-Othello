#include <vector>
#include <string>
#include <iostream>

enum class Player_color { white, black };
enum class Enemy{ random, heuristic, minmax };

void assign_start_variables(Player_color& player_color, Enemy& enemy) {
	while (true) {
		bool error = false;
		std::string color_string, enemy_string;
		std::cout << "Welcome to Othello console game!\nChoose your color:\n";
		std::cout << "Press 1 for white (O)\nPress 2 for black (X)\n";
		std::cin >> color_string;
		if (color_string == "1")
			player_color = Player_color::white;
		else if (color_string == "2")
			player_color = Player_color::black;
		else {
			std::cout << "Invalid option. Try again!";
			error = true;
			continue;
		}

		std::cout << "\nChoose enemy AI to play against:\n";
		std::cout << "Press 1 for random enemy\nPress 2 for heuristic enemy\nPress 3 for minmax enemy\n";
		std::cin >> enemy_string;
		if (enemy_string == "1")
			enemy = Enemy::random;
		else if (enemy_string == "2")
			enemy = Enemy::heuristic;
		else if (enemy_string == "3")
			enemy = Enemy::minmax;
		else {
			std::cout << "Invalid option. Try again!\n\n";
			error = true;
			continue;
		}

		if (!error)
			break;
	}

	std::cout << "\nPlaying with ";
	if (player_color == Player_color::black)
		std::cout << "black";
	else if (player_color == Player_color::white)
		std::cout << "white";
	std::cout << " against ";
	if (enemy == Enemy::random)
		std::cout << "random";
	else if (enemy == Enemy::heuristic)
		std::cout << "heuristic";
	else if (enemy == Enemy::minmax)
		std::cout << "minmax";
	std::cout << " enemy.\n\n\n";
}

void setup_game(std::vector<std::vector<char>>& game_board) {
	for (size_t i = 0; i < 8; i++)
	{
		game_board.push_back(std::vector<char>{});
		for (size_t j = 0; j < 8; j++)
			game_board[i].push_back('-');
	}
	game_board[3][3] = 'O';
	game_board[4][4] = 'O';
	game_board[3][4] = 'X';
	game_board[4][3] = 'X';
}

void print_game(const std::vector<std::vector<char>>& game)
{
	std::cout << "    A B C D E F G H\n\n";
 	for (size_t i = 0; i < 8; i++)
	{
		std::cout << static_cast<int>(i+1) << "   ";
		for (size_t j = 0; j < 8; j++)
			std::cout << game[i][j] << " ";
		std::cout << "\n";
	}
}

bool check_valid_input(const std::string input) {
	if (input.size() != 2)
		return false;

	char row, col;
	row = static_cast<char>(input[0]);
	if (row < '1' || row > '8')
		return false;

	col = static_cast<char>(input[1]);
	if (!(col >= 'A' && col <= 'H') && !(col >= 'a' && col <= 'h'))
		return false;

	return true;

}

int main()
{
	Player_color player_color;
	Enemy enemy;
	assign_start_variables(player_color, enemy);
	std::vector<std::vector<char>> game_board;
	setup_game(game_board);
	print_game(game_board);
	if (player_color == Player_color::black)
	{
		std::string input;
		std::cout << "Your turn!\n";
		std::cout << "Enter the row and column of the new piece: (example: 1A)\n";
		std::cin >> input;
		if (!check_valid_input(input))
			std::cout << "Invalid input. Enter the row and column of the new piece: (example: 1A)\n";
	}
	return 0;
}
