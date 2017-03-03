// HW2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include <array>
#include <string.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <ostream>
#include <iterator>

using namespace std;

#define ATRAND (double)rand()/RAND_MAX



/////////////////////////////////////////////////
/////////////// AGENT STUFF /////////////////////
/////////////////////////////////////////////////



class agent {
public:
	int ax;
	int ay;
	int agent_position[2] = { ay, ax };   																							 // 2 entry array
	double epsilon;
	double alpha;
	double gamma;
	void init();
	void decide(agent* plearner);
	void act1(agent* plearner);
	void act2(agent*plearner);
};

void agent::init() {
	ax = 2;   																														 // places learner at (0,0)
	ay = 1;
	agent_position[1] = ax;   																										 // stores agent's x coord in 2nd data entry
	agent_position[0] = ay;   																										 // stores agent's y coord in 1st data entry
}



/////////////////////////////////////////////////
///////////////// DOMAIN STUFF //////////////////
/////////////////////////////////////////////////



class domain {
public:
	int x;
	int y;
	void init();
	void write();
	void show(agent* plearner);
	void position(domain* pgrid, agent* plearner);
	void goal(domain* pgrid);
	int goal_x;
	int goal_y;
	vector<vector<int>> matrix;   																									 // 2D vector
	vector<vector<double>> qtable;
	vector<int> state;
	vector<int> rewards;
	void fillq(agent* plearner);
	void updateq(agent* plearner, int user_input)
};

void domain::init() {
	cout << "Please choose how many rows \n x = " << endl;
	cin >> x;  																											 // user input for rows
	cout << "Please choose how many columns \n y = " << endl;
	cin >> y;  																											 // user input for columns
	matrix.resize(x);   																									 // creates x columns (i think)
	goal_x = x - 1;   																										 // goal placed at a random X coordinate
	goal_y = y - 1;   																										 // goal placed at a random Y coordinate
	for (int i = 0; i < x; i++) {
		matrix[i].resize(y);   																							 // creates y rows (i think)
	}
	for (int t = 0; t < x; t++) {   																						 // creates state vector
		for (int j = 0; j < y; j++) {
			matrix[t][j] = j + (t*y);
			state.push_back(matrix[t][j]);
		}
	}
	for (int i = 0; i < state.size(); i++) {
		cout << state.at(i);   																							 // fills state vector
	}
	for (int t = 0; t < x; t++) {
		for (int j = 0; j < y; j++) {
			matrix[t][j] = j + (t*y);
			rewards.push_back(matrix[t][j]);   																			 // creates rewards vector
		}
	}
	for (int i = 0; i < rewards.size(); i++) {
		rewards.at(i) = -1;   																								 // all rewards = -1
	}
	rewards.at(state.at(matrix[goal_y][goal_x])) = 100;   																	 // goal reward = 100

	cout << endl;
	goal_x = x - 1;   																										 // goal placed at a random X coordinate
	goal_y = y - 1;   																										 // goal placed at a random Y coordinate
}
// obtained from http://stackoverflow.com/questions/1403150/how-do-you-dynamically-allocate-a-matrix



void domain::write() {
	for (int t = 0; t < x; t++) {
		for (int j = 0; j < y; j++) {
			matrix[t][j] = j + t*x; 																									 // populates board with 1's
		}
	}
	cout << endl;
}

void domain::show(agent* plearner) {
	for (int o = 0; o < x; o++) {
		for (int p = 0; p < y; p++) {
			cout << matrix[o][p] << "\t";  																						 // show matrix
		}
		cout << endl;
	}
	cout << "\nYour X coordinate is " << plearner->ax << " and your Y coordinate is " << plearner->ay << ".\n" << endl;  			 // display learner coordinates
	cout << "The goal's coordinates are at " << goal_y << "," << goal_x << ".\n" << endl;   										 // display goal coordinates
}

