#include <iostream>
#include "jug.cpp"

int main () {
    {
        string solution;
        Jug head(3, 5, 4, 1, 2, 3, 4, 5, 6);
       
        int jug_problem = head.solve(solution);

        cout << "Jug problem 1:" << endl;
        if (jug_problem == -1) {
            cout << "Invalid inputs.";
        } else if (jug_problem == 0){
            cout << "No solution.";
        } else {
            cout << solution;
        }
    }
    cout << endl << endl;

    {
        string solution;
        Jug head( 3, 5, 4, 1, 1, 1, 1, 1, 2);
       
        int jug_problem = head.solve(solution);

        cout << "Jug problem 2:" << endl;
        if (jug_problem == -1) {
            cout << "Invalid inputs.";
        } else if (jug_problem == 0){
            cout << "No solution.";
        } else {
            cout << solution;
        }
    }
    cout << endl << endl;

    {
        string solution;
        Jug head(4, 8, 6, 1, 2, 3, 4, 5, 6);
       
        int jug_problem = head.solve(solution);

        cout << "Jug problem 3:" << endl;
        if (jug_problem == -1) {
            cout << "Invalid inputs.";
        } else if (jug_problem == 0){
            cout << "No solution.";
        } else {
            cout << solution;
        }
    }
    cout << endl;
    
    return 0;
}