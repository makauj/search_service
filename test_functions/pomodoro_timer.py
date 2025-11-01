import time
import os

# --- Configuration ---
# All times are in seconds
WORK_TIME = 25 * 60       # 25 minutes
SHORT_BREAK_TIME = 5 * 60 # 5 minutes
LONG_BREAK_TIME = 15 * 60 # 15 minutes
POMODOROS_PER_CYCLE = 4   # Take a long break after 4 Pomodoros

def clear_console():
    """Clears the terminal screen."""
    # Check OS type: 'nt' for Windows, anything else (like 'posix') for Linux/Mac
    os.system('cls' if os.name == 'nt' else 'clear')

def countdown_timer(duration, stage_name, pomodoro_count):
    """
    Counts down the specified duration and updates the console display.

    Args:
        duration (int): The time in seconds for the countdown.
        stage_name (str): The name of the current stage (e.g., "Work", "Short Break").
        pomodoro_count (int): The number of completed Pomodoros.
    """
    print(f"--- Pomodoro Timer --- | Completed Pomodoros: {pomodoro_count}")

    while duration >= 0:
        mins, secs = divmod(duration, 60)
        time_format = f"{mins:02d}:{secs:02d}"

        # Print the status, flush=True ensures it prints immediately
        print(f"[{stage_name}] Time Remaining: {time_format}", end='\r', flush=True)

        try:
            time.sleep(1)
        except KeyboardInterrupt:
            # Handle user interruption (Ctrl+C)
            clear_console()
            print("\nTimer stopped by user. Goodbye!")
            raise  # Re-raise the exception to break the outer loop

        duration -= 1

    clear_console()
    print(f"\n[DING DING!] {stage_name} is over! Starting next stage...\n")
    # A simple indicator that the time is up
    print("*************************************************")
    print("***** Take a deep breath and switch tasks *****")
    print("*************************************************\n")
    time.sleep(3) # Pause for 3 seconds after a stage ends


def run_pomodoro():
    """The main loop for the Pomodoro timer application."""
    pomodoros_completed = 0

    clear_console()
    print("Welcome to the Python Pomodoro Timer!")
    print(f"Work: {WORK_TIME // 60}m | Short Break: {SHORT_BREAK_TIME // 60}m | Long Break: {LONG_BREAK_TIME // 60}m\n")
    print("Press Ctrl+C to stop the timer at any time.")

    try:
        while True:
            # 1. Work Session
            countdown_timer(WORK_TIME, "WORK", pomodoros_completed)

            # Increment the counter after a successful work session
            pomodoros_completed += 1

            # 2. Determine Break Type
            if pomodoros_completed % POMODOROS_PER_CYCLE == 0:
                # 2a. Long Break
                countdown_timer(LONG_BREAK_TIME, "LONG BREAK", pomodoros_completed)
            else:
                # 2b. Short Break
                countdown_timer(SHORT_BREAK_TIME, "SHORT BREAK", pomodoros_completed)

    except KeyboardInterrupt:
        # Exit message for the main loop
        pass

if __name__ == "__main__":
    run_pomodoro()