void domain::position(domain* pgrid, agent* plearner) {  																			 // show where the agent is on grid
	int a = plearner->agent_position[0];
	int b = plearner->agent_position[1];
	int AP = 9;   																													 // agent represented as a 9 on the board
																																	 /*pgrid->matrix[a][b] = AP;*/   																								 // places agent representation on board
}

void domain::goal(domain* pgrid) {  																								 // show where goal is on grid
	int goal = 5;
	/*pgrid->matrix[goal_y][goal_x] = goal;*/   																					 // places goal coords onto gridworld
}

void domain::fillq(agent* plearner) {
	int st = x * y;
	qtable.resize(st);   																									  		 // creates x columns (i think)
	for (int i = 0; i < st; i++) {
		qtable[i].resize(4);   																									 // creates y rows (i think)
	}
	double q_init = 0;
	for (int i = 0; i < st; i++) {
		for (int j = 0; j < 4; j++) {
			q_init = 0.001 * ATRAND;
			qtable[i][j] = q_init;
		}
	}
	cout << "filled table" << endl;
	for (int o = 0; o < st; o++) {
		for (int p = 0; p < 4; p++) {
			cout << qtable[o][p] << "\t";  																						 // show matrix
		}
		cout << endl;
	}
	int state_current;
	state_current = state.at(matrix[plearner->ay][plearner->ax]);
	cout << state.at(matrix[plearner->ay][plearner->ax]) << endl;   												 // read state from agent coords
	cout << qtable[state_current][0] << endl;   																	 // read q value from state and action
}



void updateq(agent* plearner, int user_input) {

}




/////////////////////////////////////////////////
/////////////// MOVEMENT FUNCTIONS //////////////
/////////////////////////////////////////////////



void up(agent* plearner) {
	plearner->ay = plearner->ay - 1; 																								 // agent's y position is moved up 1
	plearner->agent_position[0] = plearner->ay;
};

void down(agent* plearner) {
	plearner->ay = plearner->ay + 1; 																								 // agent's y position is moved down 1
	plearner->agent_position[0] = plearner->ay;
}


void right(agent* plearner) {
	plearner->ax = plearner->ax + 1; 																								 // agent's x position is moved right 1
	plearner->agent_position[1] = plearner->ax;
}

void left(agent* plearner) {
	plearner->ax = plearner->ax - 1; 																								 // agent's x position is moved left 1
	plearner->agent_position[1] = plearner->ax;
}



/////////////////////////////////////////////////
///////////////// BUMP THINGS ///////////////////
/////////////////////////////////////////////////



void bumper_down(agent* plearner, domain* pgrid, int user_input) {  																 // (-,0) & input = up
	if (plearner->ay == 0 && user_input == 1) {
		plearner->ay = plearner->ay + 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped down" << endl;
	}
}

void bumper_up(agent* plearner, domain* pgrid, int user_input) {  																	 // (-,y) & input = down
	if (plearner->ay == pgrid->y - 1 && user_input == 2) {
		plearner->ay = plearner->ay - 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped up\n" << endl;
	}
}

void bumper_left(agent* plearner, domain* pgrid, int user_input) {  																 // (x,-) & input = right
	if (plearner->ax == pgrid->x - 1 && user_input == 3) {
		plearner->ax = plearner->ax - 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped left\n" << endl;
	}
}

void bumper_right(agent* plearner, domain* pgrid, int user_input) {  																 // (0,-) & input = left
	if (plearner->ax == 0 && user_input == 4) {
		plearner->ax = plearner->ax + 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped right\n" << endl;
	}
}

// corner cases where agent can go out of bounds by going in two directions

void bumper_top_left(agent* plearner, domain* pgrid, int user_input) {
	if (plearner->ax == 0 && plearner->ay == 0 && user_input == 4) {  																 // (0,0) & input = left
		plearner->ax = plearner->ax + 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped right\n" << endl;
	}
	if (plearner->ax == 0 && plearner->ay == 0 && user_input == 1) {  																 // (0,0) & input = up
		plearner->ay = plearner->ay + 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped down\n" << endl;
	}
}

