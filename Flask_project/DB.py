import pymysql

db = pymysql.connect(
    host="localhost",
    user="root",
    passwd="1234",
    db="blog",
    charset="utf8")
    
cursor = db.cursor()

sql = "SELECT * from project"
cursor.execute(sql)
value = cursor.fetchall()