from flask import Flask, render_template
import DB

app = Flask(__name__)

@app.route('/')
def Main():
    return render_template('Main.html')

@app.route('/Main')
def GetMain():
    return render_template('Main.html')

@app.route('/Console')
def GetConsole():
    return render_template('Console.html')

@app.route('/Results')
def GetResults():
    return render_template('Results.html', data_list=DB.value)

if __name__ == "__main__":
    app.run()