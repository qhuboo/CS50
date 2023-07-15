CREATE TABLE students (
    id INTEGER, 
    student_name TEXT, 
    PRIMARY KEY(id)
);

CREATE TABLE houses (
    house TEXT,
    head TEXT,
    PRIMARY KEY(house)
);

CREATE assignments (
    student_id INTEGER,
    house TEXT,
    FOREIGN KEY(student_id) REFERENCES students(id),
    FOREIGN KEY(house) REFERENCES houses(house)
);  
