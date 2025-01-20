#include <iostream>
#include <string>
using namespace std;

// Constants
const int MAX_SPECIALIZATION = 20;
const int MAX_QUEUE = 5;

// Struct to manage each specialization's data
struct Specialization {
    string names[MAX_QUEUE];
    int status[MAX_QUEUE];  // 0: regular, 1: urgent
    int queue_length = 0;   // Number of patients in the specialization
};

// Array of specializations
Specialization specializations[MAX_SPECIALIZATION + 1];

int menu() {
    int choice = -1;
    while (choice == -1) {
        cout << "\nEnter your choice:\n";
        cout << "1) Add new patient\n";
        cout << "2) Print all patients\n";
        cout << "3) Get next patient\n";
        cout << "4) Exit\n";

        cin >> choice;

        if (!(1 <= choice && choice <= 4)) {
            cout << "Invalid choice. Try again\n";
            choice = -1;  // loop keep working
        }
    }
    return choice;
}

// Move each patient to the left in the queue
void shift_left(Specialization &spec) {
    for (int i = 1; i < spec.queue_length; ++i) {
        spec.names[i - 1] = spec.names[i];
        spec.status[i - 1] = spec.status[i];
    }
    spec.queue_length--;
}

// Move each patient to the right in the queue
void shift_right(Specialization &spec) {
    for (int i = spec.queue_length - 1; i >= 0; --i) {  // critical to start from END
        spec.names[i + 1] = spec.names[i];
        spec.status[i + 1] = spec.status[i];
    }
    spec.queue_length++;
}

bool add_patient() {
    int spec_index;
    string name;
    int st;

    cout << "Enter specialization, name, status: ";
    cin >> spec_index >> name >> st;

    Specialization &spec = specializations[spec_index];

    if (spec.queue_length >= MAX_QUEUE) {
        cout << "Sorry, we can't add more patients for this specialization\n";
        return false;
    }

    if (st == 0) {  // Regular, add to end
        spec.names[spec.queue_length] = name;
        spec.status[spec.queue_length] = st;
        spec.queue_length++;
    } else {  // Urgent, add to beginning
        shift_right(spec);
        spec.names[0] = name;
        spec.status[0] = st;
    }

    return true;
}

void print_patient(const Specialization &spec, int spec_index) {
    if (spec.queue_length == 0)
        return;

    cout << "There are " << spec.queue_length << " patients in specialization " << spec_index << "\n";
    for (int i = 0; i < spec.queue_length; ++i) {
        cout << spec.names[i] << " ";
        if (spec.status[i])
            cout << "urgent\n";
        else
            cout << "regular\n";
    }
    cout << "\n";
}

void print_patients() {
    cout << "****************************\n";
    for (int spec_index = 0; spec_index < MAX_SPECIALIZATION; ++spec_index) {
        print_patient(specializations[spec_index], spec_index);
    }
}

void get_next_patient() {
    int spec_index;
    cout << "Enter specialization: ";
    cin >> spec_index;

    Specialization &spec = specializations[spec_index];

    if (spec.queue_length == 0) {
        cout << "No patients at the moment. Have rest, Dr\n";
        return;
    }

    // Let the patient go to the doctor
    cout << spec.names[0] << " please go with the Dr\n";

    // Remove the patient from position 0
    shift_left(spec);
}

void hospital_system() {
    while (true) {
        int choice = menu();

        if (choice == 1)
            add_patient();
        else if (choice == 2)
            print_patients();
        else if (choice == 3)
            get_next_patient();
        else
            break;
    }
}

int main() {
    hospital_system();
    return 0;
}