void bumper_top_right(agent* plearner, domain* pgrid, int user_input) {
	if (plearner->ax == pgrid->x - 1 && plearner->ay == 0 && user_input == 3) {  													 // (x,0) & input = right
		plearner->ax = plearner->ax - 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped left\n" << endl;
	}
	if (plearner->ax == pgrid->x - 1 && plearner->ay == 0 && user_input == 1) {  													 // (x,0) & input = up
		plearner->ay = plearner->ay + 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped down\n" << endl;
	}
}

void bumper_bot_left(agent* plearner, domain* pgrid, int user_input) {
	if (plearner->ax == 0 && plearner->ay == pgrid->y - 1 && user_input == 4) {  													 // (0,y) & input = left
		plearner->ax = plearner->ax + 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped left\n" << endl;
	}
	if (plearner->ax == 0 && plearner->ay == pgrid->y - 1 && user_input == 2) {  													 // (0,y) & input = down
		plearner->ay = plearner->ay - 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped up\n" << endl;
	}
}

void bumper_bot_right(agent* plearner, domain* pgrid, int user_input) {
	if (plearner->ax == pgrid->x - 1 && plearner->ay == pgrid->y - 1 && user_input == 3) {  										 // (x,y) & input = right
		plearner->ax = plearner->ax - 1;
		plearner->agent_position[1] = plearner->ax;
		cout << "bumped left\n" << endl;
	}
	if (plearner->ax == pgrid->x - 1 && plearner->ay == pgrid->y - 1 && user_input == 2) {  										 // (x,y) & input = down
		plearner->ay = plearner->ay - 1;
		plearner->agent_position[0] = plearner->ay;
		cout << "bumped up\n" << endl;
	}
}



/////////////////////////////////////////////////
///////// MOVING AGENT BACK TO BOARD FROM ///////
///////// EXTREEEEEEEEEEEME COORDINATES /////////
/////////////////////////////////////////////////



void testA(agent* plearner, domain* pgrid) {
	cout << "Enter an extreme X,Y coordinate" << endl;
	cout << "X coordinate =" << endl;
	cin >> plearner->ax;
	plearner->agent_position[1] = plearner->ax;
	cout << "Y coordinate =" << endl;
	cin >> plearner->ay;
	plearner->agent_position[0] = plearner->ay;
	cout << "\nExtreme coordinates are " << plearner->ax << "," << plearner->ay << "\n" << endl;
	if (plearner->ax > pgrid->x) {   																								 // reposition learner's x coord
		plearner->ax = 0;
		plearner->agent_position[1] = plearner->ax;
	}
	if (plearner->ay > pgrid->y) {   																								 // reposition learner's y coord
		plearner->ay = 0;
		plearner->agent_position[0] = plearner->ay;
	}
	cout << "Magic happens. \n" << endl;
	cout << "New coordinates are " << plearner->ax << "," << plearner->ay << "\n" << endl;
	pgrid->goal(pgrid);
	pgrid->position(pgrid, plearner);  																							 // positions the learner
	pgrid->write();
	pgrid->position(pgrid, plearner);
	pgrid->show(plearner);
}



/////////////////////////////////////////////////
//////// HUMAN CONTROLLED NAVIGATION ////////////
/////////////////////////////////////////////////



