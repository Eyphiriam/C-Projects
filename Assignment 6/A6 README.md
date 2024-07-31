
### Code Functionality

1. **Global Variables**:
   - `buffer`: A queue to hold integers produced by producers.
   - `mtx`: A mutex to protect access to the buffer.
   - `cv`: A condition variable used to notify consumers when there is data to consume or when production is complete.
   - `counter_mtx`: A mutex to protect access to the counters `total_produced` and `total_consumed`.
   - `total_produced` and `total_consumed`: Counters to track the number of items produced and consumed.
   - `all_producers_done`: A boolean flag indicating whether all producers have finished producing.

2. **Producer Function (`produce`)**:
   - Each producer pushes integers (0 to 9) into the buffer.
   - After producing each item, it notifies all waiting threads (consumers) that new data is available.
   - Tracks the total number of items produced using `total_produced`.
   - Sets `all_producers_done` to true when finished and notifies all waiting threads.

3. **Consumer Function (`consume`)**:
   - Consumers wait until the buffer is not empty or until all producers are done.
   - They consume items from the buffer until it is empty and all producers have finished.
   - Tracks the total number of items consumed using `total_consumed`.

4. **Main Function**:
   - Parses command line arguments to determine the number of producers and consumers.
   - Creates and starts producer and consumer threads.
   - Waits for all threads to complete.
   - Outputs the total number of items produced and consumed.

### Key Points to Consider

- **Thread Safety**: The use of mutexes (`mtx` and `counter_mtx`) ensures that changes to shared resources (like the buffer and counters) are thread-safe.
- **Condition Variable**: Used to efficiently block consumers when the buffer is empty and wake them when there is data to consume or when production has ended.
- **Proper Locking**: The code uses `std::unique_lock` for managing mutex locking, which provides exception safety and flexibility for condition variables.
- **Command Line Arguments**: The program expects two arguments specifying the number of producers and consumers. It handles incorrect input by displaying usage information.

### Summary

The code effectively demonstrates a multi-threaded producer-consumer scenario using modern C++ synchronization constructs. 

