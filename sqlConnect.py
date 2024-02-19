import pyodbc

def conectar():
    global cursor
    server = 'CA-C-00654\SQLEXPRESS'
    database = 'python'

    cnxn = pyodbc.connect('DRIVER={ODBC Driver 17 for SQL Server};SERVER='+server+';DATABASE='+database+';Trusted_Connection=yes')
    cursor = cnxn.cursor()
    

# cursor.execute(f"CREATE TABLE ALUNO (ID INT, NOME VARCHAR(255))") #comando que sera executado
# cursor.commit() 

conectar()

cursor.execute('SELECT ID, Nome FROM Aluno')
row = cursor.fetchone()

while row:
    print(row[0])
    print(row[1])
    row = cursor.fetchone()

print("Inserido com sucesso!")
