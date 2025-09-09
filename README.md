# 🏏 Upcountry Warriors Management System

A simple C++ console-based management system for handling cricket players and teams.
The system allows adding, editing, deleting, searching, and managing players and teams, with persistent storage using text files.

📂 Project Structure <br>
├── main.cpp        # Main source code <br>
├── Makefile.win    # Makefile (Windows - Code::Blocks/MinGW)<br>
├── players.txt     # Sample player data<br>
├── teams.txt       # (Auto-generated) Team data file<br>

# ✨ Features

# + Player Management
- Add new players (with validation for unique registration numbers)
- Display all players
- Edit player details
- Delete players
- Search by registration number or name
- Store/retrieve players from players.txt

# + Team Management
- Create new teams
- Assign players to teams (up to 2 per player)
- View team details
- Edit and delete teams
- View all teams
- Store/retrieve teams from teams.txt

# + Authentication
- Simple login system (default credentials:
  - Username: oshan
  - Password: oshan2024)

# + Persistence
- Players and teams are saved in text files for reuse between sessions.

# 🛠️ Requirements
- C++11 or later
- Windows (Makefile is configured for Code::Blocks/MinGW)
- Alternatively, you can compile with g++ on Linux/macOS.

# 🚀 How to Build & Run
# +Using G++ (Linux/macOS/Windows with MinGW):
    g++ main.cpp -o management
    ./management

# Using Code::Blocks (Windows):
  1.Open Makefile.win in Code::Blocks.
  2.Build & Run the project.

# 👉 Teams will be stored in teams.txt after you create them via the system.

# 📸 Demo (Console Output)
# --- Upcountry Warriors Management System ---
  1. Display Players Information
  2. Add New Player
  3. Manage Teams
  4. Search Player
  5. Delete Player
  6. Edit Player
  7. Logout
  8. Exit
  Enter your choice:

# 🔒 Login Credentials
- Username: oshan
- Password: oshan2024

# 👨‍💻 Author
+ Oshan Nethsara
(Software Engineering Student, passionate about OOP and system design)
