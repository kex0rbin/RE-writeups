# crackme: what_password by [Cyberpenguin](https://crackmes.one/crackme/6a83e2f205a9e80a90724421)
This is another simple crackme but *in this case I used WSL (debian in linux) and just static analysis and algorithm reconstruction*. The author said that it's necesary to guess or find the correct password. There are two ways to resolve it.
The first one it's really easy, patching the program. But now I want to find the correct password. 
And that means learn the algorithm and if it's neceasry, do the keygen. (I'll do in C).
So, let's do it!.

## First step : recon
At first, the basic information gathered from this crackme. 
I used xdump to analyse this file cause if I'm honest, I didn't see the Arch and Code specifications from crackmes.one
And the output was:

```bash
❯ xdmp f what_password
File name: what_password
File size: 16984 bytes. (16.59 kb)
Format: Executable and Linkable Format file (ELF). Linux executable.
```
## Second step: analysis

And now, I know that i'ts and ELF file (linux file), and then I opened ghidra.
I recognized that it's assembly code because of the syscalls were present. And the logic was simple, if
the password was wrong, the program ends with:
```bash
❯ ./what_password                                                                                                       idkthepassword                                                                                                          Incorrect password!
```   
I did some notes below and after the main function (password encrypt) and renamed the three variables (in spanish):

```bash
 ...
                    /* input syscall */
  syscall();
  valor2 = 0;
  for (valor3 = '\x02'; valor1 = ((&pw)[valor2] ^ 0x27) + valor3, valor1 == (&input)[valor2];
      valor3 = valor3 + '\x02') {
    if (valor1 == '\n') goto right;
    valor2 = valor2 + 1;
  }
                    /* print syscall size 0x14 */
  syscall();
                    /* exit syscall 60 */
  syscall();
 ...
```
So, I noticed that `valor3` starts at 0x2, `valor1` is always reset after the logical operation, and `valor1` is subsequently compared with the result. Finally `valor2` acts as an array index, as it increments by 1.
There's an weird and interesting value, `pw`. So, I traced the location of this variable. I found the
address and next to pw, there was `DAT_00404029`. 

The first value was 4E, so I think that this value is compared recursively. I was wrong. Then, I combined pw with `DAT_00404029`beacuse I though both were the same array. The complete hex value was:

```bash
> 4e 49 1d 42 7c 41 7c 33 75 6a 6b 3c 7e 7f cb
```

And I tried to reconstruct the logic of the encryption. There's a part of my analysis (first iteration), but I did it in notes.
You can read the whole file in this same directory. It's called, xoranalysis.txt. I just did three iterations and
it was necesary to do the keygen.

EDIT: I did the xor operations and the rest in online calculators.
```bash
>>>>>iteration1>>>>>>
val1 = (&pw + val2) xor 0x27 + val3
val1 = 4e xor 0x27 + 0x02
val1 = 0x69 + 0x02
val1 = 0x6B (k)

val3 += 0x02
val3 = 0x04
val2 += 0x01
val2 = 0x01
```
So I wrote the keygen. The part of the logic is below, but you can see the keygen code in this repository too.
It's a C code.
```bash
	for(char *p = pw; *p != 0x00 ;p++){
		val1 = *p ^ XOR_KEY;
		val1 += val3;
		printf("%c",val1);

		//;update the variables
		val3 += 0x02;
		val2 += 0x01;
	}
```
### Solution
Finaly, I compiled the keygen and this is my result:
```bash
❯ ./keygen
KEY: kr@meri$dab3st
❯ ./what_password 
kr@meri$dab3st          
Correct! You won!         
```
As you can see, the key was correct!. My code and my notes are in this same directory. Check it, I'll be
grateful with u. Thanks!

### Screenshots
Not for now.
### Author
Author : [Cyberpenguin](https://crackmes.one/user/Cyberpenguin)
