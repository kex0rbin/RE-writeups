# crackme: mexican by [evilprogrammer](https://crackmes.one/crackme/5d63011533c5d46f00e2c305)
This is an simple crackme. *In this case I used Windows Powershell instead of Debian or WSL shell*. The author said that there are two ways to resolve it, here is one of them that I did. 
The file is called Untitled.exe (PE file). I patched two instructions to change the behaviour of this crackme.
So, let's see.

## First step : recon
Basic information gathered from this crackme. I used DIE for identify the architecture (x86), base point
and the entry point. These concepts are really necesary to identify before the analysis.

```bash
Base point: 0x0040000
Entry point: 0x004014e0
```
## Second step: analysis

With this info, I started x64dbg for dynamic analysis because I want to improve my skills in this tool and specially in dynamic analysis.
Checking it, I jumped to the base point and step by step I analyzed the behaviour. The program runs and the
console output is below:
```bash
D:\crackmes> .\Untitled1.exe
try harder     
```
Following the execution, I found a jump very interesting,  
``` 
 ...
 004014ED E8 EE0A0000 call untitled1.401FEO
 004014F2 83C4 0C add esp,C
 00401455 E9 EE0A0000 jmp untitled1.401180 <- here!
 ...
```
This jump is located before of one *stack frame* or prologue (function creation) in 32 bits and jumps to another address.
I analized the execution of that.

``` 
 00401500 55 push ebp
 00401501 89E5 mov ebp,esp 
 00401503 83EC sub esp,28 
```
Below, we can find the structure of malloc and printf (the string key). I found the string of the key, but theres no 
'\0', that's why it will print trash or weird characters in the output.
So, I decided to change that jump that I mencionated and complete the next instruction with nop

``` 
 004014F5 E9 EE0A0000 jmp untitled1.401500<- Begining of the stack frame
```

### Solution
Finally, the program runs and the new output is this key:
```bash
flag{M3x1c4nMl4lw4r3_pl3rro}  
½½½½½½½½■
```
But it's not enough, I decided to use ghidra to patch this program and try to analize the binary.


Note: It's easier to use ghidra in this case 'cause you can find the referenced string with strings tool from ghidra.
So, I decided to find the address 0x004014F5 and change the address of the jump,( from 0x00401180 to 0x00401500).
And now, the tag of the address has changed to flag, what confirms what I did.


Patched, now we run the program and the output is:
```bash
PS D:\crackmes> .\cracked.exe                                                                                           flag{M3x1c4nMl4lw4r3_pl3rro}  
helª)Á8{, 
```

### Screenshots
Not for now.
### Author
Author : [evilprogrammer](https://crackmes.one/user/evilprogrammer)
