# Operating Systems Programming Project

This project contains practical exercises (TPs) focused on operating systems concepts including process management, threading, synchronization, file I/O, and network programming in C.

**Authors**: Kylian MEHDI & Nadia LAHYA  
**Group**: TD1H

## 📁 Project Structure

```
├── LectureEcriture/          # File I/O and PPM image manipulation
├── TPFork/                   # Process creation and fork() exercises
├── TPRoadSocket/             # Network programming with road simulation
├── TPSynchronisations/       # Threading and synchronization exercises
└── TPThreadRoad/             # Thread management exercises
```

## 🚀 Modules Overview

### 1. LectureEcriture (File Reading/Writing)
**Purpose**: File I/O operations and PPM image format manipulation

**Key Programs**:
- `firstPPM.c` - Create basic PPM image files
- `copy.c` - File copying utilities for PPM images
- `darker.c` - Image darkening operations (divides pixel values by 6)
- `tuner.c` - Image brightening operations (multiplies pixel values by 4)
- `binaryPPM.c` - Convert text PPM to binary PPM format
- `gradient.c` - Generate gradient images
- `arguments.c` - Command-line argument handling for image processing

**Features**:
- PPM image format support (P3/P6)
- Pixel manipulation algorithms
- File handling with proper error checking

### 2. TPFork (Process Management)
**Purpose**: Process creation, forking, and inter-process communication

**Key Programs**:
- `fork.c` - Basic fork() demonstration
- `forkGlobales.c` - Global variables behavior across processes
- `forkShared.c` - Shared file access between processes
- `forkSharedWait.c` - Process synchronization with wait()
- `forkSync.c` - Advanced process synchronization
- `forkBonus.c` - Using exec() family functions

**Key Concepts Demonstrated**:
- Process creation with `fork()`
- Process IDs (PID/PPID) understanding
- Variable isolation between processes
- File sharing and race conditions
- Process synchronization with `wait()`

### 3. TPSynchronisations (Threading & Synchronization)
**Purpose**: Multi-threaded programming with synchronization mechanisms

**Key Programs**:
- `stillOnTheRoadQ1.1.c` - Basic mutex synchronization for road crossing
- `stillOnTheRoadQ1.2.c` - Enhanced car validation system with mutex
- `stillOnTheRoadQ2.c` - Semaphore-based lane switching system
- `stillOnTheRoad.c` - Base road simulation

**Features**:
- **Multi-threaded car simulation** with 300 concurrent vehicles
- **Mutex locks** for critical sections (road crossing protection)
- **Semaphore-based lane management** with automatic switching every 2 seconds
- **Safe distance validation** between vehicles (minimum 50 units)
- **Real-time traffic simulation** with collision avoidance

**Technical Details**:
- Maximum 3 cars can cross simultaneously per lane
- Lane switching mechanism alternates traffic flow
- Thread-safe car movement with distance checking

### 4. TPRoadSocket (Network Programming)
**Purpose**: Socket programming with road simulation integration

**Key Programs**:
- `RoadSocketIn.c` - TCP server accepting incoming car connections
- `RoadSocketInOut.c` - Bidirectional client-server communication

**Features**:
- **TCP socket server** implementation on port 4321
- **Real-time car simulation** over network
- **Client connection handling** with threading
- **Network-based car spawning** system

### 5. TPThreadRoad (Thread Management)
**Purpose**: Advanced threading exercises with interactive controls

**Key Programs**:
- `onTheRoad.c` - Basic single-threaded car simulation
- `onTheRoad2.c` - Multi-threaded car creation
- `onTheRoad3.c` - Enhanced thread management
- `onTheRoad4.c` - Interactive controls with keyboard input

**Features**:
- **Interactive keyboard controls**: 
  - `V` key: Add new car with random direction
  - `P` key: Pause/resume simulation
- **Dynamic car creation** during runtime
- **Thread synchronization** for pause functionality
- **Allegro integration** for graphics and input handling

## 🛠️ Dependencies

- **Graphics Library**: Allegro 5 (for road visualization)
- **Threading**: POSIX threads (pthread)
- **Networking**: Standard POSIX sockets
- **Build System**: Make
- **Compiler**: GCC with C99 standard

## 🔧 Building the Project

Each module contains its own `Makefile`:

```bash
# Build file I/O exercises
cd LectureEcriture
make

# Build process management exercises
cd TPFork
make

# Build synchronization exercises  
cd TPSynchronisations
make

# Build network programming exercises
cd TPRoadSocket
make

# Build thread management exercises
cd TPThreadRoad
make

# Clean build files in any directory
make clean
```

## 🎮 Running the Programs

### File I/O Examples:
```bash
cd LectureEcriture
./darker                    # Darkens Chaton.ppm
./arguments input.ppm output.ppm  # Process with arguments
./gradient                  # Generate gradient image
```

### Process Management:
```bash
cd TPFork
./fork                      # Basic fork demonstration
./forkGlobales             # Global variables test
./forkShared               # Shared file access
```

### Threading & Synchronization:
```bash
cd TPSynchronisations
./stillOnTheRoadQ1.1       # Mutex-based road crossing
./stillOnTheRoadQ1.2       # Enhanced validation system
./stillOnTheRoadQ2         # Semaphore lane switching
```

### Network Programming:
```bash
cd TPRoadSocket
./RoadSocketIn             # Start TCP server
./RoadSocketInOut          # Bidirectional communication
```

### Interactive Thread Management:
```bash
cd TPThreadRoad
./onTheRoad4               # Interactive car simulation
# Press 'V' to add cars, 'P' to pause, 'ESC' to exit
```

## 📋 Key Programming Concepts Demonstrated

1. **Process Management**
   - Fork, exec, wait operations
   - Process hierarchy and adoption
   - Inter-process communication

2. **Threading**
   - Pthread creation, joining, and management
   - Thread-safe programming practices
   - Concurrent execution control

3. **Synchronization**
   - Mutexes for critical section protection
   - Semaphores for resource management
   - Condition variables and signaling

4. **Network Programming**
   - TCP socket programming
   - Client-server architecture
   - Network-based real-time systems

5. **File I/O**
   - Binary and text file handling
   - Image processing algorithms
   - Command-line argument processing

6. **Real-time Systems**
   - Traffic simulation with timing constraints
   - Interactive user interfaces
   - Resource management and scheduling

## ⚙️ Runtime Environment

- **Platform**: Linux/Unix systems (tested on Ubuntu)
- **Compiler**: GCC with pthread support (`-pthread` flag)
- **Graphics**: Allegro 5 library for visualization
- **Library Path**: `/users/but/info/Public/Systeme/onTheRoad/` (for road.h)

## 📚 Educational Objectives

This project serves as a comprehensive introduction to systems programming, covering:

- **Low-level system calls** and their proper usage
- **Concurrent programming** patterns and best practices
- **Resource management** and synchronization techniques
- **Network programming** fundamentals
- **Real-time system** design principles
- **Memory management** and thread safety
- **Error handling** and robust programming practices

## 🔍 Technical Highlights

- **Thread Safety**: All multi-threaded components use proper synchronization
- **Error Handling**: Comprehensive error checking and graceful failure handling
- **Resource Management**: Proper cleanup of threads, sockets, and file descriptors
- **Scalability**: Supports hundreds of concurrent entities (300 cars in synchronization exercises)
- **Real-time Performance**: Optimized for smooth animation and responsive controls

---