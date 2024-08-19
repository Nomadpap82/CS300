/* 
 * Author: Joshua Hale
 * Date: 2024-08-11
 * Project: CS300 Project Two - Advising Assistance Program
 * 
 * This program is designed to assist academic advisors at ABCU in managing course information.
 * It reads course data from a file, allows the user to interact with the data via a menu, and provides 
 * options to load data, print a sorted list of courses, and display course details along with prerequisites.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

// This structure defines a course, including its number, title, and prerequisites.
struct Course {
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

// This map holds all courses using the course number as the key.
std::map<std::string, Course> courses;

// Converts a given string to upper case. This is useful for case-insensitive comparisons.
std::string ToUpperCase(const std::string& str) {
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return upperStr;
}

// This function loads course data from a file into the global 'courses' map.
void LoadDataStructure(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::istringstream ss(line);
        std::string courseNumber, courseTitle, prerequisite;
        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.courseTitle = courseTitle;

        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        courses[course.courseNumber] = course;
    }

    file.close();
    std::cout << "Data loaded successfully!" << std::endl;
}

// Function to print a sorted list of courses
void PrintCourseList() {
    if (courses.empty()) {
        std::cout << "No courses loaded. Please load data first." << std::endl;
        return;
    }

    std::vector<std::string> courseKeys;
    for (const auto& pair : courses) {
        courseKeys.push_back(pair.first);
    }
    std::sort(courseKeys.begin(), courseKeys.end());

    std::cout << "\nHere is a sample schedule:\n" << std::endl;
    for (const auto& key : courseKeys) {
        std::cout << key << ", " << courses[key].courseTitle << std::endl;
    }
}

// Function to print information about a specific course
void PrintCourse(const std::string& courseNumber) {
    if (courses.empty()) {
        std::cout << "No courses loaded. Please load data first." << std::endl;
        return;
    }

    std::string upperCourseNumber = ToUpperCase(courseNumber);
    if (courses.find(upperCourseNumber) != courses.end()) {
        const Course& course = courses[upperCourseNumber];
        std::cout << course.courseNumber << ", " << course.courseTitle << std::endl;
        if (!course.prerequisites.empty()) {
            std::cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                std::cout << course.prerequisites[i];
                if (i != course.prerequisites.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "Prerequisites: None" << std::endl;
        }
    }
    else {
        std::cout << "Course not found." << std::endl;
    }
}

// Function to display the main menu
void DisplayMenu() {
    std::cout << "\n1. Load Data Structure." << std::endl;
    std::cout << "2. Print Course List." << std::endl;
    std::cout << "3. Print Course." << std::endl;
    std::cout << "9. Exit." << std::endl;
}

// The main function, which serves as the entry point of the program.
int main() {
    std::cout << "Welcome to the course planner.\n" << std::endl;

    int choice = 0;
    const std::string filename = "U:\\ProjectTwo\\CS 300 ABCU_Advising_Program_Input.csv";
    while (choice != 9) {
        DisplayMenu();
        std::cout << "\nWhat would you like to do? ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            LoadDataStructure(filename);
            break;
        case 2:
            PrintCourseList();
            break;
        case 3: {
            std::string courseNumber;
            std::cout << "\nWhat course do you want to know about? ";
            std::cin >> courseNumber;
            PrintCourse(courseNumber);
            break;
        }
        case 9:
            std::cout << "\nThank you for using the course planner!" << std::endl;
            break;
        default:
            std::cout << "\n" << choice << " is not a valid option." << std::endl;
            break;
        }
    }
    return 0;
}