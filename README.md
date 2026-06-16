# HEC Standard GPA Calculator

A C++ console application that calculates semester GPA according to Pakistan's HEC (Higher Education Commission) grading standard, and automatically generates a styled HTML report card that opens in the browser.

## Features

- Calculates GPA based on official HEC grading scale (percentage to grade point mapping)
- Object-oriented design using composition (`Student` class contains a vector of `Course` objects)
- File-based student record storage — returning students can retrieve their saved data by roll number
- Dynamically generates a styled HTML/CSS report card using the calculated results
- Automatically opens the generated report card in the default browser

## How It Works

1. User enters their roll number
2. If the roll number already exists in `students.txt`, their saved data is loaded and a report card is generated
3. If not, the user enters their name, semester, number of courses, and marks for each course
4. The program calculates GPA using the HEC grading scale (read from `grading_scale.txt`)
5. Student data is saved to `students.txt`
6. A report card is generated from `template.html` with the student's data filled in, then opened in the browser

## Technologies Used

- C++ (OOP, file handling, STL vectors)
- HTML/CSS (report card design)

## Files

- `main.cpp` — main program logic
- `template.html` — report card template with placeholders
- `style.css` — report card styling
- `grading_scale.txt` — HEC percentage-to-grade-point mapping
- `students.txt` — saved student records

## How to Run

```bash
g++ main.cpp -o main
./main
```

## Author

Amna Habib — Software Engineering student, PMAS Arid Agriculture University Rawalpindi
