from flask import Flask, render_template
from arduino_io import ArduinoIO
import platform


app = Flask(__name__)

# Track the state of the button
button_state = {"closed": False}

if platform.system() == "Windows":
    arduino = ArduinoIO("COM3", 9600)
else:
    arduino = ArduinoIO("/dev/ttyACM0", 9600)


@app.route("/")
def index():
    return render_template("index.html", closed=button_state["closed"])


@app.route("/toggle-button", methods=["POST"])
def toggle_button():
    # Toggle the button state
    button_state["closed"] = not button_state["closed"]

    arduino.write(f"<{'C' if button_state['closed'] else 'O'}>")
    return ("", 204)


if __name__ == "__main__":
    app.run(debug=False, host="0.0.0.0")
