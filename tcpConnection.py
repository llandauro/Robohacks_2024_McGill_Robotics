import socket
import keyboard
import threading
import time

# Define the server address and port
SERVER_ADDRESS = '192.168.137.177'  # Change this to your server's IP address
SERVER_PORT = 80  # Change this to your server's port

# Define the commands for controlling the robot
COMMANDS = {
    'o': 'O', # open storage door
    'c': 'C', # close storage door
    't':'T', #start turning the swiffer
    's':'S', # stop turning the swiffer
    'left': 'L',
    'right': 'R',
    'up': 'F',
    'down': 'B',
    None: 'X'
}

COMMAND_SUFFIX = '!'

timeToMoveForward = 0.5
timeToMoveBackward = timeToMoveForward * 3.1
def runAutonomyMountainRegion():
    global input_key
    start_time = time.time()
    while start_time + timeToMoveForward > time.time():
        input_key = COMMANDS['up'] + COMMAND_SUFFIX
    time.sleep(1)
    start_time = time.time()
    while start_time + timeToMoveBackward > time.time():
        input_key = COMMANDS['down'] + COMMAND_SUFFIX

# Function to handle user input
def handle_user_input():
    global isRunning
    global input_key
    while isRunning:
        try:
            input_key = COMMANDS[None] + COMMAND_SUFFIX
            if keyboard.is_pressed("right shift"):
                runAutonomyMountainRegion()
                continue
            for key, command in COMMANDS.items():
                if key is None: continue
                if keyboard.is_pressed(key):
                    input_key = command + COMMAND_SUFFIX
                    break

        except KeyboardInterrupt:
            isRunning = False
            break
        time.sleep(0.01)

isRunning = True
input_key = COMMANDS[None]

if __name__ == "__main__":
    try:
        # Create a TCP socket
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Connect to the server
        print("Connecting to server...")
        client_socket.connect((SERVER_ADDRESS, SERVER_PORT))
        print("Connected to server")

        # Start thread to handle user input
        input_thread = threading.Thread(target=handle_user_input)
        input_thread.daemon = True
        input_thread.start()
        
        while True:
            try:
                client_socket.sendall(input_key.encode())
                print(input_key)
            except Exception as e:
                print("Error sending command:", e)
            time.sleep(0.01)

    except KeyboardInterrupt:
        isRunning = False
        print("Keyboard interrupt. Exiting...")
    finally:
        client_socket.close()
        input_thread.join()

