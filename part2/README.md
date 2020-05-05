## 1 Usage

### 1.1 Compiling & Running on CSE
```text
You can run the following four commands to compile and run on cse.unl.edu:

cd sshrestha11_pa3/part2
make
./part2
```

### 1.2 Cleaning the folder(removes the current binary file and .out files)

```text
cd sshrestha11_pa3/part2
make clean
```

### 1.3 Parsing the input command

```text
./part2 -b 1 -p 5 -c 5 -i 10
./part2 -b 4 -p 30 -c 30 -i 10
./part2 -b 1000 -p 10 -c 10 -i 10000
parseInput(argc, argv);
```

### 1.4 Signal and wait (Hoare-implementation)

```text
I chose this signal and wait because i found it easier to keep track of threads using this semantics. Also, found it easier to employ mutual exclusion.
```
