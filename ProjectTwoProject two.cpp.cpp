#include <iostream> //Standard input/output stream
#include <fstream> // File stream
#include <string> // String manipulation
#include <vector> // Vector container
#include <algorithm> // Algorithms for sorting

using namespace std; //Namespace declaration to avoid repetition of std::

// Structure to hold informationinformation about a course 
struct Course {
	string courseNumber; // Course number
	string courseTitle; // Course title
	vector<string> prerequisites; // Prerequisites for the course
};

vector<Course> courses; // Vector to store Course objects

// Function to load data from a file into the courses vector
void loadDataStructure(const string& fileName) {
	ifstream file(fileName); //Open the file for reading
	if (!file.is_open()) { // Check if file opening failed
		cout << "Unable to open file: " << fileName << endl; //Print error message
		return; //Exit function
	}

	string line; //String to store each line of the file
	while (getline(file, line)) { // Read each line of the file
		Course course; // Create a course object to store course information
		size_t pos = line.find(","); // Find the position of the first comma
		course.courseNumber = line.substr(0, pos); // Extract course number
		line.erase(0, pos + 1); // Erase the extracted part from the line
		pos = line.find(","); // Find the position of the next comma
		course.courseTitle = line.substr(0, pos); // Extract course title
		line.erase(0, pos + 1); // Erase the extracted part from the line

		// Extract and store prerequisites
		while (!line.empty()) {
			pos = line.find(","); // Find the position of the next comma
			string prerequisites = line.substr(0, pos); // Extract preresite
			course.prerequisites.push_back(prerequisites); // Store prerequisite
			if (pos == string::npos) break; // If no more commas, exit loop
			line.erase(0, pos + 1); // Erase the extracted part from the line
		}

		courses.push_back(course); // Add the Course objectobjects to the courses vector
	}

	file.close(); // Close the file
}

// Function to print a list of courses in alphanumeric order
void printCourseList() {
	// Sort the courses vectorVector based on course numbers
	sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
		return a.courseNumber < b.courseNumber;
		});

	cout << "Here is a list of course:" << endl; // Print header
	// Loop through each course and print its number and title
	for (const auto& course : courses) {
		cout << course.courseNumber << ", " << course.courseTitle << endl;
	}
}

// Function to print information about a specific course
void printCourse(const string& courseNumber) {
	// Find the course with the given course number
	auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {
		return c.courseNumber == courseNumber;
		});

	if (it != courses.end()) { // Check if course is found
		cout << it->courseNumber << ", " << it->courseTitle << endl; // Print course number and title
		cout << "Prerequisites: ";
		if (it->prerequisites.empty()) { // Check if there are no prerequisites
			cout << "None" << endl; // Print "None"
		}
		else {
			// Loop through prerequisites and print each one
			for (const auto& prerequisite : it->prerequisites) {
				cout << endl;
			}
		}
	}
	else { // If course is not found
		cout << "Course not found." << endl;
	}
}

int main() {
	string fileName; // String to store file name
	int choice; // Integer to store user's choice
	string courseNumber; // String to store course number

	cout << "Welcome to the course planned." << endl; //Print welcome message
	do { // Start a do-while loop
	//Print menu options
		cout << "1. Load Data Structure." << endl;
		cout << "2.Print Course List." << endl;
		cout << "3.Print Course." << endl;
		cout << "9. Exit" << endl;
		cout << "What would you like to do? "; // Prompt user for choice
		cin >> choice; // Read user's choice

		switch (choice) { // Switch statement based on user's choice
		case 1: // If user chooses option 1
			cout << "Enter the file name: "; // Prompt for file name
			cin >> fileName; // Read file name from user
			loadDataStructure(fileName); // Call function to load data from file
			break; // Exit switch statement
		case 2: // If user chooses option 2
			printCourseList(); // Call function to print course list
			break; // Exit switchswitch statement
		case 3: // If user chooses option 3
			cout << "What course do you want to know about? "; // Prompt for course number
			cin >> courseNumber; // Read course number from user
			printCourse(courseNumber); // Call function to print course information
			break; // Exit switch statement 
		default: // If user chooses and invalidinvalid option
			cout << choice << " is notit not a valid option." << endl; // Print error message
		}
	} while (choice != 9); // Continue loop until chooses to exit

	return 0; // Return 0 to indicate succeessfulsuccessful execution
}
		
