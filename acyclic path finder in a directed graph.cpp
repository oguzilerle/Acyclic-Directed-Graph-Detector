#include "the6.h"
// Don't add any additional includes

/*
  N: Number of racers
  updates: Updates you have heard
*/


class Graph
{
    int N;
    bool cycleRec(int N, bool* visited, bool *stack);
    void sortRec(int N, bool* visited, std::stack<int>& Stack);
public:
    std::vector<int> *adjList;
    Graph(int N);
    bool hasCycle();
    std::vector<int> topSort();
};

Graph::Graph(int N)
{
    this->N = N;
    adjList = new std::vector<int>[N];
}

bool Graph::cycleRec(int N, bool* visited, bool *stack)
{
    if(visited[N] == false)
    {
        visited[N] = true;
        stack[N] = true;
        std::vector<int>::iterator i = adjList[N].begin();
        while(i != adjList[N].end())
        {
            if ( cycleRec(*i, visited, stack) && !visited[*i] )
            {
                return true;
            }
            else if (stack[*i])
            {
                return true;
            }
            i++;
        }
    }
    stack[N] = false;
    return false;
}

bool Graph::hasCycle()
{

    bool *visited = new bool[N];
    bool *recStack = new bool[N];
    int i = 0;
    while(i < N)
    {
        visited[i] = false;
        recStack[i] = false;
        i++;
    }
    i = 0;
    while(i < N)
    {
        if (cycleRec(i, visited, recStack))
        {
            return true;
        }
        i++;
    }

    return false;
}

void Graph::sortRec(int N, bool* visited, std::stack<int>& Stack)
{
    visited[N] = true;

    std::vector<int>::iterator i = adjList[N].begin();
    while (i != adjList[N].end())
    {
        if (!visited[*i])
        {
            sortRec(*i, visited, Stack);
        }
        i++;
    }
    Stack.push(N);
}


std::vector<int> Graph::topSort()
{
    std::vector<int> list;
    std::stack<int> Stack;

    bool* visited = new bool[N];
    int i = 0;
    while (i < N)
    {
        visited[i] = false;
        i++;
    }
    i = 0;
    while (i < N)
    {
        if (visited[i] == false)
        {
            sortRec(i, visited, Stack);
        }
        i++;
    }

    while (Stack.empty() == false) 
    {
        list.push_back(Stack.top());
        Stack.pop();
    }
    
    return list;
}


std::pair<bool, std::vector<int>>
RaceResult(int N, std::vector<std::pair<int, int>> updates) {
    Graph main(N);
    for (long unsigned int i = 0; i < updates.size(); i++)
    {
        main.adjList[updates[i].first].push_back(updates[i].second);
    }
    if (main.hasCycle())
    {
        return {false, main.topSort()};
    }
    else
    {
        return {true, main.topSort()};
    }
}
