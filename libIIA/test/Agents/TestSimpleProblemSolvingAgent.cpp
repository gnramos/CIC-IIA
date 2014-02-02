#include "TestSimpleProblemSolvingAgent.h"

using namespace IIA::Test;
int main(int argc, char **argv)	{	
	Problem::ZeroToFour problem;
	Agents::SimpleProblemSolvingAgent agent(problem);
	
	Integer state = problem.initial_state;
	while(!problem.is_goal(state)) state = agent.act(state);

	return 0;
}

