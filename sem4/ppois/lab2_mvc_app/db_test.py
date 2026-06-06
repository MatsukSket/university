import sqlite3

conn = sqlite3.connect('students.db') # create or open (if already exists)
cursor = conn.cursor()

# # define table structure
# cursor.execute('''
#     CREATE TABLE IF NOT EXISTS students (
#         id INTEGER PRIMARY KEY AUTOINCREMENT,
#         student_name TEXT, father_name TEXT, father_income REAL,
#         mother_name TEXT, mother_income REAL, brothers INTEGER, sisters INTEGER
#     )
# ''')
#
# cursor.execute('''
#     INSERT INTO students (student_name, father_name, father_income, mother_name, mother_income, brothers, sisters)
#     VALUES (?, ?, ?, ?, ?, ?, ?)
# ''', ('Иванов Иван', 'Иванов Петр', 3000.0, 'Иванова Ирина', 1000.0, 1, 0))
#
# conn.commit()


cursor.execute('SELECT * FROM students')

student_list = cursor.fetchall()

print("Вся бд:")
for student in student_list:
    print(student)

conn.close()

print("successsul")

