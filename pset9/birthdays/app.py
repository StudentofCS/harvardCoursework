import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# app.debug = True
app.secret_key = os.urandom(24)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        # Retrieve the submitted form data
        name = request.form.get("name")
        day = request.form.get("day")
        month = request.form.get("month")

        thirtyDays = ['4', '6', '9', '11']
        february = ['2']

        # Check if the months with 30 days have a valid date
        if ((month in thirtyDays) and (day > '30')):
            flash("Please select a valid date!")
            return redirect("/")
        # Check if february has a valid date
        elif ((month in february) and (day > '29')):
            flash("Please select a valid date!")
            return redirect("/")
        # If valid dates, insert birthday into db
        else:
            db.execute("INSERT INTO birthdays (name, day, month) VALUES (?, ?, ?)", name, day, month)
            return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", birthdays=birthdays)

# Route that renders the page where you can enter the new data for a birthday
# @app.route("/edit", methods=["GET", "POST"])
# def edit():

#     if request.method == "POST":
#         birthday = request.form.get("editId")
#         editBirthday = db.execute("SELECT * FROM birthdays WHERE id=?", birthday)[0]

#         return render_template("edit.html", birthday=editBirthday)
#     else:

#         return render_template("edit.html")

# Route that will delete a birthday from the database
@app.route("/delete", methods=["POST"])
def delete():

    id = request.form.get("deleteId")
    db.execute("DELETE FROM birthdays WHERE id=?", id)

    return redirect("/")

# Route to insert the new edited information for a birthday
@app.route("/insert", methods=["POST"])
def insert():

    name = request.form.get("name")
    day = request.form.get("day")
    month = request.form.get("month")

    thirtyDays = ['4', '6', '9', '11']
    february = ['2']

    # Check if the months with 30 days have a valid date
    if ((month in thirtyDays) and (day > '30')):
        flash("Please select a valid date!")
        return redirect("/")
    # Check if february has a valid date
    elif ((month in february) and (day > '29')):
        flash("Please select a valid date!")
        return redirect ("/")
    else:
        db.execute("UPDATE birthdays SET day = ?, month = ? WHERE id = ?", day, month, name)

        return redirect("/")
