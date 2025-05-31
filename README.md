# 🔐 File Encryptor

A modular, command-line file encryption and decryption tool written in C using low-level system calls. Supports two cipher algorithms: **XOR** and **Caesar**. Designed for system programming and final year coursework — featuring dynamic memory, modular architecture, and Linux syscall usage.

---

## ✅ Features

- XOR and Caesar cipher support
- Uses `open`, `read`, `write`, `close` (Linux syscalls)
- Dynamic memory allocation (`malloc`, `free`)
- Modular design with separate `cipher.c` and `cipher.h`
- CLI argument parsing and validation
- Auto-generates output filenames if not specified
- Supports any file type (text or binary)

---

## 📦 Project Structure

```
file_encryptor/
├── Makefile
├── cipher.c
├── cipher.h
├── main.c
├── README.md
```

---

## 🐳 Docker Development Guide

This project is designed to be developed and run inside a Docker container using a mounted volume. The steps below show you how to build, start, and use the container to compile and run the `file_encryptor` program.

### 📁 1. Prepare Project Folder (on Host)

Place all project files into a folder like:

```
~/Desktop/FileEncryptor
```

---

### 🐳 2. Create and Start Docker Container (One-Time Setup)

```bash
docker run -it --name encryptor-dev \
  -v ~/Desktop/FileEncryptor:/workspace \
  ubuntu
```

---

### 🧰 3. Inside the Container: Install Tools

```bash
apt update && apt install -y gcc make
cd /workspace
```

---

## 🛠️ Build Instructions

```bash
make         # Compile the program
make clean   # Clean up build files
```

---

## 🏃 Usage

### 🔐 Encrypt with XOR cipher:

```bash
./file_encryptor xor encrypt <Key> <input_file> [output_file]
```

### 🔓 Decrypt with XOR cipher:

```bash
./file_encryptor xor decrypt <Key> <input_file> [output_file]
```

### 🔐 Encrypt with Caesar cipher:

```bash
./file_encryptor caesar encrypt <Shift> <input_file> [output_file]
```

### 🔓 Decrypt with Caesar cipher:

```bash
./file_encryptor caesar decrypt <Shift> <input_file> [output_file]
```

---

## 📄 Example

```bash
./file_encryptor xor encrypt 42 input.txt
./file_encryptor xor decrypt 42 input.txt.enc

./file_encryptor caesar encrypt 3 input.txt
./file_encryptor caesar decrypt 3 input.txt.enc
```

---

## 💾 Custom Output Filename

```bash
./file_encryptor xor encrypt 42 input.txt my_encrypted.bin
./file_encryptor caesar decrypt 3 input.txt.enc decrypted.txt
```

---

## 🎓 Learning Outcomes

- Mastered low-level file I/O using Linux system calls
- Implemented dynamic memory using `malloc()` and `free()`
- Designed a modular program in C using `.h` and `.c` files
- Used command-line argument parsing and validation
- Built and ran the project inside a Dockerized Linux dev environment
---

Link to the original [GitHub repository](https://github.com/hossei-cyber/file-encryptor)