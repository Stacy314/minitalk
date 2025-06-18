# Minitalk

## 🧠 Project Summary

**Minitalk** is a small data transmission project that demonstrates interprocess communication in Unix-based systems using only **UNIX signals**. It consists of a `server` and a `client` program: the client sends a message to the server via signals, and the server receives and displays it in real-time.

---

## 📦 Contents

- [Project Summary](#-project-summary)
- [How It Works](#-how-it-works)
- [Mandatory Requirements](#-mandatory-requirements)
- [Compiling and Usage](#-compiling-and-usage)
- [Allowed Functions](#-allowed-functions)

---

## ⚙️ How It Works

- The **server** starts and displays its **PID** (process ID).
- The **client** takes the server's PID and a string as arguments.
- The client sends the string to the server using only the `SIGUSR1` and `SIGUSR2` signals, encoding each character bit by bit.
- The server decodes the incoming signals into characters and prints the final message on the terminal.

---

## ✅ Mandatory Requirements

- Communication must use **only SIGUSR1 and SIGUSR2**.
- The server must:
  - Print its PID on startup.
  - Receive and display messages from the client(s) with no delay.
- The client must:
  - Take 2 arguments: the server's PID and the string to send.
  - Send the string to the server, character by character using UNIX signals.
- Server must be able to **handle multiple clients in sequence** without being restarted.
- The program must:
  - Be free from memory leaks.
  - Be stable and not crash (e.g., segfault, double free, etc.).
  - Conform to the **Norm** and use only allowed functions.

---

## 🛠 Compiling and Usage

To clone the project:
```bash
git clone --recurse-submodules https://github.com/Stacy314/minitalk
```

To compile the project:

```bash
make
```
To start the server:

```bash
./server
```
It will display a PID (e.g., Server PID: 12345).

To send a message from the client:

```bash
./client <server_pid> "Your message here"
```

Example:

```bash
./client 12345 "Hello, server!"
```

To clean compiled objects:

```bash
make clean
```
To remove all compiled files including executables:

```bash
make fclean
```
To recompile everything:

```bash
make re
```
## ✔️ Allowed Functions
- write

- ft_printf

- signal, sigemptyset, sigaddset, sigaction

- kill, getpid

- malloc, free

- pause, sleep, usleep, exit

## 👀 Notes
Signal transmission is not queued on Linux. Make sure to handle signals reliably with delays or acknowledgments.

Keep the implementation efficient — printing 100 characters shouldn't take a whole second.

## 💡 Inspiration
Named after the simplicity of the task — a "mini talk" between two programs — this project is a great introduction to Unix signal handling, bitwise manipulation, and low-level IPC.
