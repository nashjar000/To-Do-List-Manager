#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Function prototypes
void displayMenu();
void addTask(vector<string> &tasks);
void viewTasks(const vector<string> &tasks, const vector<bool> &completed);
void markTaskAsComplete(vector<string> &tasks, vector<bool> &completed);
void removeTask(vector<string> &tasks, vector<bool> &completed);
void saveToFile(const vector<string> &tasks, const vector<bool> &completed);
void addTask(vector<string> &tasks, vector<bool> &completed);
void openFile(vector<string> &tasks, vector<bool> &completed);

// Main function
int main() {
    vector<string> tasks; // Vector to store tasks
    vector<bool> completed; // Vector to store whether tasks are completed or not

    // Display menu
    int choice;
    do {
        displayMenu(); // Display the menu options
        cout << "Enter your choice: ";
        cin >> choice; // Read user choice
        cout << endl; // Add an empty line for readability

        switch(choice) {
            case 1:
                addTask(tasks); // Call function to add a new task
                completed.push_back(false); // New tasks are not completed
                break;
            case 2:
                viewTasks(tasks, completed); // Call function to view tasks
                break;
            case 3:
                markTaskAsComplete(tasks, completed); // Call function to mark a task as complete
                break;
            case 4:
                removeTask(tasks, completed); // Call function to remove a task
                break;
            case 5:
                saveToFile(tasks, completed); // Call function to save tasks to a file
                break;
            case 6:
                openFile(tasks, completed); // Call function to open tasks from a file
                break;
            case 7:
                cout << "Goodbye!" << endl; // Display farewell message
                break;
            default:
                // Handle invalid choice
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 7); // Continue the loop until user chooses to quit

    return 0;
}

// Function to display the menu options
void displayMenu() {
    cout << "To-Do List Manager" << endl;
    cout << "------------------" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View Tasks" << endl;
    cout << "3. Mark Task as Complete" << endl;
    cout << "4. Remove Task" << endl;
    cout << "5. Save To-Do List to File" << endl;
    cout << "6. Open To-DO List from File" << endl;
    cout << "7. Quit" << endl;
    cout << "------------------" << endl;
}

// Function to add a new task to the list
void addTask(vector<string> &tasks) {
    string newTask;
    cout << "Enter task: ";
    cin.ignore(); // Ignore newline character
    getline(cin, newTask); // Read input until newline
    tasks.push_back(newTask); // Add task to vector
    cout << "Task added successfully!" << endl; // Display success message
}

// Function to view the list of tasks
void viewTasks(const vector<string> &tasks, const vector<bool> &completed) {
    cout << "To-Do List:" << endl;
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". " << tasks[i] << " ";
        
        // Display a single checkbox regardless of completion status
        cout << (completed[i] ? "[x]" : "[ ]") << endl;
    }
    cout << "------------------" << endl;
}


// Function to mark a task as complete
void markTaskAsComplete(vector<string> &tasks, vector<bool> &completed) {
    viewTasks(tasks, completed); // Display tasks for the user to choose from
    int taskNumber;
    cout << "Enter the number of the task you want to mark as complete: ";
    cin >> taskNumber; // Read user input

    // Check if the index is valid
    if (taskNumber >= 1 && taskNumber <= tasks.size()) {
        // Update the corresponding element in the completed vector
        completed[taskNumber - 1] = true;
        cout << "Task marked as completed!" << endl;
    } else {
        cout << "Invalid index. Please try again." << endl;
    }
}

// Function to remove a task from the list
void removeTask(vector<string> &tasks, vector<bool> &completed) {
    viewTasks(tasks, completed); // Display tasks for the user to choose from
    int taskNumber;
    cout << "Enter task number to remove: ";
    cin >> taskNumber; // Read user input

    // Check if task number is valid
    if (taskNumber >= 1 && taskNumber <= tasks.size()) {
        tasks.erase(tasks.begin() + taskNumber - 1); // Remove task from tasks vector
        completed.erase(completed.begin() + taskNumber - 1); // Remove corresponding completion status
        cout << "Task removed." << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}

// Function to save tasks to a file
void saveToFile(const vector<string> &tasks, const vector<bool> &completed) {
    string filename;
    cout << "Enter the name of the file to save (include '.txt' at the end): ";
    cin >> filename; // Read user input

    // Check if the filename ends with ".txt"
    if (filename.find(".txt") == string::npos) {
        filename += ".txt"; // If not, add ".txt" to the end
    }

    ofstream outputFile(filename); // Open the file with the specified filename

    if (outputFile.is_open()) {
        // Write each task along with its completion status to the file
        for (size_t i = 0; i < tasks.size(); ++i) {
            outputFile << tasks[i] << (completed[i] ? " [x]" : " [ ]") << endl;
        }
        outputFile.close(); // Close the file
        cout << "To-Do List saved to file." << endl;
    } else {
        cout << "Unable to open file." << endl; // Display error message if file could not be opened
    }
}

// Function to open tasks from a file
void openFile(vector<string> &tasks, vector<bool> &completed) {
    string filename;
    cout << "Enter the name of the file to open (include '.txt' at the end): ";
    cin >> filename; // Read user input

    // Check if the filename ends with ".txt"
    if (filename.find(".txt") == string::npos) {
        filename += ".txt"; // If not, add ".txt" to the end
    }

    ifstream inputFile(filename); // Open the file with the specified filename

    // Used AI for this function to read where the | was in the file
    if (inputFile.is_open()) {
        // Read tasks and completion status from the file
        string line;
        while (getline(inputFile, line)) {
            // Trim trailing whitespace from the line
            size_t end = line.find_last_not_of(" \t");
            if (end != string::npos) {
                line = line.substr(0, end + 1);
            }
            string task;
            bool isCompleted = false; // Initialize as not completed
            // Check if "[x]" is present at the end of the line
            size_t found = line.find("[x]");
            if (found != string::npos && found == line.size() - 3) {
                isCompleted = true; // If "[x]" is found at the end, mark task as completed
                // Extract task name (excluding "[x]")
                task = line.substr(0, found);
            } else {
                // Check if "[ ]" is present at the end of the line
                found = line.find("[ ]");
                if (found != string::npos && found == line.size() - 3) {
                    task = line.substr(0, found); // Extract task name (excluding "[ ]")
                } else {
                    task = line; // If neither "[x]" nor "[ ]" is found, the entire line is the task name
                }
            }
            tasks.push_back(task); // Add task to tasks vector
            completed.push_back(isCompleted); // Add completion status to completed vector
        }
        inputFile.close(); // Close the file
        cout << "To-Do List loaded from file." << endl;
    } else {
        cout << "Unable to open file." << endl; // Display error message if file could not be opened
    }
}
