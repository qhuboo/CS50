import sqlite3
import csv

# Creating a connection to db
connect = sqlite3.connect("prophecy.db")

# Creating a cursor
cursor = connect.cursor()

# Create tables
cursor.execute("CREATE TABLE IF NOT EXISTS students (id INTEGER PRIMARY KEY AUTOINCREMENT, student_name TEXT)")
cursor.execute("CREATE TABLE IF NOT EXISTS houses (house TEXT, head TEXT, PRIMARY KEY(house))")
cursor.execute("CREATE TABLE IF NOT EXISTS assignments (student_id INTEGER, house TEXT, FOREIGN KEY(student_id) REFERENCES students(id), FOREIGN KEY(house) REFERENCES houses(house))")


with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    houses = []
    student_assignments = []
    students = []
    for row in reader:
        house = dict(house = row["house"], head = row["head"])
        if house not in houses:
            houses.append(house)
        student_assignments.append(dict(ID = row["id"], assignment = row["house"]))
        students.append(dict(ID = row["id"], student_name = row["student_name"]))

# Inserting into the houses table
for i in range(len(houses)):
    house = houses[i]["house"]
    head = houses[i]["head"]
    cursor.execute("INSERT INTO houses (house, head) VALUES (?, ?)", (house, head))
    connect.commit()

# Inserting into the assignments table
for i in range(len(student_assignments)):
    ID = student_assignments[i]["ID"]
    assignment = student_assignments[i]["assignment"]
    cursor.execute("INSERT INTO assignments (student_id, house) VALUES (?, ?)", (ID, assignment))
    connect.commit()

# Inserting into the students table
for i in range(len(students)):
    ID = students[i]["ID"]
    student_name = students[i]["student_name"]
    cursor.execute("INSERT INTO students (id, student_name) VALUES (?, ?)", (ID, student_name))
    connect.commit()
