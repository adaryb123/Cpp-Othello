#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

enum class Color { white, black };
enum class Enemy{ random, heuristic, minmax };
typedef struct Tile {
	int row;
	int col;
}tile;

void assign_start_variables(Color& player_color, Enemy& enemy, Color& enemy_color) {
	while (true) {
		bool error = false;
		std::string color_string, enemy_string;
		std::cout << "Welcome to Othello console game!\nChoose your color:\n";
		std::cout << "Press 1 for white (O)\nPress 2 for black (X)\n";
		std::cin >> color_string;
		if (color_string == "1") {
			player_color = Color::white;
			enemy_color = Color::black;
		}
		else if (color_string == "2") {
			player_color = Color::black;
			enemy_color = Color::white;
		}
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
	if (player_color == Color::black)
		std::cout << "black";
	else if (player_color == Color::white)
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
	std::cout << "\n    A B C D E F G H\n\n";
 	for (size_t i = 0; i < 8; i++)
	{
		std::cout << static_cast<int>(i+1) << "   ";
		for (size_t j = 0; j < 8; j++)
			std::cout << game[i][j] << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
}

bool check_valid_input(const std::string input) {
	if (input.size() != 2)
		return false;

	char row, col;
	row = static_cast<char>(input[0]);
	if (row < '1' || row > '8')
		return false;

	col = static_cast<char>(input[1]);
	if (col < 'A' || col > 'H')
		return false;

	return true;
}

Tile string_to_tile(const std::string& input)					
{
	Tile output;
	char temp = input[0];
	output.row = temp - '1';
	output.col = static_cast<int>(input[1] - 'A');
	return output;
}

std::string tile_to_string(const Tile& input)			
{
	std::string output;
	output += std::to_string(input.row + 1);
	output += static_cast<char>(input.col + 'A');
	return output;
}

void print_possible_moves(const std::vector<tile> moves)
{
	std::cout<<"Possible moves are:\n";
	for (size_t i = 0; i < moves.size(); i++)
		std::cout << tile_to_string(moves[i]) << "\n";
}

bool check_move_valid(std::vector<std::vector<char>> game, const Tile& tile, const Color& color)
{
	char enemy_piece, friendly_piece;

	if (color == Color::black) {
		game[tile.row][tile.col] = 'X';
		enemy_piece = 'O';
		friendly_piece = 'X';
	}
	else {
		game[tile.row][tile.col] = 'O';
		enemy_piece = 'X';
		friendly_piece = 'O';
	}

	//up
	if (tile.row - 1 >= 0 && game[tile.row - 1][tile.col] == enemy_piece) 
		for (int i = tile.row - 1; i >= 0; i--) {
			if (game[i][tile.col] == friendly_piece)
				return true;
			else if (game[i][tile.col] == '-')
				break;
		}
	

	//down
	if (tile.row + 1 <= 7 && game[tile.row + 1][tile.col] == enemy_piece) 
		for (int i = tile.row + 1; i <= 7; i++) {
			if (game[i][tile.col] == friendly_piece)
				return true;
			else if (game[i][tile.col] == '-')
				break;
		}
	

	//left
	if (tile.col - 1 >= 0 && game[tile.row][tile.col - 1] == enemy_piece) 
		for (int i = tile.col - 1; i >= 0; i--) {
			if (game[tile.row][i] == friendly_piece)
				return true;
			else if (game[tile.row][i] == '-')
				break;
		}

	//right
	if (tile.col + 1 <= 7 && game[tile.row][tile.col + 1] == enemy_piece) 
		for (int i = tile.col + 1; i <= 7; i++){
			if (game[tile.row][i] == friendly_piece)
				return true;
			else if (game[tile.row][i] == '-')
				break;
		}

	//up left
	if (tile.row - 1 >= 0 && tile.col -1 >= 0 && game[tile.row -1][tile.col -1] == enemy_piece)
		for (int i = tile.row - 1, j = tile.col - 1; i >= 0 && j >= 0; i--, j--) {
			if (game[i][j] == friendly_piece)
				return true;
			else if (game[i][j] == '-')
				break;
		}

	//up right
	if (tile.row - 1 >= 0 && tile.col + 1 <= 7 && game[tile.row - 1][tile.col + 1] == enemy_piece)
		for (int i = tile.row - 1, j = tile.col + 1; i >= 0 && j <= 7; i--, j++) {
			if (game[i][j] == friendly_piece)
				return true;
			else if (game[i][j] == '-')
				break;
		}

	//down left
	if (tile.row + 1 <= 7 && tile.col - 1 >= 0 && game[tile.row + 1][tile.col - 1] == enemy_piece)
		for (int i = tile.row + 1, j = tile.col - 1; i <= 7 && j >= 0; i++, j--) {
			if (game[i][j] == friendly_piece)
				return true;
			else if (game[i][j] == '-')
				break;
		}

	//down right
	if (tile.row + 1 <= 7 && tile.col + 1 <= 7 && game[tile.row + 1][tile.col + 1] == enemy_piece)
		for (int i = tile.row + 1, j = tile.col + 1; i <= 7 && j <= 7; i++, j++) {
			if (game[i][j] == friendly_piece)
				return true;
			else if (game[i][j] == '-')
				break;
		}

	return false;
}

std::vector<Tile> find_possible_moves(const std::vector<std::vector<char>>& game, const Color& color)
{

	std::vector<Tile> valid_moves;

	for (int i = 0 ; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (game[i][j] != '-')
				continue;

			Tile current_move;
			current_move.row = i;
			current_move.col = j;
			if (check_move_valid(game, current_move, color))
			{
				valid_moves.push_back(current_move);
			}
		}
	return valid_moves;
}

void update_game(std::vector<std::vector<char>>& game, const Tile& tile, const Color& color)
{
	char enemy_piece, friendly_piece;

	if (color == Color::black) {
		game[tile.row][tile.col] = 'X';
		enemy_piece = 'O';
		friendly_piece = 'X';
	}
	else {
		game[tile.row][tile.col] = 'O';
		enemy_piece = 'X';
		friendly_piece = 'O';
	}

	//up
	if (tile.row - 1 >= 0 && game[tile.row - 1][tile.col] == enemy_piece)
		for (int i = tile.row - 1; i >= 0; i--) {
			if (game[i][tile.col] == friendly_piece)
			{
				for (int j = i; j <= tile.row - 1; j++)
					game[j][tile.col] = friendly_piece;
				break;
			}
			else if (game[i][tile.col] == '-')
				break;

		}

	//down
	if (tile.row + 1 <= 7 && game[tile.row + 1][tile.col] == enemy_piece)
		for (int i = tile.row + 1; i <= 7; i++) {
			if (game[i][tile.col] == friendly_piece)
			{
				for (int j = i; j >= tile.row + 1; j--)
					game[j][tile.col] = friendly_piece;
				break;
			}
			else if (game[i][tile.col] == '-')
				break;
		}

	//left
	if (tile.col - 1 >= 0 && game[tile.row][tile.col - 1] == enemy_piece)
		for (int i = tile.col - 1; i >= 0; i--) {
			if (game[tile.row][i] == friendly_piece)
			{
				for (int j = i; j <= tile.col - 1; j++)
					game[tile.row][j] = friendly_piece;
				break;
			}
			else if (game[tile.row][i] == '-')
				break;
		}

	//right
	if (tile.col + 1 <= 7 && game[tile.row][tile.col + 1] == enemy_piece)
		for (int i = tile.col + 1; i <= 7; i++) {
			if (game[tile.row][i] == friendly_piece)
			{
				for (int j = i; j >= tile.col + 1; j--)
					game[tile.row][j] = friendly_piece;
				break;
			}
			else if (game[tile.row][i] == '-')
				break;
		}

	//up left
	if (tile.row - 1 >= 0 && tile.col - 1 >= 0 && game[tile.row - 1][tile.col - 1] == enemy_piece)
		for (int i = tile.row - 1, j = tile.col - 1; i >= 0 && j >= 0; i--, j--) {
			if (game[i][j] == friendly_piece)
			{
				for (int k = i, l = j; (k <= tile.row - 1) && (l <= tile.col - 1); k++, l++)
					game[k][l] = friendly_piece;
				break;
			}
			else if (game[i][j] == '-')
				break;
		}

	//up right
	if (tile.row - 1 >= 0 && tile.col + 1 <= 7 && game[tile.row - 1][tile.col + 1] == enemy_piece)
		for (int i = tile.row - 1, j = tile.col + 1; i >= 0 && j <= 7; i--, j++) {
			if (game[i][j] == friendly_piece)
			{
				for (int k = i, l = j; (k <= tile.row - 1) && (l >= tile.col + 1); k++, l--)
					game[k][l] = friendly_piece;
				break;
			}
			else if (game[i][j] == '-')
				break;
		}
	

	//down left
	if (tile.row + 1 <= 7 && tile.col - 1 >= 0 && game[tile.row + 1][tile.col - 1] == enemy_piece)
		for (int i = tile.row + 1, j = tile.col - 1; i <= 7 && j >= 0; i++, j--) {
			if (game[i][j] == friendly_piece)
			{
				for (int k = i, l = j; (k >= tile.row + 1) && (l <= tile.col - 1); k--, l++)
					game[k][l] = friendly_piece;
				break;
			}
			else if (game[i][j] == '-')
				break;
		}

	//down right
	if (tile.row + 1 <= 7 && tile.col + 1 <= 7 && game[tile.row + 1][tile.col + 1] == enemy_piece)
		for (int i = tile.row + 1, j = tile.col + 1; i <= 7 && j <= 7; i++, j++) {
			if (game[i][j] == friendly_piece)
			{
				for (int k = i, l = j; (k >= tile.row + 1) && (l >= tile.col + 1); k--, l--)
					game[k][l] = friendly_piece;
				break;
			}
			else if (game[i][j] == '-')
				break;
		}

}

void player_turn(std::vector<std::vector<char>>& game,const std::vector<Tile>& possible_moves, const Color& color)
{
	std::string input;
	std::cout << "Your turn!\n";
	while (true)
	{
		std::cout << "Enter the row and column of the new piece: (example: 1A)\n";
		std::cin >> input;
		input[1] = static_cast<char>(toupper(input[1]));
		if (!check_valid_input(input))
		{
			std::cout << "Invalid input format. Try again.\n";
			continue;
		}
		Tile selected_move = string_to_tile(input);

		bool valid = false;
		for (auto move : possible_moves)
		{
			if (move.col == selected_move.col && move.row == selected_move.row) {
				valid = true;
				break;
			}
		}
		if (valid) {
			update_game(game, selected_move, color);
			break;
		}
		else
		{
			std::cout << "Invalid move. Try again.\n";
			print_possible_moves(possible_moves);
		}
	}
}

int main()
{
	Color player_color, enemy_color;
	Enemy enemy;
	assign_start_variables(player_color, enemy,enemy_color);
	std::vector<std::vector<char>> game_board;
	setup_game(game_board);
	print_game(game_board);
	
	while(true)
	{
		Color on_turn;
		bool black_skip = false;
		bool white_skip = false;

		on_turn = Color::black;
		std::vector<Tile> possible_moves_black = find_possible_moves(game_board, on_turn);
		if (possible_moves_black.empty())
		{
			std::cout << "No available moves for black player.\n";
			black_skip = true;
		}
		else {
			if (player_color == Color::black)
				player_turn(game_board,possible_moves_black,player_color);
			else
				player_turn(game_board, possible_moves_black, enemy_color);;//enemy_make_turn
		}

		print_game(game_board);

		on_turn = Color::white;
		std::vector<Tile> possible_moves_white = find_possible_moves(game_board, on_turn);
		// find possible moves
		if (possible_moves_white.empty())
		{
			std::cout << "No available moves for white player.\n";
			white_skip = true;
		}
		else {
			if (player_color == Color::white)
				player_turn(game_board,possible_moves_white,player_color);
			else
				player_turn(game_board, possible_moves_white, enemy_color);//enemy_make_turn
		}

		print_game(game_board);

		if (black_skip && white_skip)
			break;
	}
	std::cout << "Game has ended.\n";
	return 0;
}
