#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Define a Task structure
// Define a Task structure
struct Task {
    int id;
    string description;
    int priority; // Lower value = Higher priority
    bool completed;

    // Default constructor
    Task() : id(0), description(""), priority(0), completed(false) {}

    // Parameterized constructor
    Task(int id, string description, int priority) 
        : id(id), description(description), priority(priority), completed(false) {}

    // Equality operator for comparison in unordered_map
    bool operator==(const Task& other) const {
        return id == other.id;
    }

    // Less-than operator for priority_queue (Min-Heap based on task priority)
    bool operator<(const Task& other) const {
        return priority > other.priority; // Lower priority value means higher priority
    }
};


// Task Manager class
class TaskManager {
private:
    priority_queue<Task> taskQueue;
    unordered_map<int, Task> taskMap; // For efficient search and task management
    int taskIdCounter;

public:
    TaskManager() : taskIdCounter(1) {}

    // Add a task to the queue
    void addTask(string description, int priority) {
        Task newTask(taskIdCounter, description, priority);
        taskQueue.push(newTask);
        taskMap[taskIdCounter] = newTask;
        taskIdCounter++;
        cout << "Task added successfully!" << endl;
    }

    // Remove a task by ID
    void deleteTask(int id) {
        if (taskMap.find(id) != taskMap.end()) {
            taskMap.erase(id); // Just erase from map
            rebuildTaskQueue(); // Rebuild the queue after deletion
            cout << "Task removed successfully!" << endl;
        } else {
            cout << "Task ID not found!" << endl;
        }
    }

    // Mark a task as completed
    void markTaskAsCompleted(int id) {
        if (taskMap.find(id) != taskMap.end()) {
            taskMap[id].completed = true;
            rebuildTaskQueue(); // Rebuild the queue to reflect completion
            cout << "Task marked as completed!" << endl;
        } else {
            cout << "Task ID not found!" << endl;
        }
    }

    // Display all tasks
    void displayTasks() {
        if (taskQueue.empty()) {
            cout << "No tasks to display!" << endl;
            return;
        }

        priority_queue<Task> tempQueue = taskQueue; // Copy to avoid modification
        while (!tempQueue.empty()) {
            Task task = tempQueue.top();
            tempQueue.pop();
            cout << "ID: " << task.id << ", Description: " << task.description
                << ", Priority: " << task.priority
                << ", Status: " << (task.completed ? "Completed" : "Pending") << endl;
            cout << "-----------------------------" << endl;
        }
    }

    // Search for a task by ID
    void searchTask(int id) {
        if (taskMap.find(id) != taskMap.end()) {
            Task task = taskMap[id];
            cout << "ID: " << task.id << ", Description: " << task.description
                << ", Priority: " << task.priority
                << ", Status: " << (task.completed ? "Completed" : "Pending") << endl;
        } else {
            cout << "Task ID not found!" << endl;
        }
    }

    // Rebuild the priority queue after deletion or completion
    void rebuildTaskQueue() {
        priority_queue<Task> newQueue;
        for (const auto& pair : taskMap) {
            newQueue.push(pair.second);
        }
        taskQueue = newQueue;
    }
};

// Driver function
int main() {
    TaskManager manager;

    int choice;
    do {
        cout << "\n1. Add Task\n2. Delete Task\n3. Mark Task as Completed\n4. View Tasks\n5. Search Task\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string desc;
                int priority;
                cout << "Enter task description: ";
                cin.ignore();
                getline(cin, desc);
                cout << "Enter task priority (lower is higher priority): ";
                cin >> priority;
                manager.addTask(desc, priority);
                break;
            }
            case 2: {
                int id;
                cout << "Enter task ID to delete: ";
                cin >> id;
                manager.deleteTask(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter task ID to mark as completed: ";
                cin >> id;
                manager.markTaskAsCompleted(id);
                break;
            }
            case 4: {
                manager.displayTasks();
                break;
            }
            case 5: {
                int id;
                cout << "Enter task ID to search: ";
                cin >> id;
                manager.searchTask(id);
                break;
            }
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
