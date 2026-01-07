// Section 9
// Challenge
/*    
    This challenge is about using a collection (list) of integers and allowing the user
    to select options from a menu to perform operations on the list.
    
    Your program should display a menu options to the user as follows:
    
    P - Print numbers
    A - Add a number
    M - Display mean of the numbers
    S - Display the smallest number
    L - Display the largest number
    Q - Quit

    Enter your choice:
    
The program should only accept valid choices from the user, both upper and lowercase selections should be allowed.
If an illegal choice is made, you should display, "Unknown selection, please try again" and the menu options should be
displayed again.


If the user enters 'P' or 'p', you should display all of the elements (ints) in the list.
If the list is empty you should display "[] - the list is empty"
If the list is not empty then all the list element should be displayed inside square brackets separated by a space. 
For example, [ 1 2 3 4 5 ]
      
If the user enters 'A' or 'a' then you should prompt the user for an integer to add to the list 
which you will add to the list and then display it was added. For example, if the user enters 5
You should display, "5 added".
Duplicate list entries are OK

If the user enters 'M' or 'm'  you should calculate the mean or average of the elements in the list and display it.
If the list is empty you should display, "Unable to calculate the mean - no data"

If the user enters 'S' or 's' you should display the smallest element in the list.
For example, if the list contains [2 4 5 1],  you should display, "The smallest number is 1"
If the list is empty you should display, "Unable to determine the smallest number - list is empty"

If the user enters 'L' or 'l' you should display the largest element in the list
For example, if the list contains [2 4 5 1], you should display, "The largest number is 5"
If the list is empty you should display, "Unable to determine the largest number - list is empty"

If the user enters 'Q' or 'q' then you should display 'Goodbye" and the program should terminate.

Before you begin. Write out the steps you need to take and decide in what order they should be done.
Think about what loops you should use as well as what you will use for your selection logic.

This exercise can be challenging! It may likely take a few attempts before you complete it -- that's OK!

Finally, be sure to test your program as you go and at the end.

Hint: Use a vector!

Additional functionality if you wish to extend this program.

- search for a number in the list and if found display the number of times it occurs in the list
- clearing out the list (make it empty again) (Hint: the vector class has a .clear() method)
- don't allow duplicate entries
- come up with your own ideas!

Good luck!

*/

#include <iostream>
#include <vector>

using namespace std;

void menu();
bool lista_vazia(vector <int> l);
void print_num(vector <int> l);
void add_num(vector <int> &l);
void mean_num(vector <int> l);
void smallest_num(vector <int> l);
void largest_num(vector <int> l);

int main() {
    
    vector <int> lista;
    char op;

    do
    {
        menu();
        cin >> op;
        op = toupper(op);

        switch (op)
        {
        case 'P':
            if(lista_vazia(lista) == false){
                print_num(lista);
            } 
            break;

        case 'A':   
            add_num(lista);
            break;

        case 'M':
            if(lista_vazia(lista) == false){
                mean_num(lista);
            } 
            break;

        case 'S':
            if(lista_vazia(lista) == false){
                smallest_num(lista);
            }
            break;

        case 'L':
             if(lista_vazia(lista) == false){
                largest_num(lista);
            }    
            break;

        case 'Q':   
            cout << "Goodbye" << "\n";
            break;  
        
        default:
            cout << "Unknown selection, please try again" << "\n";
            break;
        }

    } while (op != 'Q');

    return 0;
}

void menu() {
    cout << "\n";
    cout << "P - Print numbers" << "\n";
    cout << "A - Add a number" << "\n";
    cout << "M - Display mean of the numbers" << "\n";
    cout << "S - Display the smallest number" << "\n";
    cout << "L - Display the largest number" << "\n";
    cout << "Q - Quit" << "\n";
    cout << "\nEnter your choice:" << "\n";
}

bool lista_vazia(vector <int> l){
    if(l.empty() == 1){
        cout << "[] - the list is empty" << "\n";
        return true;
    } else {
        return false;
    }
}

void print_num(vector <int> l){
    cout << "[ ";

    for(size_t i{0}; i < l.size(); ++i){
        cout << l.at(i) << " ";
    }

    cout << "]" << "\n";
}

void add_num(vector <int> &l){
    int num;
    cin >> num;
    l.push_back(num);
    cout << num << " was added" << "\n";
}

void mean_num(vector <int> l){
    double mean {0};

    for(size_t i{0}; i < l.size(); ++i){
        mean += l.at(i);
    }

    mean = mean / l.size();
    cout << "The mean is " << mean << "\n";
}

void smallest_num(vector <int> l){
    int menor = l.at(0);

    for(size_t i{1}; i < l.size(); ++i){ //?
        if(menor > l.at(i))
            menor = l.at(i);
    }

    cout << "The smallest number is " << menor << "\n";
}

void largest_num(vector <int> l){
    int maior = l.at(0);

    for(size_t i{1}; i < l.size(); ++i){ //?
        if(maior < l.at(i))
            maior = l.at(i);
    }

    cout << "The biggest number is " << maior << "\n";
}       

