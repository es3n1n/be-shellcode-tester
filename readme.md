## be-shellcode-tester

### What is this?
As you may know battleye loads custom shellcodes for detecting some stuff. \
Well this software is running those shellcodes and dumps every report that was sent.

### How's this works?
- Iterating dir with previously dumped shellcodes and maps it to self mem.
- Passes 'hooked' GetProcAddress/GetModuleHandleA/send_report functions to shellcode.
- Reads report and prints info about it.

### How's it useful for me?
Imagine your p2c is detected in be-protected game, all you need to do is dump their shellcodes and check your cheat with this tool.

### Features:
- [x] Hookless
- [x] Parses 9/10 reports(tested only on eft/r6 tho)
- [x] Both .dll and .exe versions are available
- [x] Decrypts encrypted reports from shellcodes
- [ ] Decrypts encrypted reports from BEClient2.dll

### How can i dump shellcode from game?
Hook GetProcAddress, get mbi of return address and check if it's not a legit module.

### Screenshot:
![img](https://i.imgur.com/9qbQ6JZ.png)

### Credits:
[@es3n1n](https://github.com/es3n1n/) \
[@user344](https://github.com/user344/)

