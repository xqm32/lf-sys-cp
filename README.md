1. Compile `lfcp.c` and `syscp.c`

   ```
   $ cmake .
   $ make
   ```

2. Create a 512MB file `test`

   ```
   $ fallocate -l 512M test
   $ stat test
     File: test
     Size: 536870912       Blocks: 1048584    IO Block: 4096   regular file
   Device: 820h/2080d      Inode: 39517       Links: 1
   Access: (0644/-rw-r--r--)  Uid: ( 1000/     xqm)   Gid: ( 1000/     xqm)
   Access: 2022-11-30 13:36:02.502376982 +0800
   Modify: 2022-11-30 13:36:02.502376982 +0800
   Change: 2022-11-30 13:36:02.502376982 +0800
    Birth: -
   ```

3. Compare `syscp[BUFFSIZE=1024]`, `lfcp` and `cp`

   ```
   $ time ./lfcp test test.lfcp
   real    0m7.463s
   user    0m4.788s
   sys     0m2.659s
   $ time ./syscp test test.syscp
   syscp[1024]: Copying...
   
   real    0m1.249s
   user    0m0.050s
   sys     0m1.195s
   $ time cp test test.cp
   real    0m0.468s
   user    0m0.000s
   sys     0m0.459s
   $ rm -f test.* # Remove all test copies
   ```

4. Compare `syscp[BUFFSIZE=16,128,1024,4096,16384]`

   ```
   $ cmake -DBUFFSIZE=16 . # BUFFSIZE=16
   $ make syscp
   $ time ./syscp test test.syscp16
   syscp[16]: Copying...
   
   real    0m57.522s
   user    0m2.290s
   sys     0m55.217s
   $ cmake -DBUFFSIZE=128 . # BUFFSIZE=128
   $ make syscp
   $ time ./syscp test test.syscp128
   syscp[128]: Copying...
   
   real    0m7.525s
   user    0m0.319s
   sys     0m7.188
   $ cmake -DBUFFSIZE=1024 . # BUFFSIZE=1024
   $ make syscp
   $ time ./syscp test test.syscp1024
   syscp[1024]: Copying...
   
   real    0m1.157s
   user    0m0.080s
   sys     0m1.077s
   $ cmake -DBUFFSIZE=4096 . # BUFFSIZE=4096
   $ make syscp
   $ time ./syscp test test.syscp4096
   syscp[4096]: Copying...
   
   real    0m0.486s
   user    0m0.020s
   sys     0m0.465s
   $ cmake -DBUFFSIZE=16384 . # BUFFSIZE=16384
   $ make syscp
   $ time ./syscp test test.syscp16384
   syscp[16384]: Copying...
   
   real    0m0.434s
   user    0m0.010s
   sys     0m0.415s
   ```
   
   

