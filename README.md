# Rushikesh CVFS (Custom Virtual File System)

## 📌 Project Overview

**Rushikesh CVFS** is a **Custom Virtual File System implemented in C** that simulates basic file system operations inside memory.
It demonstrates how operating systems manage **files, inodes, file descriptors, and permissions**.

This project is designed for **learning Operating System concepts such as File System Architecture, Inode structure, File Tables, and Memory Management.**

---

# 🚀 Features

The CVFS supports several basic file system commands similar to Linux.

| Command                         | Description            |
| ------------------------------- | ---------------------- |
| `creat <filename> <permission>` | Create a new file      |
| `write <fd>`                    | Write data into a file |
| `read <fd> <size>`              | Read data from a file  |
| `ls`                            | List all files         |
| `unlink <filename>`             | Delete a file          |
| `man <command>`                 | Show manual page       |
| `help`                          | Display all commands   |
| `clear`                         | Clear terminal         |
| `exit`                          | Terminate the system   |

---

# 🧠 Concepts Implemented

This project implements key operating system concepts:

* Boot Block
* Super Block
* Inode Structure
* File Table
* User File Descriptor Table (UFDT)
* Linked List based Inode Management
* File Permissions (Read / Write)
* File Descriptor Handling
* Memory Allocation
* Virtual File Storage

---

# 🏗 System Architecture

```
            +------------------+
            |    Boot Block     |
            +------------------+
                     |
                     v
            +------------------+
            |    Super Block    |
            | Total Inodes      |
            | Free Inodes       |
            +------------------+
                     |
                     v
           +-------------------+
           |       DILB        |
           | (Linked List of   |
           |      Inodes)      |
           +-------------------+
                     |
                     v
           +-------------------+
           |     File Table    |
           | (Opened Files)    |
           +-------------------+
                     |
                     v
           +-------------------+
           |       UFDT        |
           | User File Table   |
           +-------------------+
```

---

# 📂 Data Structures Used

### BootBlock

Stores system boot information.

### SuperBlock

Maintains total and free inodes.

### Inode

Stores metadata about files.

Fields include:

* File Name
* File Size
* Actual File Size
* File Type
* Permission
* Reference Count
* Data Buffer

### FileTable

Maintains information about opened files.

### UAREA

Contains process name and **UFDT (User File Descriptor Table)**.

---

# 🔐 File Permissions

| Value | Permission   |
| ----- | ------------ |
| 1     | Read         |
| 2     | Write        |
| 3     | Read + Write |

---

# ⚙️ Constants Used

| Constant     | Meaning                      |
| ------------ | ---------------------------- |
| MAXFILESIZE  | Maximum file size (50 bytes) |
| MAXOPENFILES | Maximum open files (20)      |
| MAXINODE     | Total inodes (5)             |

---

# 🖥 Example Usage

### Create File

```
Rushikesh CVFS : > creat Demo.txt 3
File gets successfully created with FD 3
```

### Write File

```
Rushikesh CVFS : > write 3
Enter the data that you want to write :
Hello CVFS
```

### Read File

```
Rushikesh CVFS : > read 3 10
Data from file is : Hello CVFS
```

### List Files

```
Rushikesh CVFS : > ls
InodeNo  FileName   FileSize
1        Demo.txt   10
```

### Delete File

```
Rushikesh CVFS : > unlink Demo.txt
File gets successfully deleted
```

---

# 🛠 How to Compile and Run

### Compile

```bash
gcc cvfs.c -o cvfs
```

### Run

```bash
./cvfs
```

---

# 📁 Project Structure

```
CVFS
│
├── cvfs.c
├── README.md
```

---

# 🎯 Learning Outcomes

After completing this project, you will understand:

* File system working
* Inode structure
* File descriptors
* Memory allocation in file systems
* OS level file management
* Linked list based resource management

---

# 👨‍💻 Author

**Rushikesh Baban Dhande**
Aspiring Full Stack Developer

Skills:

* C / C++
* Java
* JavaScript
* React.js
* Node.js
* SQL / NoSQL

---

# ⭐ GitHub

If you like this project, give it a ⭐ on GitHub.
