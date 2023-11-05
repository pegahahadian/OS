**Producer-Consumer Problem Solution**

This project demonstrates a solution to the Producer-Consumer problem using C programs. The Producer generates items and places them onto a shared table. The Consumer picks up items from this table. Synchronization between Producer and Consumer is achieved using semaphores. The table is a shared memory space limited to holding a maximum of two items at a time.

**Instructions**

-Compile the programs using the provided commands:

```
$ gcc producer.c -pthread -lrt -o producer
```
```
$ gcc consumer.c -pthread -lrt -o consumer
```

-Run the compiled programs using the following command:

```
$ ./producer & ./consumer &
```

-This command will start the Producer and Consumer programs in the background, simulating the item generation and consumption process.

**Output Capture**

-To save the output to a file, use the following commands:
```
$ ./producer > producer_output.txt 2>&1 &
```

```
$ ./consumer > consumer_output.txt 2>&1 &
```

**File Description**

producer.c: C code for the Producer program

consumer.c: C code for the Consumer program
