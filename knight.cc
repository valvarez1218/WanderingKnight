#include <iostream>
#include <string>
#include <utility>
#include <random>


// return a pair of integers (a, b) where 0 <= a, b <= 7
std::pair<int, int> toPair(std::string coord);

// runs the algorithm
int wander(std::pair<int, int> startingSquare);

// The number of trials that will be run from the specified square
int g_Trials = 100000;

// main function will take a chess square as input, and run algorithm
int main(void) {
    std::string starting_square;
    std::cout << "Please enter a starting square for the knight: " << std::endl;
    std::cin >> starting_square;

    while (toPair(starting_square) == std::make_pair(-1, -1)) {
        std::cout << "Please enter a starting square for the knight: " << std::endl;
        std::cin >> starting_square;
    }

    std::pair<int, int> coord = toPair(starting_square);

    int sumOfTrials = 0;

    for (int i = 0; i < g_Trials; i++) {
        sumOfTrials += wander(coord);
    }

    float avg = (float)sumOfTrials / g_Trials ;

    std::cout << "The knight took an average of " << avg << " moves to return." << std::endl;

    return 0;
}


// returns integer pair representing chess coordinate
std::pair<int, int> toPair(std::string coord) {
    std::pair<int, int> toReturn;

    // if the length of the input is more than two characters, return (-1, -1)
    if (coord.size() != 2) {
        return std::make_pair(-1, -1);
    }

    char file = coord[0];
    char rank = coord[1];
    
    if (file == 'A' || file == 'a') {
        toReturn.first = 0;
    }
    else if (file == 'B' || file == 'b') {
        toReturn.first = 1;
    }
    else if (file == 'C' || file == 'c') {
        toReturn.first = 2;
    }
    else if (file == 'D' || file == 'd') {
        toReturn.first = 3;
    }
    else if (file == 'E' || file == 'e') {
        toReturn.first = 4;
    }
    else if (file == 'F' || file == 'f') {
        toReturn.first = 5;
    }
    else if (file == 'G' || file == 'g') {
        toReturn.first = 6;
    }
    else if (file == 'H' || file == 'h') {
        toReturn.first = 7;
    }
    else {
        return std::make_pair(-1, -1);
    }

    switch(rank) {
        case '1':
            toReturn.second = 0;
            break;

        case '2':
            toReturn.second = 1;
            break;

        case '3':
            toReturn.second = 2;
            break;

        case '4':
            toReturn.second = 3;
            break;

        case '5':
            toReturn.second = 4;
            break;

        case '6':
            toReturn.second = 5;
            break;

        case '7':
            toReturn.second = 6;
            break;

        case '8':
            toReturn.second = 7;
            break;

        default:
            return std::make_pair(-1, -1);
    }

    return toReturn;
}


// given a position, generate the valid moves from this square
std::vector<std::pair<int, int>> generateMoves (std::pair<int, int> coord) {
    std::vector<int> horizontal;
    std::vector<int> vertical;

    if (coord.first - 2 >= 0) {
        horizontal.push_back(-2);
    }
    if (coord.first - 1 >= 0) {
        horizontal.push_back(-1);
    }
    if (coord.first + 2 <= 7) {
        horizontal.push_back(2);
    }
    if (coord.first + 1 <= 7) {
        horizontal.push_back(1);
    }
    
    if (coord.second - 2 >= 0) {
        vertical.push_back(-2);
    }
    if (coord.second - 1 >= 0) {
        vertical.push_back(-1);
    }
    if (coord.second + 2 <= 7) {
        vertical.push_back(2);
    }
    if (coord.second + 1 <= 7) {
        vertical.push_back(1);
    }

    // create possible moves
    std::vector<std::pair<int, int>> moves;
    for (int h : horizontal) {
        for (int v : vertical) {
            if (abs(h) != abs(v)) {
                moves.push_back(std::make_pair(h, v));
            }
        }
    }

    return moves;
}

// given a coordinate, move to new position
std::pair<int, int> makeMove(std::pair<int, int> coord) {
    std::random_device rand;
    std::vector<std::pair<int, int>> moves = generateMoves(coord);
    std::pair<int, int> direction = moves[rand() % (moves.size())];

    // return new coord
    std::pair<int, int> new_coord = std::make_pair(coord.first + direction.first, coord.second + direction.second);
    return new_coord;
}

int wander(std::pair<int, int> startingSquare) {
    // make first move
    std::pair<int, int> currSquare = makeMove(startingSquare);
    int moveCount = 1;

    while (currSquare != startingSquare) {
        currSquare = makeMove(currSquare);
        moveCount++;
    }

    return moveCount;
}