void testB(agent* plearner, domain*pgrid) {
	cout << "Coordinates start from 1,1 at top left corner. \nThe AGENT is represented by a 9. \nThe GOAL is represented by a 5. \nAn empty space is represented by a 1. \n" << endl;
	pgrid->show(plearner);
	int check = 1;
	while (check < 50) {
		int user_input;
		cout << "check = " << check << endl;
		cout << "Move the agent (9) around. 1 to move up, 2 to move down, 3 to move right, 4 to move left!\n" << endl;
		cin >> user_input;
		if (user_input == 1) {   																									 // up
			bumper_down(plearner, pgrid, user_input);
			bumper_top_left(plearner, pgrid, user_input);
			bumper_top_right(plearner, pgrid, user_input);
			up(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
		}
		if (user_input == 2) {   																									 // down
			bumper_up(plearner, pgrid, user_input);
			bumper_bot_left(plearner, pgrid, user_input);
			bumper_bot_right(plearner, pgrid, user_input);
			down(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
		}
		if (user_input == 3) {   																									 // right
			bumper_left(plearner, pgrid, user_input);
			bumper_top_right(plearner, pgrid, user_input);
			bumper_bot_right(plearner, pgrid, user_input);
			right(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
		}
		if (user_input == 4) {   																									 // left
			bumper_right(plearner, pgrid, user_input);
			bumper_top_left(plearner, pgrid, user_input);
			bumper_bot_left(plearner, pgrid, user_input);
			left(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
		}
		if (plearner->ax == pgrid->goal_x && plearner->ay == pgrid->goal_y) {   													 // ends the while loop
			check = 100;
			cout << "Goal reached! Program ending.\n" << endl;
		}

	}

}



/////////////////////////////////////////////////
///////////// HARD CODED NAVIGATION /////////////
/////////////////////////////////////////////////



void testC(agent* plearner, domain* pgrid) {
	// if agent x > goal x, agent x - 1 (LEFT)
	// if agent y > goal y, agent y - 1 (UP)
	// if agent x < goal x, agent x + 1 (RIGHT)
	// if agent y < goal y, agent y + 1 (DOWN)
	cout << "Coordinates start from 1,1 at top left corner. \nThe AGENT is represented by a 9. \nThe GOAL is represented by a 5. \nAn empty space is represented by a 1. \n" << endl;
	cout << "Heuristic control!" << endl;
	int user_input = 0;
	int check = 10;
	while (check < 50) {
		if (plearner->ax > pgrid->goal_x) {  																						 // move left
			user_input = 4;
			bumper_right(plearner, pgrid, user_input);   																			 // technically, the heuristic control should never need bumpers
			bumper_top_left(plearner, pgrid, user_input);
			bumper_bot_left(plearner, pgrid, user_input);
			left(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
			cout << "Press any number to continue movement" << endl;
			int input;
			cin >> input;
		}
		else if (plearner->ax < pgrid->goal_x) {  																					 // move right
			user_input = 3;
			bumper_left(plearner, pgrid, user_input);
			bumper_top_right(plearner, pgrid, user_input);
			bumper_bot_right(plearner, pgrid, user_input);
			right(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
			cout << "Press any number to continue movement" << endl;
			int input;
			cin >> input;
		}
		else if (plearner->ay < pgrid->goal_y) {  																					 // move down
			user_input = 2;
			bumper_up(plearner, pgrid, user_input);
			bumper_bot_left(plearner, pgrid, user_input);
			bumper_bot_right(plearner, pgrid, user_input);
			down(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
			cout << "Press any number to continue movement" << endl;
			int input;
			cin >> input;
		}
		else if (plearner->ay > pgrid->goal_y) {  																					 // move up
			user_input = 1;
			bumper_down(plearner, pgrid, user_input);
			bumper_top_left(plearner, pgrid, user_input);
			bumper_top_right(plearner, pgrid, user_input);
			up(plearner);
			pgrid->write();
			pgrid->goal(pgrid);
			pgrid->position(pgrid, plearner);
			pgrid->show(plearner);
			cout << "Press any number to continue movement" << endl;
			int input;
			cin >> input;
		}
		else if (plearner->ax == pgrid->goal_x && plearner->ay == pgrid->goal_y) {   												 // end while loop
			check = 100;
		}
		else {
			cout << "Press any number to continue movement" << endl;   															 // user makes next step happen, but movement is still "autonomous"
			int input;
			cin >> input;
		}
	}
}

/////////////////////////////////////////////////

int decide(agent* plearner) {
	int action;
	double decision = ATRAND;
	if (1 - plearner->epsilon <= decision) {   																						 // compares if epsilon is less than or equal to a random number
		action = 1;   																													 // random action
	}
	else {
		action = 2;   																													 // greedy action
	}
	return action;
}

double act1(agent* plearner, domain* pgrid, int user_input) {   																									 // random action
	user_input = rand() % 4 + 1;
	if (user_input == 1) {
		bumper_down(plearner, pgrid, user_input);
		bumper_top_left(plearner, pgrid, user_input);
		bumper_top_right(plearner, pgrid, user_input);
		up(plearner);
	}
	if (user_input == 2) {
		bumper_up(plearner, pgrid, user_input);
		bumper_bot_left(plearner, pgrid, user_input);
		bumper_bot_right(plearner, pgrid, user_input);
		down(plearner);
	}
	if (user_input == 3) {
		bumper_left(plearner, pgrid, user_input);
		bumper_top_right(plearner, pgrid, user_input);
		bumper_bot_right(plearner, pgrid, user_input);
		right(plearner);
	}
	if (user_input == 4) {
		bumper_right(plearner, pgrid, user_input);
		bumper_top_left(plearner, pgrid, user_input);
		bumper_bot_left(plearner, pgrid, user_input);
		left(plearner);
	}
	return user_input;
}

double act2(agent* plearner, domain* pgrid, int input) {   																									 // greedy action
	int Q_up;
	int Q_down;
	int Q_right;
	int Q_left;
	int state_current;
	state_current = pgrid->state.at(pgrid->matrix[plearner->ay][plearner->ax]);
	Q_up = pgrid->qtable[state_current][0];
	Q_down = pgrid->qtable[state_current][1];
	Q_right = pgrid->qtable[state_current][2];
	Q_left = pgrid->qtable[state_current][3];
	double findmax[4] = { Q_up, Q_down, Q_right, Q_left };
	int max = 0;																																			// find max q of current state
	for (int i = 0; i < 4; i++) {
		if (findmax[i] > max) {
			max = findmax[i];
		}
	}
	if (max == Q_up) {
		input = 0;
	}
	if (max == Q_down) {
		input = 1;
	}
	if (max == Q_right) {
		input = 2;
	}
	if (max == Q_left) {
		input = 3;
	}
	if (input == 0) {
		up(plearner);
	}
	if (input == 1) {
		down(plearner);
	}
	if (input == 2) {
		right(plearner);
	}
	if (input == 3) {
		left(plearner);
	}
	return input;
}

// 0 1 2 3
// u d r l

double react(agent* plearner, domain* pgrid, int input) {
	int reward;
	double old_q;
	double curr_q;
	int prev_state;
	reward = pgrid->rewards.at(pgrid->state.at(pgrid->matrix[plearner->ay][plearner->ax]));
	if (input == 0) {
		prev_state = pgrid->state.at(pgrid->matrix[plearner->ax][plearner->ay - 1]);
		old_q = pgrid->qtable[prev_state][input];																											// q from last state
		int Q_up;
		int Q_down;
		int Q_right;
		int Q_left;
		int state_current;
		state_current = pgrid->state.at(pgrid->matrix[plearner->ay][plearner->ax]);
		Q_up = pgrid->qtable[state_current][0];
		Q_down = pgrid->qtable[state_current][1];
		Q_right = pgrid->qtable[state_current][2];
		Q_left = pgrid->qtable[state_current][3];
		double findmax[4] = { Q_up, Q_down, Q_right, Q_left };
		int max = 0;																																		// current q max
		for (int i = 0; i < 4; i++) {
			if (findmax[i] > max) {
				max = findmax[i];
			}
		}
		int update_q;
		update_q = old_q + plearner->alpha*(reward + plearner->gamma*max - old_q);
		pgrid->qtable[prev_state][input] = update_q;
	}
	if (input == 1) {
		prev_state = pgrid->state.at(pgrid->matrix[plearner->ax][plearner->ay + 1]);
		old_q = pgrid->qtable[prev_state][input];																											// q from last state
		int Q_up;
		int Q_down;
		int Q_right;
		int Q_left;
		int state_current;
		state_current = pgrid->state.at(pgrid->matrix[plearner->ay][plearner->ax]);
		Q_up = pgrid->qtable[state_current][0];
		Q_down = pgrid->qtable[state_current][1];
		Q_right = pgrid->qtable[state_current][2];
		Q_left = pgrid->qtable[state_current][3];
		double findmax[4] = { Q_up, Q_down, Q_right, Q_left };
		int max = 0;																																		// current q max
		for (int i = 0; i < 4; i++) {
			if (findmax[i] > max) {
				max = findmax[i];
			}
		}
		int update_q;
		update_q = old_q + plearner->alpha*(reward + plearner->gamma*max - old_q);
		pgrid->qtable[prev_state][input] = update_q;
	}
	if (input == 2) {
		prev_state = pgrid->state.at(pgrid->matrix[plearner->ax+1][plearner->ay]);
		old_q = pgrid->qtable[prev_state][input];																											// q from last state
		int Q_up;
		int Q_down;
		int Q_right;
		int Q_left;
		int state_current;
		state_current = pgrid->state.at(pgrid->matrix[plearner->ay][plearner->ax]);
		Q_up = pgrid->qtable[state_current][0];
		Q_down = pgrid->qtable[state_current][1];
		Q_right = pgrid->qtable[state_current][2];
		Q_left = pgrid->qtable[state_current][3];
		double findmax[4] = { Q_up, Q_down, Q_right, Q_left };
		int max = 0;																																		// current q max
		for (int i = 0; i < 4; i++) {
			if (findmax[i] > max) {
				max = findmax[i];
			}
		}
		int update_q;
		update_q = old_q + plearner->alpha*(reward + plearner->gamma*max - old_q);
		pgrid->qtable[prev_state][input] = update_q;
	}
	if (input == 3) {
		prev_state = pgrid->state.at(pgrid->matrix[plearner->ax-1][plearner->ay]);
		old_q = pgrid->qtable[prev_state][input];																											// q from last state
		int Q_up;
		int Q_down;
		int Q_right;
		int Q_left;
		int state_current;
		state_current = pgrid->state.at(pgrid->matrix[plearner->ay][plearner->ax]);
		Q_up = pgrid->qtable[state_current][0];
		Q_down = pgrid->qtable[state_current][1];
		Q_right = pgrid->qtable[state_current][2];
		Q_left = pgrid->qtable[state_current][3];
		double findmax[4] = { Q_up, Q_down, Q_right, Q_left };
		int max = 0;																																		// current q max
		for (int i = 0; i < 4; i++) {
			if (findmax[i] > max) {
				max = findmax[i];
			}
		}
		int update_q;
		update_q = old_q + plearner->alpha*(reward + plearner->gamma*max - old_q);
		pgrid->qtable[prev_state][input] = update_q;
	}
}

int main()
{
	srand(time(NULL));
	cout << "Coordinates start from the top left corner. \nThe AGENT is represented by a 9. \nThe GOAL is represented by a 5. \nAn empty space is represented by a 1." << endl;
	agent learner;
	learner.init();
	agent* plearner = &learner;
	domain grid;
	grid.init();
	// prevents randomized goal coordinates from being placed on the agent
	while (learner.ax == grid.goal_x && learner.ay == grid.goal_y) {
		cout << "Goal coordinates were placed on agent position, please re-enter X and Y\n" << endl;
		grid.init();
	}
	domain* pgrid = &grid;
	grid.goal(pgrid);  																											 // establishes goal
	grid.position(pgrid, plearner);  																								 // positions the learner
	grid.show(plearner);
	cout << "\n" << endl;
	grid.fillq(plearner);
	// user chooses which test to do
	/*int test_run;
	cout << "Select a test (1 for test A, 2 for test B, 3 for test C)" << endl;
	cin >> test_run;
	if (test_run == 1) {
	testA(plearner, pgrid);
	}
	if (test_run == 2) {
	testB(plearner, pgrid);
	}
	if (test_run == 3) {
	testC(plearner, pgrid);
	}*/
	cout << "You found Waldo! \n" << endl;
	return 0;
}


