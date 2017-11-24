/*
 * App.cpp
 * This class contains the main method for PhoneBook Application
 * Underlying data structure for this application is a Binary Search Tree
 *
 *  Created on: Nov 21, 2017
 *      Author: Shaila Hirji
 *      Supervisor:Dr Fatma Serce
 */

#include<iostream>
#include<fstream>
#include <sstream>
#include "BinarySearchTree.h"
#include "Contact.h"
using namespace std;

void loadTree();
string searchContact(string &fname, string &lname);
int nameValidity(string name);
int phoneValidity(string phone);
char operationPrompt();

//accesible to all methods in this class

string fileName;
BinarySearchTree<Contact>* phoneBookTree;

int main() {

    cout << "***My Phonebook Application***" << endl;
    cout << "Please choose operation:\n";

    BinarySearchTree < Contact > tree; // create BST

    phoneBookTree = &tree; //points to the tree with contacts

    //----------------- to do always--------------------------

    bool run = true;
    char userRequest;
    while (run) // to exit, user enters q.
    {
        userRequest = operationPrompt();
        switch (userRequest) {

            case 'A':
            case 'a': {

                //get user input, name and phone#
                string _name, _phone;
                cout << "Enter name:";
                getline(cin, _name);
                cout << "Enter phone:";
                getline(cin, _phone);
                cout << endl;

                //break user name input into fname and lname
                string fname, lname;
                istringstream iss(_name);
                iss >> fname;
                iss >> lname;

                //check validity of user input
                while (!nameValidity(fname) || !nameValidity(lname)
                       || !phoneValidity(_phone)) {
                    cout << "Please re-enter information" << endl;
                    cout << "Enter name:";
                    getline(cin, _name);
                    cout << "Enter phone:";
                    getline(cin, _phone);
                    cout << endl;
                    istringstream iss(_name);
                    iss >> fname;
                    iss >> lname;
                }

                //if user's input is valid, insert into tree
                Contact person(fname, lname, _phone);
                phoneBookTree->insert(person);

            }
                break;

            case 'L':
            case 'l': {

                loadTree(); // loads tree with contact information from desired file
                cout << endl;
            }
                break;

            case 'S':
            case 's': {

                //get user input
                string _name, _phone;
                cout << "Enter name:";
                getline(cin, _name);

                string fname, lname; //break user name input into fname and lname
                istringstream iss(_name);
                iss >> fname;
                iss >> lname;

                //check for name validity
                while (!nameValidity(fname) || !nameValidity(lname)) {
                    cout << "Please re-enter information" << endl;
                    cout << "Enter name:";
                    getline(cin, _name);
                    istringstream iss(_name);
                    iss >> fname;
                    iss >> lname;
                }
                cout <<searchContact(fname, lname) << endl; //if contact exists, print contacts phone number, else prints contact doesn't exists
                cout << endl;

            }
                break;

            case 'P':
            case 'p': {

                //print all contacts in the BST, ascending order by traversing tree inorder
                phoneBookTree->inOrder();
                //count number of contacts on record/ on BST
                int contacts = phoneBookTree->nodeCount();
                cout << contacts;
                cout << " contacts..." << endl;
                cout << endl;

            }
                break;

            case 'F':
            case 'f': {

                string _name;
                cout << "Enter name:";
                getline(cin, _name);
                cout << endl;
                string fname, lname; //break user input into fname and lname
                istringstream iss(_name);
                iss >> fname;
                iss >> lname;

                //check if user input is a valid name, letters only
                while (!nameValidity(fname) || !nameValidity(lname)) {
                    cout << "Please re-enter information" << endl;
                    cout << "Enter name:";
                    getline(cin, _name);
                    istringstream iss(_name);
                    iss >> fname;
                    iss >> lname;
                }

                Contact person(fname, lname, "");

                person = phoneBookTree->search(person);//check if contact exists
                if (person.getContactPhone() == "") {
                    cout << "Contact doesn't exists in PhoneBook" << endl;
                    cout << endl;
                } else {

                    //if contact in tree is less than Contact to filter by, print contact
                    LinkedList < Contact > *ll = new LinkedList<Contact>();
                    phoneBookTree->filter(person, ll);
                    cout << *ll;
                    //print number of contacts that appear before contact to filter by
                    cout << ll->length() << " Contacts..." << endl;
                    cout << endl;
                }

            }
                break;

            case 'Q':
            case 'q': {

                run = false; //flag
                cout << "Bye!";
                return 0;
            }
            default:
                cout << "\nPlease, try again.\n";
        }
    }
}

/*
 * Prints operation prompt
 */
char operationPrompt() {
    char userWants;
    cout
            << " A (Add) | L (Load) | S (Search) | P (Print) | F (Filter)| Q(Quit): ";
    cin >> userWants;
    cin.ignore();
    return userWants;

}

/*
 * This method load's the BST via the text file
 */
void loadTree() {

    //    string fileName;
    cout << "Enter file name:";
    cin >> fileName; // get the file name

    ifstream myFile("/Users/shaila/Desktop/Lion_c++/Assignment4/" + fileName);
    if (myFile.is_open()) {

        while (!myFile.eof()) { //

            string Fname = "";
            string Lname = "";
            string phone = "";

            myFile >> Fname; //get first name
            myFile >> Lname; //get last name
            myFile >> phone; //get phone

            //if file has no empty lines, add them to tree, if empty line, go to next line
            if (Fname != "" && Lname != "" && phone != "") {
                Contact person = Contact(Fname, Lname, phone);
                phoneBookTree->insert(person); // add the person to the tree

            }
        }
        myFile.close();
    } else
        cout << "Unable to open file" << endl;
}

/*
 * This method searches for a specific contact within the BST
 */
string searchContact(string &fname, string &lname) {

    Contact person = Contact(fname, lname, "");
    person = phoneBookTree->search(person);

    if (person.getContactPhone() == "") { // phone field wasn't updated
        return "Contact not found";
    }
    return "Phone: "+person.getContactPhone(); // return's person's phone number

}

/*
 * Checks validity of user's input for names, input contains letters only
 * returns 1 if name contains letters only
 * returns 0 if name contains characters other than letters
 */
int nameValidity(string name) {
    char c;

    // Iterate through the string one letter at a time.
    for (int i = 0; i < name.length(); i++) {
        c = name.at(i);         // Get a char from string
        // if it's NOT within these bounds, then it's not a character
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
            return 0;		//number used instead of alphabet
        }
    }

    return 1;		//all ok!
}

/*
 * This method checks if the phone number entered by the user is valid, input doesn't include letters
 *  returns 1 if phone contains numbers only
 * returns 0 if name contains characters other than numbers
 */
int phoneValidity(string phoneNumber) {
    char c;

    // Iterate through the string one number at a time.
    for (int i = 0; i < phoneNumber.length(); i++) {
        c = phoneNumber.at(i);         // Get a char from string
        // if it's NOT within these bounds, then it's not a character
        if (!(c >= '1' && c <= '9')) {
            return 0;		//number used instead of alphabet
        }
    }
    return 1;		//all ok!
}

