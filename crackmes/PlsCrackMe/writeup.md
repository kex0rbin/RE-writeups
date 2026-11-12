# crackme: PlsCrackme by [BadEngineer](https://crackmes.one/crackme/697f67fe977274421cc111ef)
In this crackme, the author said that it's necesary to find the correct password and do not parching. I decided to analyze the alrgoritm and do a simple keygen (or password generator), it's not complicated at all. Let's do it!.

## First step : recon
At first, I noticed that the file it's called NormalCrackme.
Besides, the information gathered from DIE was that it's x86-64 file, written in c.
The entry point was `0x0000000140001440`. But using a debugger was not necessary on this occasion, only a static analysis.

## Second step: analysis
At first, using ghidra, I see the main function. It asks you to enter a password, but check it is longer than 13 characters. There is a function called `check`, which contains the algorithm
```bash
  __mingw_printf("Please enter the password : ");
  __mingw_scanf("%s",password);
  while( true ) {
    returnCode = Checker(password);
    if ((int)returnCode != 0) break;
    sVar1 = strlen(password);
    if (0xd < sVar1) {       <-- hereee
      puts("Way 2 Big!");
    }
```   
At first, the password length is 13 characters. Let's see the algotithm.
In checker function, I found four int variables, that I recalled `check1`,`check2`,`check3`,`check4`, the iterator as `i` and the length as `passCode`.
And here's the algorithm (I changed the chars to decimal numbers, it's easier to analyse).

```bash
    if ((passChar < 48) || (57 < passChar)) {
      if ((((passChar < 33) || (47 < passChar)) &&
          (((passChar < 58 || (64 < passChar)) && ((passChar < 91 || (96 < passChar)))))) &&
         ((passChar < 123 || (126 < passChar)))) {
        if ((passChar < 65) || (91 < passChar)) {
          if ((96 < passChar) && (passChar < 123)) {
            ...
```
If the value pass the condition, it proceeds to the next conditional; otherwise, 1 is added to one of the variables. I mean, if the value doesn't pass the first `if` , 1 is added to `check1`; if the value doesn't pass the second `if`, 1 is added to `check2`, and so on. This section of the code adds 1 to the checks and return to the main function, where is it compared and if the result is 1, the password was found, otherwise, it's incorrect:

```bash
  if ((((check1 == 3) && (check2 == 3)) && (check3 == 3)) && (check4 == 4)) {
    returnCode = 1;
  }
  else {
    returnCode = 0;
  }
  return returnCode;
```
And this was my analysis in a txt file.
Only adds 1 if the pass[i] it's:
- check1 = 48 - 57 (3 values)
- check2 = 33 - 47, 58 - 64, 91 - 96, 123 - 126 (3 values)
- check3 = 65 - 90 (3 values)
- check4 = 97 - 122 (4 values)

With this, I decided to try with: 333***AAAaaaa
and the output was:
 ```bash
 PS D:\crackmes> .\NormalCrackme.exe
 Please enter the password : 333***AAAaaaa
 Good job, You Really Cracked it!
```
But I decided to do a simple keygen in C. The code it's here in this same directory.

### Solution
My simple keygen just generates 5 posible random keys (passwords) that you can use it. All of them work.

Use hexadecimal values ​​for the symbols to avoid potential errors (I used sizeof for this cause it's not a string), and treat the letters as strings. Also, use `rand()` to generate random keys from the values ​​in the arrays instead of a single password or two. Here are two outputs.

 ```bash
  VALID KEY: { 109.-;ARWxivi }
  VALID KEY: { 337:.^XTBggmg }
  VALID KEY: { 897*.$KVZjdog }
  VALID KEY: { 852$^'MFAoniw }
  VALID KEY: { 457-#;XEBcthp }
```
 ```bash
  VALID KEY: { 018/-$MNPzhyp }
  VALID KEY: { 557:+<QINrink }
  VALID KEY: { 374?"'GUHhxyv }
  VALID KEY: { 157#*,YLLomnq }
  VALID KEY: { 140#->GWFmalo }
```
### Screenshots
Not for now.
### Author
Author : [BadEngineer](https://crackmes.one/user/BadEngineer)
